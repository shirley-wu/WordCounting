#include <cstring>
#include "cmd_analyse.h"

using namespace std;

bool analyse_cmd(int argc, char **argv, string &dir, bool &if_test) {
	bool hasDir = false;
	if_test = false;
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-d") == 0 && i + 1 < argc) {
			i++;
			dir = argv[i];
			hasDir = true;
		}
		else if (strcmp(argv[i], "-t") == 0) {
			if_test = true;
		}
	}
	return hasDir;
}