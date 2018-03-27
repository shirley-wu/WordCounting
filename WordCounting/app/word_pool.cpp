#include <assert.h>
#include <iostream>

#include "word_pool.h"

using namespace std;


#ifdef _CALCULATE_HASH
long word_occupied = 0;
long word_link = 0;
long phrase_occupied = 0;
long phrase_link = 0;
#endif


const int PHRASE_SIZE = WORD_SIZE * 2 + 5;
const int HASH_SIZE = 10000000;


struct wnode {
	char format[WORD_SIZE + 2] = "";
	char exp[WORD_SIZE + 2] = "";
	int count = 0;
	wnode *next = NULL;

	wnode(const char* f, const char* e) {
		if (strlen(f) <= WORD_SIZE || strlen(e) <= WORD_SIZE) {
			strcpy(format, f);
			strcpy(exp, e);
		}
	}
	~wnode() { if (next) next->~wnode(); }
};
wnode *wtable[HASH_SIZE] = { NULL };
wnode *wmax[10] = { NULL };


struct pnode {
	char format[PHRASE_SIZE + 2] = "";
	char exp[PHRASE_SIZE + 2] = "";
	int count = 0;
	pnode *next = NULL;

	pnode(const char* f, const char* e) {
		if (strlen(f) <= PHRASE_SIZE || strlen(e) <= PHRASE_SIZE) {
			strcpy(format, f);
			strcpy(exp, e);
		}
	}
	~pnode() { if (next) next->~pnode(); }
};
pnode *ptable[HASH_SIZE] = { NULL };
pnode *pmax[10] = { NULL };


bool pool_occupied = false;


int my_hash(char *s) {
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
	return (h % HASH_SIZE);
}


WordPool::WordPool() {
	assert(pool_occupied == false);
	for (int i = 0; i < HASH_SIZE; i++) {
		wtable[i] = NULL;
		ptable[i] = NULL;
	}
	for (int i = 0; i < 10; i++) {
		wmax[i] = NULL;
		pmax[i] = NULL;
	}
	pool_occupied = true;
}


WordPool::~WordPool() {
	for (int i = 0; i < HASH_SIZE; i++) {
		if (wtable[i]) delete wtable[i];
		if (ptable[i]) delete ptable[i];
	}
	pool_occupied = false;
}


void WordPool::exp_to_format(char f[], const char e[]) {
	int j = strlen(e) - 1;
	while (isdigit(e[j])) j--;
	for (int i = 0; i <= j; i++) f[i] = tolower(e[i]);
	f[j+1] = 0;
}


void WordPool::add_word(const char * exp) {
	if (strlen(exp) > WORD_SIZE) return;

	char format[WORD_SIZE + 2];
	exp_to_format(format, exp);

	int key = my_hash(format);
	wnode * p = wtable[key];
	if (p) {
		while (strcmp(p->format, format) != 0) {
			if (p->next) p = p->next;
			else {
				p = p->next = new wnode(format, exp);
#ifdef _CALCULATE_HASH
				word_link++;
#endif
			}
		}
	}
	else {
		p = wtable[key] = new wnode(format, exp);
#ifdef _CALCULATE_HASH
		word_occupied++;
#endif
	}
	/*if (strlen(p->format) == 0) {
		cout << "\nformat zero" << endl;
		if (strlen(p->exp) == 0) {
			cout << "exp also zero" << endl;
		}
		else cout << p->exp << endl;
	}
	else if (strlen(p->exp) == 0) {
		cout << "\nexp zero" << endl;
		cout << p->format << endl;
	}
	else cout << p->format << " ";*/
	assert(strlen(p->format) > 0);
	assert(strlen(p->exp) > 0);

	p->count++;
	if(strcmp(p->exp, exp) > 0) strcpy(p->exp, exp);

	for (int i = 0; i < 10; i++) {
		if (wmax[i] == NULL || wmax[i] == p) {
			wmax[i] = p;
			return;
		}
		else {
			int ci = wmax[i]->count;
			int cp = p->count;
			if ((ci < cp) || (ci == cp && strcmp(p->exp, wmax[i]->exp) < 0)) {
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


void WordPool::add_phrase(const char* exp1, const char *exp2) {
	if (strlen(exp1) > WORD_SIZE || strlen(exp2) > WORD_SIZE) {
		return;
	}

	char f1[WORD_SIZE + 2];
	exp_to_format(f1, exp1);
	char f2[WORD_SIZE + 2];
	exp_to_format(f2, exp2);

	char f[PHRASE_SIZE + 2] = { 0 };
	char e[PHRASE_SIZE + 2] = { 0 };
	strcat(f, f1); strcat(f, " "); strcat(f, f2);
	strcat(e, exp1); strcat(e, " "); strcat(e, exp2);

	int key = my_hash(f);
	pnode * p = ptable[key];
	if (p) {
		while (strcmp(p->format, f) != 0) {
			if (p->next) p = p->next;
			else {
				p = p->next = new pnode(f, e);
#ifdef _CALCULATE_HASH
				phrase_link++;
#endif
			}
		}
	}
	else {
		p = ptable[key] = new pnode(f, e);
#ifdef _CALCULATE_HASH
		phrase_occupied++;
#endif
	}
	assert(strlen(p->format) > 0);
	assert(strlen(p->exp) > 0);

	p->count++;
	if (strcmp(p->exp, e) > 0) strcpy(p->exp, e);

	for (int i = 0; i < 10; i++) {
		if (pmax[i] == NULL || pmax[i] == p) {
			pmax[i] = p;
			return;
		}
		else {
			int ci = pmax[i]->count;
			int cp = p->count;
			if ((ci < cp) || (ci == cp && strcmp(p->format, pmax[i]->format) < 0)) {
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
		e = wmax[i]->exp;
		return wmax[i]->count;
	}
}


int WordPool::get_max_phrase(int i, string &e) {
	if (i < 0 || i >= 10 || pmax[i] == NULL) {
		return -1;
	}
	else {
		e = pmax[i]->exp;
		return pmax[i]->count;
	}
}