#pragma once
#include <string>
#include <cstring>
#include <assert.h>

#define _CALCULATE_HASH
#ifdef _CALCULATE_HASH
extern long word_occupied;
extern long word_link;
extern long phrase_occupied;
extern long phrase_link;
extern const int HASH_SIZE;
#endif


const int WORD_SIZE = 100;


struct wnode {
	char format[WORD_SIZE + 2] = "";
	char exp[WORD_SIZE + 2] = "";
	int count = 0;
	wnode *next = NULL;

	wnode(const char* f, const char* e) {
		assert(strlen(f) <= WORD_SIZE);
		assert(strlen(e) <= WORD_SIZE);
		strcpy(format, f);
		strcpy(exp, e);
	}
	~wnode() { if (next) next->~wnode(); }
};


class WordPool {

private:
	void exp_to_format(char f[], const char e[]);

public:
	WordPool();
	~WordPool();
	wnode* add_word(const char* exp);
	void add_phrase(const wnode* pw1, const wnode* pw2);
	int get_max_word(int i, std::string &e);
	int get_max_phrase(int i, std::string &e);
};