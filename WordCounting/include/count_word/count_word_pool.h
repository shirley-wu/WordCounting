#pragma once
#include <string>

#include "word.h"

// #define _WORD_COUNTER_POOL_TRIE
#define _WORD_COUNTER_POOL_HASH


class WordCounterPool {

private:

#ifdef _WORD_COUNTER_POOL_TRIE

	class WordItem {
		
	private:
		std::string word;
		std::string exp;
		int count;

	public:
		WordItem(std::string w, std::string e);
		void update(std::string e);
		void add();
		int get_count();

	};
	
	class Node {
		
	public:
		Node();
		Node * next[37]; // 0~25: a~z,  26~35: 0~9, 36: parent
		WordItem* word;

	};

	Node* trie;
	Node* locate(string w);

#endif
#ifdef _WORD_COUNTER_POOL_HASH

	template<class T>
	class HashTable {

	private:
		static const int size = 100;
		int hash(std::string s);

		typedef struct node {
			<T> arr[size];
			struct node* next;
		} Node arr[size];

		void release(Node * p);

	public:
		int occupied = 0;
		int redundant = 0;
		// TODO: 两个统计效率用的属性，不计入api。最后应该删除。

		HashTable();
		~HashTable();
		Node * get_node(std::string w, std::string e);

	} word_table, phrase_table;

	Node * max_word[10];
	Node * max_phrase[10];

	void update(Node * arr[], Node * p);

#endif

public:
	WordCounterPool();
	void add_word(Word w);
	void add_phrase(Word w1, Word w2);
	int get_max_word(int i, std::string& e);
	int get_max_phrase(int j, std::string& e);

};