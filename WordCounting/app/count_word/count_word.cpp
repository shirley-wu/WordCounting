#include <iostream>

#include "count_word.h"

using namespace std;


void WordCounter::count(char c) {
	w.affix(c);
	if (w.get_iscomplete()) {
		cout << "exp:\t" << w.get_exp() << endl;
		cout << "word:\t" << w.get_word() << endl;

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