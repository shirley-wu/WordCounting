#pragma once
#include <string>

#include "word.h"


const int size = 100;


template <class T>
struct node {
	T dat;
	int count;
	node * next;
	node(T d) { dat = d; count = 0; next = NULL; }
	void add() { count++; }
};


template <class T>
class HashTable {

private:
	node<T> * arr[size] = { 0 };

public:
	void release(node<T> * p) {
		if (p->next) release(p->next);
		delete p;
	}

	~HashTable() {
		for (int i = 0; i < size; i++) release(arr[i]);
	}

	int hash(std::string s) {
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
		return (h % size);
	}

	node<T>* get_node(std::string key, T dat) {
		int hash_val = hash(key);
		node<T> * p = arr[hash_val];
		if (p) {
			while (!(p->dat == dat)) {
				if (p->next) p = p->next;
				else {
					p = p->next = new node<T>(dat);
					break;
				}
			}
		}
		else {
			p = arr[hash_val] = new node<T>(dat);
		}
		return p;
	}

};


class WordCounterPool {

private:
	HashTable<Word> word_table;
	HashTable<Phrase> phrase_table;

	node<Word> * max_word[10];
	node<Phrase> * max_phrase[10];

	template <class T>
	void update(node<T> *arr[], node<T> * p);

public:
	WordCounterPool();
	void add_word(Word w);
	void add_phrase(Word w1, Word w2);
	int get_max_word(int i, std::string& e);
	int get_max_phrase(int j, std::string& e);

};