#include "word_pool.h"

using namespace std;


int WordPool::my_hash(std::string s) {
	unsigned long h = 0;
	unsigned long g;
	for (int i = 0; i < s.size(); i++) {
		h = (h << 4) + s[i];
		g = h & 0xF0000000L;
		if (g) {
			h ^= g >> 24;
			h &= ~g;
		}
	}
	return (h % hash_size);
}


string WordPool::exp_to_format(string exp) {
	string word = "";
	int j = exp.size() - 1;
	while (isdigit(exp[j])) j--;
	for (int i = 0; i <= j; i++) word += tolower(exp[i]);
	return word;
}


void WordPool::add_word(string exp) {
	string format = exp_to_format(exp);

	int key = my_hash(format);
	wnode * p = wtable[key];
	if (p) {
		while (p->w.format != format) {
			if (p->next) p = p->next;
			else p = p->next = new wnode(format, exp);
		}
	}
	else p = wtable[key] = new wnode(format, exp);

	p->count++;
	if(exp < p->w.exp) p->w.exp = exp;

	for (int i = 0; i < 10; i++) {
		if (wmax[i] == NULL || wmax[i] == p) {
			wmax[i] = p;
			return;
		}
		else {
			int ci = wmax[i]->count;
			int cp = p->count;
			if ((ci < cp) || (ci == cp && p->w < wmax[i]->w)) {
				int j;
				for (j = i; j < 10 - 1; j++) if (wmax[j] == p) break;
				for (; j > i; j--) {
					wmax[j] = wmax[j - 1];
				}
				wmax[i] = p;
				return;
			}
		}
	}
}


void WordPool::add_phrase(string exp1, string exp2) {
	string f1 = exp_to_format(exp1);
	string f2 = exp_to_format(exp2);
	string f = f1 + " " + f2;

	int key = my_hash(f);
	pnode * p = ptable[key];
	if (p) {
		while (p->w1.format != f1 || p->w2.format != f2) {
			if (p->next) p = p->next;
			else p = p->next = new pnode(f1, exp1, f2, exp2);
		}
	}
	else p = ptable[key] = new pnode(f1, exp1, f2, exp2);

	p->count++;
	if (exp1 < p->w1.exp || (exp1 == p->w1.exp && exp2 < p->w2.exp)) {
		p->w1.exp = exp1;
		p->w2.exp = exp2;
	}

	for (int i = 0; i < 10; i++) {
		if (pmax[i] == NULL || pmax[i] == p) {
			pmax[i] = p;
			return;
		}
		else {
			int ci = pmax[i]->count;
			int cp = p->count;
			if ((ci < cp) || (ci == cp && ((p->w1 < pmax[i]->w1) || (p->w1 == pmax[i]->w1 && p->w2 < pmax[i]->w2)))) {
				int j;
				for (j = i; j < 10 - 1; j++) if (pmax[j] == p) break;
				for (; j > i; j--) {
					pmax[j] = pmax[j - 1];
				}
				pmax[i] = p;
				return;
			}
		}
	}
}


int WordPool::get_max_word(int i, string &e){
	if (i < 0 || i >= 10 || wmax[i] == NULL) {
		return -1;
	}
	else {
		e = wmax[i]->w.exp;
		return wmax[i]->count;
	}
}


int WordPool::get_max_phrase(int i, string &e) {
	if (i < 0 || i >= 10 || pmax[i] == NULL) {
		return -1;
	}
	else {
		e = pmax[i]->w1.exp + " " + pmax[i]->w2.exp;
		return pmax[i]->count;
	}
}


WordPool::WordPool() {
	for (int i = 0; i < hash_size; i++) {
		wtable[i] = NULL;
		ptable[i] = NULL;
	}
	for (int i = 0; i < 10; i++) {
		wmax[i] = NULL;
		pmax[i] = NULL;
	}
}

WordPool::~WordPool() {
	for (int i = 0; i < hash_size; i++) {
		if (wtable[i]) delete wtable[i];
		if (ptable[i]) delete ptable[i];
	}
}