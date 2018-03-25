#pragma once
#include <istream>

#include "count_char.h"

class Counter {

private:
	CharCounter cc;

public:
	bool count(std::istream& in);
	int get_char_num();
	int get_line_num();

};