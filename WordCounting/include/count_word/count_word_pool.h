#pragma once
#include <string>

#include "word.h"

#define _WORD_COUNTER_POOL_TRIE


#ifdef _WORD_COUNTER_POOL_TRIE

class WordCounterPool {

private:

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

public:
	void add_word(Word w);
	void add_phrase(Word w1, Word w2);

};

#endif