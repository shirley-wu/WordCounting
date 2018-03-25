#include "count.h"

using namespace std;


bool Counter::count(istream& in) {
	if (in.bad()) return false;

	char c;
	do{
		c = in.get();
		cc.count(c);
		wc.count(c);
	}while (c != EOF);

	return true;
}


int Counter::get_char_num() {
	return cc.get_char_num();
}


int Counter::get_line_num() {
	return cc.get_line_num();
}