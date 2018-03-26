#pragma once
#include <string>

#include "count_word/word.h"
#include "count_word/count_word_pool.h"



class WordCounter {

private:

	int num = 0;
	Word w, prew;
	WordCounterPool pool;

public:
	void count(char c);
	int get_word_num();
	int get_max_word(int i, std::string& e);
	int get_max_phrase(int j, std::string& e);

};