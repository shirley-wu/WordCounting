#pragma once
#include <string>

#include "word_pool.h"


class WordCounter {

private:

	int num = 0;
	std::string pre = "";
	std::string exp = "";

public:
	void count(char c);
	int get_word_num() { return num; }
	int get_max_word(int i, std::string& e);
	int get_max_phrase(int j, std::string& e);

};