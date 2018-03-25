#include <iostream>

#include "test.h"

using namespace std;

bool test_all(string &msg, bool if_echo) {
	bool if_pass;

	if_pass = test_cmd_analyse(msg);
	if(if_echo) cout << msg << endl;
	if(!if_pass) return false;

	if_pass = test_count_char(msg);
	if (if_echo) cout << msg << endl;
	if (!if_pass) return false;
	
	return true;
}