#include <iostream>
#include <fstream>

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


wnode *wtable[HASH_SIZE] = { NULL };
wnode *wmax[10] = { NULL };

pnode *ptable[HASH_SIZE] = { NULL };
pnode *pmax[10] = { NULL };


bool pool_occupied = false;


int my_hash(const char *s) {
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


wnode * WordPool::add_word(const char * exp) {
	if (strlen(exp) > WORD_SIZE) return NULL;

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

	p->count++;
	if(strcmp(p->exp, exp) > 0) strcpy(p->exp, exp);

	for (int i = 0; i < 10; i++) {
		if (wmax[i] == NULL || wmax[i] == p) {
			wmax[i] = p;
			break;
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
				break;
			}
		}
	}

	return p;
}


void WordPool::add_phrase(const wnode * pw1, const wnode * pw2) {
	if (pw1 == NULL || pw2 == NULL) return;

	char f[PHRASE_SIZE + 2] = "";
	strcat(f, pw1->format);
	strcat(f, " ");
	strcat(f, pw2->format);

	int key = my_hash(f);
	pnode * p = ptable[key];
	if (p) {
		while (strcmp(p->format, f) != 0) {
			if (p->next) p = p->next;
			else {
				p = p->next = new pnode(pw1, pw2, f);
#ifdef _CALCULATE_HASH
				phrase_link++;
#endif
			}
		}
	}
	else {
		p = ptable[key] = new pnode(pw1, pw2, f);
#ifdef _CALCULATE_HASH
		phrase_occupied++;
#endif
	}

	p->count++;

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
		e = string(pmax[i]->w1->exp) + ' ' + string(pmax[i]->w2->exp);
		return pmax[i]->count;
	}
}