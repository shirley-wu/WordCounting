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