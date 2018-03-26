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
	void clear();

	bool get_isvalid();
	bool get_iscomplete();

	std::string get_word();
	std::string get_exp();

	void affix(char c);
	void update(string e);

};