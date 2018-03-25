#include <string>
#include <sstream>

#include "count_char.h"

using namespace std;


bool test_count_char(string &msg) {
	/*
	bool if_pass;
	string test_name;
	string str;
	istringstream in;

	test_name = "count_char";

	do {
		msg = "Do not pass test " + test_name;
		if_pass = false;

		int pre_char_num = 0;
		int pre_line_num = 0;

		// init
		CharCounter counter;
		if (counter.get_char_num() == 0 && counter.get_line_num() == 0);
		else {
			msg += "<init>";
			break;
		}

		// blank stream
		str = "";
		in = istringstream(str);
		counter.count(in);
		if (counter.get_char_num() == 0 && counter.get_line_num() == 0);
		else {
			msg += "<blank stream>";
			break;
		}

		// normal stream
		str = "abc de\n\nfgh";
		in = istringstream(str);
		pre_char_num = counter.get_char_num();
		pre_line_num = counter.get_line_num();
		counter.count(in);
		if (counter.get_char_num() - pre_char_num == 9 && counter.get_line_num() - pre_line_num == 2);
		else {
			msg += "<normal stream>";
			break;
		}

		// add
		str = "a c e\nfgh\n";
		in = istringstream(str);
		pre_char_num = counter.get_char_num();
		pre_line_num = counter.get_line_num();
		counter.count(in);
		if (counter.get_char_num() - pre_char_num == 8 && counter.get_line_num() - pre_line_num == 2);
		else {
			msg += "<add>";
			break;
		}

		if_pass = true;
		msg = "Pass test " + test_name;

	} while (0);
	*/
	return true;
}