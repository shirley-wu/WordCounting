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
#endif


const int WORD_SIZE = 100;
const int PHRASE_SIZE = WORD_SIZE * 2 + 5;
const int HASH_SIZE = 10000000;


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


struct pnode {
	const wnode *w1;
	const wnode *w2;
	char format[PHRASE_SIZE + 2];
	int count = 0;
	pnode *next = NULL;

	pnode(const wnode *pw1, const wnode *pw2, const char * f) {
		assert(strlen(f) <= PHRASE_SIZE + 2);
		w1 = pw1;
		w2 = pw2;
		strcpy(format, f);
	}
	~pnode() { if (next) next->~pnode(); }
};


class WordPool {

private:
	void exp_to_format(char f[], const char e[]);
	void word_sort_insert(const wnode * p);
	void word_sort();
	void phrase_sort_insert(const pnode * p);
	void phrase_sort();

public:
	WordPool();
	~WordPool();
	wnode* add_word(const char* exp);
	void add_phrase(const wnode* pw1, const wnode* pw2);
	int get_max_word(int i, std::string &e);
	int get_max_phrase(int i, std::string &e);
};