#include <string>

#include "cmd_analyse.h"

using namespace std;

bool test_cmd_analyse(string &msg) {
	const int size1 = 8;
	const int size2 = 10;
	int argc;
	char **argv;
	string test_name, dir;
	bool if_test, if_valid, if_pass = false;

	test_name = "cmd_analyse";

	argv = new char*[size1];
	for (int i = 0; i < size1; i++) {
		argv[i] = new char[size2];
	}
	
	do {
		msg = "Do not pass test " + test_name;

		// no argument
		argc = 0;
		if_valid = analyse_cmd(argc, argv, dir, if_test);
		if (if_valid == false && if_test == false);
		else {
			msg += "<no argument>";
			break;
		}

		// inif_valid argument
		argc = 2;
		strcpy(argv[0], "adfla");
		strcpy(argv[1], "-t");
		if_valid = analyse_cmd(argc, argv, dir, if_test);
		if (if_valid == false && if_test == true);
		else {
			msg += "<invalid argument>";
			break;
		}

		// if_valid argument
		argc = 4;
		char test_dir[20] = ".\\user";
		strcpy(argv[2], "-d");
		strcpy(argv[3], test_dir);
		if_valid = analyse_cmd(argc, argv, dir, if_test);
		if (if_valid == true && if_test == true && dir == test_dir);
		else {
			msg += "<valid argument>";
			break;
		}

		if_pass = true;
		msg = "Pass test " + test_name;

	} while (0);

	for (int i = 0; i < size1; i++) delete[] argv[i];
	delete[] argv;
	
	return true;
}