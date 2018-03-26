#pragma once
#include <string>
#include <cstring>

const int word_size = 100;


class WordPool {

private:
	static const int hash_size = 100;

	struct word {
		char format[word_size];
		char exp[word_size];
		word(const char * f = NULL, const char * e = NULL) {
			if (f && e) {
				strcpy(format, f);
				strcpy(exp, e);
			}
			else {
				format[0] = 0;
				exp[0] = 0;
			}
		}
		bool operator<(const word& w) const {
			return strcmp(format, w.format) < 0;
		}
		bool operator==(const word& w) const {
			return strcmp(format, w.format) == 0;
		}
	};

	struct wnode {
		word w;
		int count = 0;
		wnode *next = NULL;
		wnode(const char* f, const char* e) { w = word(f, e); }
		~wnode() { if (next) next->~wnode(); }
	};
	wnode *wtable[hash_size] = { NULL };
	wnode *wmax[10] = { NULL };

	struct pnode {
		word w1;
		word w2;
		int count = 0;
		pnode *next = NULL;
		pnode(const char* f1, const char* e1, const char* f2, const char* e2) {
			w1 = word(f1, e1);
			w2 = word(f2, e2);
		}
		~pnode() { if (next) next->~pnode(); }
	};
	pnode *ptable[hash_size] = { NULL };
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