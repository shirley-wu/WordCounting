#pragma once
#include <string>


class WordPool {

private:
	static const int hash_size = 100;

	struct word {
		std::string format;
		std::string exp;
		word(std::string f = "", std::string e = "") { format = f; exp = e; }
		bool operator<(const word& w) const { return format < w.format; }
		bool operator==(const word& w) const { return format == w.format; }
	};

	struct wnode {
		word w;
		int count;
		wnode *next;
		wnode(std::string f = "", std::string e = "") { w = word(f, e); count = 0; next = NULL; }
		~wnode() { if (next) next->~wnode(); }
	};
	wnode *wtable[hash_size] = { NULL };
	wnode *wmax[10] = { NULL };

	struct pnode {
		word w1;
		word w2;
		int count;
		pnode *next;
		pnode(std::string f1 = "", std::string e1 = "", std::string f2 = "", std::string e2 = "") { w1 = word(f1, e1); w2 = word(f2, e2); count = 0; next = NULL; }
		~pnode() { if (next)next->~pnode(); }
	};
	pnode *ptable[hash_size] = { NULL };
	pnode *pmax[10] = { NULL };

	bool yes = false;

	int my_hash(std::string s);
	std::string exp_to_format(std::string exp);

public:
	WordPool();
	~WordPool();
	void add_word(std::string exp);
	void add_phrase(std::string exp1, std::string exp2);
	int get_max_word(int i, std::string &e);
	int get_max_phrase(int i, std::string &e);
};