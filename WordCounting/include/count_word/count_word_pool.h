#pragma once
#include "word.h"


class WordCounterPool {

public:
	void add_word(Word w);
	void add_phrase(Word w1, Word w2);

};