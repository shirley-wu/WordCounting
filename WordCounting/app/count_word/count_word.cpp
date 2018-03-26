#include <iostream>

#include "count_word.h"

using namespace std;


void WordCounter::count(char c) {
	w.affix(c);
	if (w.get_iscomplete()) {
		cout << "exp:\t" << w.get_exp() << endl;
		cout << "word:\t" << w.get_word() << endl;

		num++;
		pool.add_word(w);
		if (prew.get_iscomplete()) {
			pool.add_phrase(prew, w);
		}

		prew = w;
		w.clear();
	}
	if (c == EOF) {
		prew.clear();
		w.clear();
	}
}


int WordCounter::get_word_num() {
	return num;
}


int WordCounter::get_max_word(int i, string &e) {
	return pool.get_max_word(i, e);
}


int WordCounter::get_max_phrase(int i, string &e) {
	return pool.get_max_phrase(i, e);
}