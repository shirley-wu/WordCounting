#include <iostream>
#include <string>

#include "cmd_analyse.h"
#include "test.h"

using namespace std;

int main(int argc, char **argv) {
	string dir;
	bool if_test;
	
	if (!analyse_cmd(argc, argv, dir, if_test)) {
		cout << "Invalid command argument";
		return 1;
	}

	// cout << "if_test: " << if_test << endl;
	// cout << "dir: " << dir << endl;
	
	if (if_test) {
		string msg;
		test_all(msg);
	}

	return 0;
}