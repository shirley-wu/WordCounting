#include <stdio.h>	// for I have to include EOF. but this seems ugly.

#include "count_char.h"

using namespace std;


CharCounter::CharCounter() {
	char_num = 0;
	line_num = 0;
}


void CharCounter::count(char c) {
	// TODO: different from official
	if (c == EOF) {
		line_num++;
	}
	else if( c == '\n') {
		line_num++;
	}
	else if(c >= 32 && c <= 126) {
		char_num++;
	}
}


int CharCounter::get_char_num() {
	return char_num;
}


int CharCounter::get_line_num() {
	return line_num;
}