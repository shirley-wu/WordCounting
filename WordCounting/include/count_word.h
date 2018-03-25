#pragma once
#include <string>


class Word {

private:
	bool is_valid;
	bool is_complete;
	std::string word;
	std::string exp;

public:
	Word();
	bool get_isvalid();
	bool get_iscomplete();
	std::string get_word();
	std::string get_exp();
	void clear();
	void affix(char c);

};


class WordCounterPool {

public:
	void add_word(Word w);
	void add_phrase(Word w1, Word w2);

};


class WordCounter {

private:

	Word w, prew;
	WordCounterPool pool;

public:
	void count(char c);

};