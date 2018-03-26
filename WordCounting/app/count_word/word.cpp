#include <iostream>
#include <ctype.h>
#include <assert.h>

#include "count_word.h"
#include "count_word/word.h"

using namespace std;


Word::Word() {
	clear();
}


bool Word::get_isvalid() {
	return is_valid;
}


bool Word::get_iscomplete() {
	return is_complete;
}


string Word::get_word() {
	return word;
}


string Word::get_exp() {
	return exp;
}


void Word::clear() {
	is_valid = false;
	is_complete = false;
	word = "";
	exp = "";
}


bool isbeginner(char c) {
	return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}

bool iscontinuer(char c) {
	return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9'));
}


string exp_to_word(string exp) {
	string word;
	int j = exp.size() - 1;
	while (isdigit(exp[j])) j--;
	word = "";
	for (int i = 0; i <= j; i++) word += tolower(exp[i]);
	return word;
}


void Word::affix(char c) {
	if (is_complete) {
		cout << "trouble in void Word::affix" << endl;
		cin.get();
		return;
	}
	else if (exp.size() < 4) {
		if (isbeginner(c)) {
			exp += c;
			is_valid = exp.size() == 4;
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
			word = exp_to_word(exp);
			is_complete = true;
		}
	}
}


void Word::update(string s) {
	assert(exp_to_word(s) == word);
	exp = exp < s ? exp : s;
}