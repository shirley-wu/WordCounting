#include <fstream>

#include "count.h"

using namespace std;


bool Counter::count(string filepath) {
	ifstream in;
	in.open(filepath.c_str());
	if (in.bad()) return false;

	char c;
	do{
		c = in.get();
		cc.count(c);
		wc.count(c);
	}while (c != EOF);

	return true;
}


int Counter::get_char_num() {
	return cc.get_char_num();
}


int Counter::get_line_num() {
	return cc.get_line_num();
}


int Counter::get_word_num() {
	return wc.get_word_num();
}


int Counter::get_max_word(int i, string &e) {
	return wc.get_max_word(i, e);
}


int Counter::get_max_phrase(int i, string &e) {
	return wc.get_max_phrase(i, e);
}