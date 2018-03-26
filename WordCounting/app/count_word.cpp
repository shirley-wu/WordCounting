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
	if (exp.size() < 4) {
		if (isbeginner(c)) {
			exp += c;
		}
		else {
			exp = "";
		}
	}
	else {
		if (iscontinuer(c)) {
			exp += c;
		}
		else {
			add_word(exp);
			if (pre != "") add_phrase(pre, exp);
			pre = exp;
			exp = ""; 
		}
	}
	if (c == EOF) {
		pre = "";
		exp = "";
	}
}


int WordCounter::get_max_word(int i, string &e) {
	return _get_max_word(i, e);
}


int WordCounter::get_max_phrase(int i, string &e) {
	return _get_max_phrase(i, e);
}