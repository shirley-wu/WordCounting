#include <iostream>
#include <fstream>

#include "word_pool.h"

using namespace std;


#ifdef _CALCULATE_HASH
long word_occupied = 0;
long word_link = 0;
long phrase_occupied = 0;
long phrase_link = 0;
int word_max_link = 0;
int phrase_max_link = 0;
#endif


wnode *wtable[WORD_HASH_SIZE] = { NULL };
const wnode *wmax[10] = { NULL };

pnode *ptable[PHRASE_HASH_SIZE] = { NULL };
const pnode *pmax[10] = { NULL };


bool pool_occupied = false;
bool word_sorted = false;
bool phrase_sorted = false;


int elfhash(const string& s) {
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
	return (h & 0x7FFFFFFF);
}


int jshash(const string& s) {
	int hash = 0;

	for (int i = 0; i < s.size(); i++) {
		hash ^= (hash << 5) + (int)s[i] + (hash >> 2);
	}

	return (hash & 0x7FFFFFFF);
}


int fnvhash(const string& s) {
	int fnvprime = 0x811C9DC5;
	int hash = 0;

	for (int i = 0; i < s.size(); i++) {
		hash *= fnvprime;
		hash ^= (int)s[i];
	}

	return hash & 0x7FFFFFFF;
}


int bknrhash(const string& s){
	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
	unsigned int hash = 0;

	for (int i = 0; i < s.size(); i++) {
		hash = hash * seed + s[i];
	}

	return (hash & 0x7FFFFFFF);
}


int (*my_hash)(const string& s) = jshash;


WordPool::WordPool() {
	assert(pool_occupied == false);
	for (int i = 0; i < WORD_HASH_SIZE; i++) {
		wtable[i] = NULL;
	}
	for (int i = 0; i < PHRASE_HASH_SIZE; i++) {
		ptable[i] = NULL;
	}
	for (int i = 0; i < 10; i++) {
		wmax[i] = NULL;
		pmax[i] = NULL;
	}
	pool_occupied = true;
}


WordPool::~WordPool() {
	for (int i = 0; i < WORD_HASH_SIZE; i++) {
		if (wtable[i]) delete wtable[i];
	}
	for (int i = 0; i < PHRASE_HASH_SIZE; i++) {
		if (ptable[i]) delete ptable[i];
	}
	pool_occupied = false;
	word_sorted = false;
	phrase_sorted = false;
}


string WordPool::exp_to_format(const string& e) {
	string f = "";
	int j = e.size() - 1;
	while (isdigit(e[j])) j--;
	for (int i = 0; i <= j; i++) f += tolower(e[i]);
	return f;
}


wnode * WordPool::add_word(const char * e) {
	if (strlen(e) > WORD_SIZE) return NULL;

	string exp = e;
	string format = exp_to_format(exp);

	int key = my_hash(format) % WORD_HASH_SIZE;
	wnode * p = wtable[key];
	if (p) {
		while (p->format != format) {
			if (p->next) p = p->next;
			else {
#ifdef _CALCULATE_HASH
				int d = p->depth;
#endif
				p = p->next = new wnode(format, exp);
#ifdef _CALCULATE_HASH
				word_link++;
				p->depth = d + 1;
				word_max_link = word_max_link > p->depth ? word_max_link : p->depth;
#endif
			}
		}
	}
	else {
		p = wtable[key] = new wnode(format, exp);
#ifdef _CALCULATE_HASH
		word_occupied++;
		p->depth = 0;
#endif
	}
	p->count++;
	if (p->exp > exp) p->exp = exp;

	return p;
}


void WordPool::add_phrase(const wnode * pw1, const wnode * pw2) {
	if (pw1 == NULL || pw2 == NULL) return;

	string f = pw1->format;
	f += " ";
	f += pw2->format;

	int key = my_hash(f) % PHRASE_HASH_SIZE;
	pnode * p = ptable[key];
	if (p) {
		while (p->format != f) {
			if (p->next) p = p->next;
			else {
#ifdef _CALCULATE_HASH
				int d = p->depth;
#endif
				p = p->next = new pnode(pw1, pw2, f);
#ifdef _CALCULATE_HASH
				phrase_link++;
				p->depth = d + 1;
				phrase_max_link = phrase_max_link > p->depth ? phrase_max_link : p->depth;
#endif
			}
		}
	}
	else {
		p = ptable[key] = new pnode(pw1, pw2, f);
#ifdef _CALCULATE_HASH
		phrase_occupied++;
		p->depth = 0;
#endif
	}
	p->count++;
}


void WordPool::word_sort_insert(const wnode * p) {
	for (int i = 0; i < 10; i++) {
		if (wmax[i] == NULL || wmax[i] == p) {
			wmax[i] = p;
			break;
		}
		else {
			int ci = wmax[i]->count;
			int cp = p->count;
			if ((ci < cp) || (ci == cp && p->format < wmax[i]->format)) {
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
}


void WordPool::word_sort() {
	const wnode * p;
	for (int i = 0; i < WORD_HASH_SIZE; i++) {
		for (p = wtable[i]; p; p = p->next) word_sort_insert(p);
	}
}


int WordPool::get_max_word(int i, string &e){
	if (word_sorted == false) {
		word_sort();
		word_sorted = true;
	}
	if (i < 0 || i >= 10 || wmax[i] == NULL) {
		return -1;
	}
	else {
		e = wmax[i]->exp;
		return wmax[i]->count;
	}
}


void WordPool::phrase_sort_insert(const pnode * p) {
	for (int i = 0; i < 10; i++) {
		if (pmax[i] == NULL || pmax[i] == p) {
			pmax[i] = p;
			return;
		}
		else {
			int ci = pmax[i]->count;
			int cp = p->count;
			if ((ci < cp) || (ci == cp && p->format < pmax[i]->format)) {
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


void WordPool::phrase_sort() {
	const pnode * p;
	for (int i = 0; i < PHRASE_HASH_SIZE; i++) {
		for (p = ptable[i]; p; p = p->next) phrase_sort_insert(p);
	}
}

int WordPool::get_max_phrase(int i, string &e) {
	if (phrase_sorted == false) {
		phrase_sort();
		phrase_sorted = true;
	}
	if (i < 0 || i >= 10 || pmax[i] == NULL) {
		return -1;
	}
	else {
		e = string(pmax[i]->w1->exp) + ' ' + string(pmax[i]->w2->exp);
		return pmax[i]->count;
	}
}