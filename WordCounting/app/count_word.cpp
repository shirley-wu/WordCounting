#include <iostream>

#include "count_word.h"

using namespace std;


bool isbeginner(char c) {
	return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}


bool iscontinuer(char c) {
	return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9'));
}


void WordCounter::count(char c) {
	if (overflow) {
		if (!iscontinuer(c)) {
			exp_len = 0;
			overflow = false;
		}
	}
	else if (exp_len < 4) {
		if (isbeginner(c)) {
			exp[exp_len++] = c;
		}
		else {
			exp_len = 0;
		}
	}
	else {
		if (iscontinuer(c)) {
			if (exp_len > WORD_SIZE) {
				overflow = true;
			}
			else exp[exp_len++] = c;
		}
		else {
			num++;
			exp[exp_len] = 0;
			pool.add_word(exp);
			if (strlen(pre) > 0) pool.add_phrase(pre, exp);
			strcpy(pre, exp);
			exp_len = 0;
		}
	}
	if (c == EOF) {
		pre[0] = 0;
		exp[0] = 0;
		exp_len = 0;
		overflow = false;
	}
}


int WordCounter::get_max_word(int i, string &e) {
	return pool.get_max_word(i, e);
}


int WordCounter::get_max_phrase(int i, string &e) {
	return pool.get_max_phrase(i, e);
}