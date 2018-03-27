#pragma once
#include <string>

#include "word_pool.h"


class WordCounter {

private:

	int num = 0;
	wnode *pre = NULL;
	wnode *now = NULL;

	char exp[WORD_SIZE + 2] = "";
	int exp_len = 0;
	bool overflow = false;

	WordPool pool;

public:
	void count(char c);
	int get_word_num() { return num; }
	int get_max_word(int i, std::string& e);
	int get_max_phrase(int j, std::string& e);

};