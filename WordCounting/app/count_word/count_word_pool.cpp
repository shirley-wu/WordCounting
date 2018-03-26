#include <assert.h>

#include "count_word.h"
#include "count_word/count_word_pool.h"

using namespace std;


WordCounterPool::WordCounterPool() {
	for (int i = 0; i <= 10; i++) {
		max_word[i] = NULL;
		max_phrase[i] = NULL;
	}
}


template <class T>
void WordCounterPool::update(node<T> * arr[], node<T> * p) {
	for (int i = 0; i < 10; i++) {
		if (arr[i] == NULL || arr[i] == p) {
			arr[i] = p;
			return;
		}
		else {
			int ci = arr[i]->count;
			int cp = p->count;
			if ((ci < cp) || (ci == cp && p->dat < arr[i]->dat)) {
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
	string key = w.get_word();
	node<Word> * p = word_table.get_node(key, w);
	p->add();
	p->dat.update(w);
	update(max_word, p);
}


void WordCounterPool::add_phrase(Word w1, Word w2) {
	string key = w1.get_word() + " " + w2.get_word();
	Phrase ph = Phrase(w1, w2);
	node<Phrase> * p = phrase_table.get_node(key, ph);
	p->add();
	p->dat.update(ph);
	update(max_phrase, p);
}


int WordCounterPool::get_max_word(int i, string &e){
	if (i < 0 || i >= 10 || max_word[i] == NULL) {
		return -1;
	}
	else {
		e = max_word[i]->dat.get_exp();
		return max_word[i]->count;
	}
}


int WordCounterPool::get_max_phrase(int i, string &e) {
	if (i < 0 || i >= 10 || max_phrase[i] == NULL) {
		return -1;
	}
	else {
		e = max_phrase[i]->dat.first().get_exp() + " " + max_phrase[i]->dat.first().get_exp();
		return max_phrase[i]->count;
	}
}