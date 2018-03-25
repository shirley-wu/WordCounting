#include "count_char.h"

using namespace std;


CharCounter::CharCounter() {
	char_num = 0;
	line_num = 0;
}


void CharCounter::clear() {
	char_num = 0;
	line_num = 0;
}


bool CharCounter::count(istream& in) {
	if (in.bad()) return false;

	bool is_line = false;
	char c;
	while (c = in.get(), c != EOF) {
		if (c != '\n') {
			char_num++;
			is_line = true;
		}
		else if (is_line) {
			line_num++;
			is_line = false;
		}
	}
	if (is_line) line_num++;

	return true;
}


int CharCounter::get_char_num() {
	return char_num;
}


int CharCounter::get_line_num() {
	return line_num;
}