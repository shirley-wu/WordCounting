#pragma once
#include <iostream>

class CharCounter {

private:
	int char_num;
	int line_num;

public:
	CharCounter();
	void clear();
	bool count(std::istream& in);
	int get_char_num();
	int get_line_num();

};