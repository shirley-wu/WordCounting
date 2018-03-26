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


std::string exp_to_word(std::string exp);