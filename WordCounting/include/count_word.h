#pragma once
#include <string>

#include "count_word/word.h"
#include "count_word/count_word_pool.h"



class WordCounter {

private:

	Word w, prew;
	WordCounterPool pool;

public:
	void count(char c);

};