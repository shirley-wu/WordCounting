#pragma once
#include <string>
#include <cstring>

const int WORD_SIZE = 20;


class WordPool {

private:
	static const int PHRASE_SIZE = WORD_SIZE * 2 + 5;
	static const int HASH_SIZE = 100;

	struct wnode {
		char format[WORD_SIZE + 2] = { 0 };
		char exp[WORD_SIZE + 2] = { 0 };
		int count = 0;
		wnode *next = NULL;

		wnode(const char* f, const char* e) {
			if (strlen(f) < WORD_SIZE || strlen(e) < WORD_SIZE) {
				strcpy(format, f);
				strcpy(exp, e);
			}
		}
		~wnode() { if (next) next->~wnode(); }
	};
	wnode *wtable[HASH_SIZE] = { NULL };
	wnode *wmax[10] = { NULL };

	struct pnode {
		char format[PHRASE_SIZE + 2] = { 0 };
		char exp[PHRASE_SIZE + 2] = { 0 };
		int count = 0;
		pnode *next = NULL;

		pnode(const char* f, const char* e) {
			if (strlen(f) < PHRASE_SIZE || strlen(e) < PHRASE_SIZE) {
				strcpy(format, f);
				strcpy(exp, e);
			}
		}
		~pnode() { if (next) next->~pnode(); }
	};
	pnode *ptable[HASH_SIZE] = { NULL };
	pnode *pmax[10] = { NULL };

	bool yes = false;

	int my_hash(char* s);
	void exp_to_format(char f[], const char e[]);

public:
	WordPool();
	~WordPool();
	void add_word(std::string e);
	void add_phrase(std::string e1, std::string e2);
	int get_max_word(int i, std::string &e);
	int get_max_phrase(int i, std::string &e);
};