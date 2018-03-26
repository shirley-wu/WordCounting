#pragma once
#include <istream>

#include "count_char.h"
#include "count_word.h"

class Counter {

private:
	CharCounter cc;
	WordCounter wc;

public:
	bool count(std::istream& in);
	int get_char_num();
	int get_line_num();
	int get_word_num();
	int get_max_word(int i, std::string& e);
	int get_max_phrase(int j, std::string& e);

};