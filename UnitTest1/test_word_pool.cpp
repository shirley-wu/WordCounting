#include "stdafx.h"
#include "CppUnitTest.h"

#include <string>

#include "word_pool.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTest1
{		
	TEST_CLASS(TestWordPool)
	{
	private:
		WordPool pool;

	public:

		TEST_METHOD(TestEmpty) {
			string s;
			for (int i = 0; i < 10; i++) {
				int n;
				n = pool.get_max_word(i, s);
				Assert::AreEqual(n, -1);
				n = pool.get_max_phrase(i, s);
				Assert::AreEqual(n, -1);
			}
		}

		TEST_METHOD(TestOneWord)
		{
			string s = "heLlo";
			pool.add_word(s.c_str());
			int n = pool.get_max_word(0, s);
			Assert::AreEqual(string("heLlo"), s);
			Assert::AreEqual(1, n);
			for (int i = 1; i < 10; i++) {
				int n;
				n = pool.get_max_word(i, s);
				Assert::AreEqual(-1, n);
			}
			for (int i = 0; i < 10; i++) {
				int n;
				n = pool.get_max_phrase(i, s);
				Assert::AreEqual(-1, n);
			}
		}

		TEST_METHOD(TestSameWord) {
			wnode *w11, *w12, *w21, *w22, *w31, *w32;
			w11 = pool.add_word("hi");
			w12 = pool.add_word("Hi");
			w21 = pool.add_word("hellO");
			w22 = pool.add_word("HelLo");
			w31 = pool.add_word("Him");
			w32 = pool.add_word("hiM");
			Assert::AreEqual((long int)w11, (long int)w12);
			Assert::AreEqual((long int)w21, (long int)w22);
			Assert::AreEqual((long int)w31, (long int)w32);
		}

		TEST_METHOD(TestSortWord) {
			wnode *w11, *w12, *w21, *w22, *w31, *w32;
			w11 = pool.add_word("hi");
			w12 = pool.add_word("Hi");
			w21 = pool.add_word("hellO");
			w22 = pool.add_word("helLo");
			w31 = pool.add_word("Him");
			w32 = pool.add_word("hiM");
			int n;
			string s;
			n = pool.get_max_word(0, s);
			Assert::AreEqual(2, n);
			Assert::AreEqual(string("helLo"), s);
			n = pool.get_max_word(1, s);
			Assert::AreEqual(2, n);
			Assert::AreEqual(string("Hi"), s);
			n = pool.get_max_word(2, s);
			Assert::AreEqual(2, n);
			Assert::AreEqual(string("Him"), s);
		}

		TEST_METHOD(TestLongWord) {
			string s = "";
			for (int i = 0; i < WORD_SIZE + 1; i++) s += 'h';
			pool.add_word(s.c_str());
			int n = pool.get_max_word(0, s);
			Assert::AreEqual(-1, n);
		}

		TEST_METHOD(TestPhrase) {
			string s;
			wnode *w1, *w2;
			w1 = pool.add_word("hello");
			w2 = pool.add_word("World");
			pool.add_phrase(w1, w2);
			w1 = pool.add_word("Hello");
			w2 = pool.add_word("world");
			pool.add_phrase(w1, w2);
			int n = pool.get_max_phrase(0, s);
			Assert::AreEqual(2, n);
			Assert::AreEqual(string("Hello World"), s);
		}

		TEST_METHOD(TestSortPhrase) {
			wnode *w1, *w2, *w3;
			w1 = pool.add_word("Hi");
			w2 = pool.add_word("HelLo");
			w3 = pool.add_word("Him");
			pool.add_phrase(w1, w1); pool.add_phrase(w1, w1); pool.add_phrase(w1, w1);
			pool.add_phrase(w1, w3); pool.add_phrase(w1, w3); pool.add_phrase(w1, w3);
			pool.add_phrase(w3, w1); pool.add_phrase(w3, w1);
			pool.add_phrase(w2, w2); pool.add_phrase(w2, w2);
			pool.add_phrase(w1, w2);
			pool.add_phrase(w3, w2);
			int n;
			string s;
			n = pool.get_max_phrase(0, s);
			Assert::AreEqual(3, n);
			Assert::AreEqual(string("Hi Hi"), s);
			n = pool.get_max_phrase(1, s);
			Assert::AreEqual(3, n);
			Assert::AreEqual(string("Hi Him"), s);
			n = pool.get_max_phrase(2, s);
			Assert::AreEqual(2, n);
			Assert::AreEqual(string("HelLo HelLo"), s);
			n = pool.get_max_phrase(3, s);
			Assert::AreEqual(2, n);
			Assert::AreEqual(string("Him Hi"), s);
			n = pool.get_max_phrase(4, s);
			Assert::AreEqual(1, n);
			Assert::AreEqual(string("Hi HelLo"), s);
			n = pool.get_max_phrase(5, s);
			Assert::AreEqual(1, n);
			Assert::AreEqual(string("Him HelLo"), s);
			n = pool.get_max_phrase(6, s);
			Assert::AreEqual(-1, n);
		}

		TEST_METHOD(TestLongPhrase) {
			string s1 = "", s2 = "", s = "";
			for (int i = 0; i < WORD_SIZE / 2; i++) s1 += 'a';
			for (int i = 0; i < WORD_SIZE + 4; i++) s2 += 'z';
			wnode * w1 = pool.add_word(s1.c_str());
			wnode * w2 = pool.add_word(s2.c_str());
			pool.add_phrase(w1, w2);
			pool.add_phrase(w2, w1);
			int n = pool.get_max_phrase(0, s);
			Assert::AreEqual(-1, n);
		}

		TEST_METHOD(TestExactWord) {
			string s = "", t;
			for (int i = 0; i < WORD_SIZE; i++) s += 'h';
			pool.add_word(s.c_str());
			int n = pool.get_max_word(0, t);
			Assert::AreEqual(1, n);
			Assert::AreEqual(s, t);
		}

		TEST_METHOD(TestExactPhrase) {
			string s1 = "", s2 = "", s = "";
			for (int i = 0; i < WORD_SIZE; i++) s1 += 'a';
			for (int i = 0; i < WORD_SIZE; i++) s2 += 'z';
			wnode * w1 = pool.add_word(s1.c_str());
			wnode * w2 = pool.add_word(s2.c_str());
			pool.add_phrase(w1, w2);
			pool.add_phrase(w2, w1);
			int n;
			n = pool.get_max_phrase(0, s);
			Assert::AreEqual(1, n);
			Assert::AreEqual(s, s1 + ' ' + s2);
			n = pool.get_max_phrase(1, s);
			Assert::AreEqual(1, n);
			Assert::AreEqual(s, s2 + ' ' + s1);
		}

	};
}