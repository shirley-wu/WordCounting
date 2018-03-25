#include <stdio.h>	// for I have to include EOF. but this seems ugly.

#include "count_char.h"

using namespace std;


CharCounter::CharCounter() {
	char_num = 0;
	line_num = 0;
	is_line = false;
}


void CharCounter::count(char c) {
	if (c == EOF) {
		if (is_line) {
			line_num++;
			is_line = false;
		}
	}
	else if( c == '\n') {
		if (is_line) {
			line_num++;
			is_line = false;
		}
	}
	else {
		char_num++;
		is_line = true;
	}
}


int CharCounter::get_char_num() {
	return char_num;
}


int CharCounter::get_line_num() {
	return line_num;
}