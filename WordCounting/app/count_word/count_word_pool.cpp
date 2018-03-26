#include <assert.h>

#include "count_word.h"
#include "count_word/count_word_pool.h"

using namespace std;


#ifdef _WORD_COUNTER_POOL_TRIE

WordCounterPool::WordItem::WordItem(string w, string e) {
	assert(exp_to_word(e) == w);
	word = w;
	exp = e;
}

void WordCounterPool::WordItem::update(string s) {
	assert(exp_to_word(s) == word);
	exp = exp < s ? exp : s;
}


void WordCounterPool::WordItem::add() {
	count++;
}


WordCounterPool::Node::Node() {
	word = NULL;
}

int WordCounterPool::WordItem::get_count() {
	return count;
}


void WordCounterPool::add_word(Word w) {

}


void WordCounterPool::add_phrase(Word w1, Word w2) {

}

#endif
#ifdef _WORD_COUNTER_POOL_HASH

WordCounterPool::Node::Node(string w, string e) {
	assert(exp_to_word(e) == w);
	// TODO: 正式代码中除去
	word = w;
	exp = e;
	count = 0;
	next = 0;

}


string WordCounterPool::Node::get_word() {
	return word;
}


string WordCounterPool::Node::get_exp() {
	return exp;
}


int WordCounterPool::Node::get_count() {
	return count;
}


void WordCounterPool::Node::add() {
	count++;
}


WordCounterPool::HashTable::HashTable() {
	for (int i = 0; i < size; i++) {
		arr[i] = NULL;
	}
}


void WordCounterPool::HashTable::release(WordCounterPool::Node * p) {
	if (p) {
		if (p->next) release(p);
		delete p;
		p = NULL;
	}
}


WordCounterPool::HashTable::~HashTable() {
	for (int i = 0; i < size; i++) {
		release(arr[i]);
	}
}


int WordCounterPool::HashTable::hash(string s) {
	unsigned long h = 0;
	unsigned long g;
	for (int i = 0; i < s.size(); i++) {
		h = (h << 4) + s[i];
		g = h & 0xF0000000L;
		if (g) {
			h ^= g >> 24;
			h &= ~g;
		}
	}
	return (h % size);
}


WordCounterPool::Node * WordCounterPool::HashTable::get_node(string w, string e) {
	int key = hash(w);
	WordCounterPool::Node * p = arr[key];
	if (p) {
		while (p->get_word() != w) {
			if (p->next) p = p->next;
			else {
				p = p->next = new Node(w, e);
				break;
			}
		}
	}
	else {
		p = arr[key] = new Node(w, e);
	}
	return p;
}


WordCounterPool::WordCounterPool() {
	for (int i = 0; i <= 10; i++) {
		max_word[i] = max_phrase[i] = NULL;
	}
}


void WordCounterPool::update(Node * arr[], Node * p) {
	for (int i = 0; i < 10; i++) {
		if (arr[i] == NULL || arr[i] == p) {
			arr[i] = p;
			return;
		}
		else {
			int ci = arr[i]->get_count();
			int cp = p->get_count();
			if ((ci < cp) || (ci == cp && arr[i]->get_word() > p->get_word())) {
				for (int j = 10 - 1; j > i; j--) {
					arr[j] = arr[j - 1];
				}
				arr[i] = p;
				return;
			}
		}
	}
}


void WordCounterPool::add_word(Word w) {
	Node * p = word_table.get_node(w.get_word(), w.get_exp());
	p->add();
	update(max_word, p);
}


void WordCounterPool::add_phrase(Word w1, Word w2) {
	string w = w1.get_word() + " " + w2.get_word();
	string e = w1.get_exp() + " " + w2.get_exp();
	Node * p = phrase_table.get_node(w, e);
	p->add();
	update(max_phrase, p);
}


int WordCounterPool::get_max_word(int i, string &e){
	if (i < 0 || i >= 10 || max_word[i] == NULL) {
		return -1;
	}
	else {
		e = max_word[i]->get_exp();
		return max_word[i]->get_count();
	}
}


int WordCounterPool::get_max_phrase(int i, string &e) {
	if (i < 0 || i >= 10 || max_phrase[i] == NULL) {
		return -1;
	}
	else {
		e = max_phrase[i]->get_exp();
		return max_phrase[i]->get_count();
	}
}

#endif