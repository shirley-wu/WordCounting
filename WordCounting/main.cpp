#include <iostream>
#include <fstream>
#include <string>

// #define _MY_DEBUG
#define _IO_RESULT

#include "traverse_file.h"
#include "count.h"

using namespace std;

int main(int argc, char **argv) {
	string dir;

	if (argc > 1) dir = string(argv[1]);
	
	Counter counter;
	TraverseFile traverse(dir);

	while (traverse.traverse(), traverse.valid()) {
		fstream in;
		cout << traverse.get_filepath() << endl;
		in.open(traverse.get_filepath());
#ifdef _MY_DEBUG
		cout << traverse.get_filepath() << endl;
		if (in.bad()) {
			cout << traverse.get_filepath() << " bad" << endl;
			cin.get();
		}
#endif
		counter.count(in);
		in.close();
	}

#ifdef _IO_RESULT
	ostream& result = cout;
#else
	ofstream result("result.txt");
#endif
	result << "char_number :" << counter.get_char_num() << endl;
	result << "line_number :" << counter.get_line_num() << endl;
	result << "word_number :" << counter.get_word_num() << endl;
	cout << "\nthe top ten frequency of word :\n";
	for (int i = 0; i < 10; i++) {
		int num;
		string s;
		num = counter.get_max_word(i, s);
		if (num <= 0) break;
		result << s << '\t' << num << endl;
	}
	cout << "\n\nthe top ten frequency of phrase :";
	for (int i = 0; i < 10; i++) {
		int num;
		string s;
		num = counter.get_max_phrase(i, s);
		if (num <= 0) break;
		result << s << "\t\t" << num << endl;
	}

	return 0;
}