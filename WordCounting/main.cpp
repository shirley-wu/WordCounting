#include <iostream>
#include <fstream>
#include <string>

#define _DEBUG

#include <cmd_analyse.h>
#include "traverse_file.h"
#include "count.h"
#include "test.h"

using namespace std;

int main(int argc, char **argv) {
	string dir;
	bool if_test;

	if (!analyse_cmd(argc, argv, if_test, dir)) {
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
		Counter counter;
		TraverseFile traverse(dir);

		while (traverse.valid()) {
			traverse.traverse();
			fstream in;
			in.open(traverse.get_filepath());
#ifdef _DEBUG
			cout << traverse.get_filepath() << endl;
			if (in.bad()) {
				cout << traverse.get_filepath() << " bad" << endl;
				cin.get();
			}
#endif
			counter.count(in);
			in.close();
		}

#ifdef _DEBUG
		cout << "char_number :" << counter.get_char_num() << endl;
		cout << "line_number :" << counter.get_line_num() << endl;
#else
		ofstream result("result.txt");
		result << "char_number :" << counter.get_char_num() << endl;
		result << "line_number :" << counter.get_line_num() << endl;
#endif

	}

	return 0;
}