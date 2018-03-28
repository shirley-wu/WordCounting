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
extern int word_max_link;
extern int phrase_max_link;
#endif


const int WORD_SIZE			= 1024;
const int PHRASE_SIZE		= WORD_SIZE * 2 + 5;
const int WORD_HASH_SIZE	= 150000;
const int PHRASE_HASH_SIZE	= 2000000;


struct wnode {
	std::string format = "";
	std::string exp = "";
	int count = 0;
	wnode *next = NULL;
#ifdef _CALCULATE_HASH
	int depth;
#endif

	wnode(const std::string& f, const std::string& e) {
		assert(f.size() <= WORD_SIZE);
		assert(e.size() <= WORD_SIZE);
		format = f;
		exp = e;
	}
	~wnode() { if (next) next->~wnode(); }
};


struct pnode {
	const wnode *w1;
	const wnode *w2;
	std::string format;
	int count = 0;
	pnode *next = NULL;
#ifdef _CALCULATE_HASH
	int depth;
#endif

	pnode(const wnode *pw1, const wnode *pw2, const std::string& f) {
		assert(f.size() <= PHRASE_SIZE + 2);
		w1 = pw1;
		w2 = pw2;
		format = f;
	}
	~pnode() { if (next) next->~pnode(); }
};


class WordPool {

private:
	std::string exp_to_format(const std::string& e);
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