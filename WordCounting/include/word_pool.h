#pragma once
#include <string>
#include <cstring>

const int WORD_SIZE = 20;

class WordPool {

private:
	void exp_to_format(char f[], const char e[]);

public:
	WordPool();
	~WordPool();
	void add_word(const char* exp);
	void add_phrase(const char* exp1, const char* exp2);
	int get_max_word(int i, std::string &e);
	int get_max_phrase(int i, std::string &e);
};