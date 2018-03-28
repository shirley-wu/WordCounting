#include <iostream>

#include "count_word.h"

using namespace std;


bool isbeginner(char c) {
	return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}


bool isdivisor(char c) {
	return !((('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9')));
}


void WordCounter::count(char c) {
	if (overflow) {
		if (isdivisor(c)) {
			exp_len = 0;
			overflow = false;
		}
	}
	else if (exp_len < 4) {
		if (exp_len == 0 && !pre_divisor) ;
		else if (isbeginner(c)) {
			exp[exp_len++] = c;
		}
		else {
			exp_len = 0;
		}
	}
	else {
		if (isdivisor(c)) {
			num++;
			exp[exp_len] = 0;
			pre = now;
			now = pool.add_word(exp);
			if (pre) pool.add_phrase(pre, now);
			exp_len = 0;
		}
		else {
			if (exp_len > WORD_SIZE) {
				overflow = true;
			}
			else exp[exp_len++] = c;
		}
	}
	pre_divisor = isdivisor(c);
}


void WordCounter::count_eof() {
	exp[0] = 0;
	exp_len = 0;
	overflow = false;
	pre = NULL;
	now = NULL;
}


int WordCounter::get_max_word(int i, string &e) {
	return pool.get_max_word(i, e);
}


int WordCounter::get_max_phrase(int i, string &e) {
	return pool.get_max_phrase(i, e);
}