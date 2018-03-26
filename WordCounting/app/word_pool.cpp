#include "word_pool.h"

using namespace std;


int WordPool::my_hash(char *s) {
	unsigned long h = 0;
	unsigned long g;
	for (int i = 0; s[i]; i++) {
		h = (h << 4) + s[i];
		g = h & 0xF0000000L;
		if (g) {
			h ^= g >> 24;
			h &= ~g;
		}
	}
	return (h % hash_size);
}


void WordPool::exp_to_format(char f[], const char e[]) {
	int j = strlen(e) - 1;
	while (isdigit(e[j])) j--;
	for (int i = 0; i <= j; i++) f[i] = tolower(e[i]);
	f[j+1] = 0;
}


void WordPool::add_word(string e) {
	char format[word_size];
	const char * exp = e.c_str();
	exp_to_format(format, exp);

	int key = my_hash(format);
	wnode * p = wtable[key];
	if (p) {
		while (strcmp(p->w.format, format) != 0) {
			if (p->next) p = p->next;
			else p = p->next = new wnode(format, exp);
		}
	}
	else p = wtable[key] = new wnode(format, exp);

	p->count++;
	if(strcmp(exp, p->w.exp) < 0) strcpy(p->w.exp, exp);

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


void WordPool::add_phrase(string e1, string e2) {
	const char * exp1 = e1.c_str();
	const char * exp2 = e2.c_str();

	char f1[word_size];
	exp_to_format(f1, exp1);
	char f2[word_size];
	exp_to_format(f2, exp2);

	char f[2 * word_size] = { 0 };
	strcat(f, f1);
	strcat(f, " ");
	strcat(f, f2);

	int key = my_hash(f);
	pnode * p = ptable[key];
	if (p) {
		while (strcmp(p->w1.format, f1) != 0 || strcmp(p->w2.format, f2) != 0) {
			if (p->next) p = p->next;
			else p = p->next = new pnode(f1, exp1, f2, exp2);
		}
	}
	else p = ptable[key] = new pnode(f1, exp1, f2, exp2);

	p->count++;
	if (strcmp(exp1, p->w1.exp) < 0 || (strcmp(exp1, p->w1.exp) == 0 && strcmp(exp2, p->w2.exp) < 0)) {
		strcpy(p->w1.exp, exp1);
		strcpy(p->w2.exp, exp2);
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
		e = string(pmax[i]->w1.exp) + " " + string(pmax[i]->w2.exp);
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