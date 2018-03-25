#include <iostream>
#include <string>
#include <io.h>

#include "cmd_analyse.h"
#include "traverse_file.h"
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
	else {
		TraverseFile traverse(dir);
		traverse.begin();
		while (traverse.valid()) {
			cout << traverse.get_filepath() << endl;
			traverse.next();
		}
	}

	return 0;
}