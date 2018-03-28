#include <iostream>
#include <cstdio>
#include <string>
#include <time.h>

#include "traverse_file.h"
#include "count.h"

// #define _IO_DEBUG
#define _IO_RESULT
#define _CALCULATE_TIME

using namespace std;

int main(int argc, char **argv) {
#ifdef _CALCULATE_TIME
	clock_t start, finish;
	start = clock();
#endif
	string dir;

	if (argc > 1) dir = string(argv[1]);
	else return 1;
	
	Counter counter;
	TraverseFile traverse(dir);

	while (traverse.traverse(), traverse.valid()) {
		string filepath = traverse.get_filepath();
#ifdef _IO_DEBUG
		cout << filepath << endl;
#endif
		counter.count(filepath);
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
	cout << "\nthe top ten frequency of phrase :\n";
	for (int i = 0; i < 10; i++) {
		int num;
		string s;
		num = counter.get_max_phrase(i, s);
		if (num <= 0) break;
		result << s << "\t" << num << endl;
	}

#ifdef _CALCULATE_HASH
	printf("\n\n\nhash situation\n");
	printf("\nword:\n");
	printf("occupied %d, link %d\n", word_occupied, word_link);
	printf("rate of occupation: %f\n", (double)word_occupied / WORD_HASH_SIZE);
	printf("average length of link: %f\n", (double)word_link / word_occupied);
	printf("max link length: %d\n", word_max_link);
	printf("\nphrase:\n");
	printf("occupied %d, link %d\n", phrase_occupied, phrase_link);
	printf("rate of occupation: %f\n", (double)phrase_occupied / PHRASE_HASH_SIZE);
	printf("average length of link: %f\n", (double)phrase_link / phrase_occupied);
	printf("max link length: %d\n", phrase_max_link);
#endif

#ifdef _CALCULATE_TIME
	finish = clock();
	cout << "\n\n\ntime situation\n";
	printf("%f seconds\n", (double)(finish - start)/ CLOCKS_PER_SEC);
#endif

	return 0;
}