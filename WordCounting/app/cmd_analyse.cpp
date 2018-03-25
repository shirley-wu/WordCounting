#include <cstring>
#include "cmd_analyse.h"

using namespace std;

// if_test сеохсз dir
bool analyse_cmd(int argc, char **argv, bool& if_test, string &dir) {
	bool valid = false;
	if_test = false;
	dir = "";
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-d") == 0 && i + 1 < argc) {
			i++;
			dir = argv[i];
			valid = true;
		}
		else if (strcmp(argv[i], "-t") == 0) {
			if_test = true;
			valid = true;
		}
	}
	return valid;
}