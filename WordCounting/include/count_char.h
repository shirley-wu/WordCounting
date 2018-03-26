#pragma once

class CharCounter {

private:
	int char_num;
	int line_num;

public:
	CharCounter();
	void count(char c);
	int get_char_num();
	int get_line_num();

};