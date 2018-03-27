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

		TEST_METHOD(TestSameWord)
		{
			string s;
			s = "heLlo";
			pool.add_word(s.c_str());
			s = "Hello";
			pool.add_word(s.c_str());
			s = "hello233";
			pool.add_word(s.c_str());
			int n;
			n = pool.get_max_word(0, s);
			Assert::AreEqual(3, n);
			Assert::AreEqual(string("Hello"), s);
		}

		TEST_METHOD(TestPhrase) {
			string s1, s2, s;
			s1 = "hello";
			s2 = "World";
			pool.add_phrase(s1.c_str(), s2.c_str());
			s1 = "Hello";
			s2 = "world";
			pool.add_phrase(s1.c_str(), s2.c_str());
			int n = pool.get_max_phrase(0, s);
			Assert::AreEqual(2, n);
			Assert::AreEqual(string("Hello world"), s);
		}

		TEST_METHOD(TestSort) {
			string s11 = "hi";
			string s12 = "Hi";
			string s21 = "hello";
			string s22 = "HelLo";
			string s31 = "Him";
			string s32 = "hiM";
			string s;
			pool.add_word(s11.c_str()); pool.add_word(s12.c_str());
			pool.add_word(s21.c_str()); pool.add_word(s22.c_str());
			pool.add_word(s31.c_str()); pool.add_word(s32.c_str());
			pool.add_phrase(s11.c_str(), s12.c_str()); pool.add_phrase(s12.c_str(), s12.c_str()); pool.add_phrase(s11.c_str(), s11.c_str());
			// 11
			pool.add_phrase(s11.c_str(), s31.c_str()); pool.add_phrase(s12.c_str(), s32.c_str()); pool.add_phrase(s11.c_str(), s32.c_str());
			// 13
			pool.add_phrase(s31.c_str(), s11.c_str()); pool.add_phrase(s32.c_str(), s12.c_str());
			// 31
			pool.add_phrase(s22.c_str(), s21.c_str()); pool.add_phrase(s21.c_str(), s22.c_str());
			// 22
			pool.add_phrase(s12.c_str(), s21.c_str());
			// 12
			pool.add_phrase(s32.c_str(), s22.c_str());
			// 32
			int n;
			n = pool.get_max_word(0, s);
			Assert::AreEqual(2, n);
			Assert::AreEqual(string("HelLo"), s);
			n = pool.get_max_word(1, s);
			Assert::AreEqual(2, n);
			Assert::AreEqual(string("Hi"), s);
			n = pool.get_max_word(2, s);
			Assert::AreEqual(2, n);
			Assert::AreEqual(string("Him"), s);
			n = pool.get_max_phrase(0, s);
			Assert::AreEqual(3, n);
			Assert::AreEqual(string("Hi Hi"), s);
			n = pool.get_max_phrase(1, s);
			Assert::AreEqual(3, n);
			Assert::AreEqual(string("Hi hiM"), s);
			n = pool.get_max_phrase(2, s);
			Assert::AreEqual(2, n);
			Assert::AreEqual(string("HelLo hello"), s);
			n = pool.get_max_phrase(3, s);
			Assert::AreEqual(2, n);
			Assert::AreEqual(string("Him hi"), s);
			n = pool.get_max_phrase(4, s);
			Assert::AreEqual(1, n);
			Assert::AreEqual(string("Hi hello"), s);
			n = pool.get_max_phrase(5, s);
			Assert::AreEqual(1, n);
			Assert::AreEqual(string("hiM HelLo"), s);
			n = pool.get_max_phrase(6, s);
			Assert::AreEqual(-1, n);
		}

		TEST_METHOD(TestLongWord) {
			string s = "";
			for (int i = 0; i < WORD_SIZE + 1; i++) s += 'h';
			pool.add_word(s.c_str());
			int n = pool.get_max_word(0, s);
			Assert::AreEqual(-1, n);
		}

		TEST_METHOD(TestLongPhrase) {
			string s1 = "", s2 = "", s = "";
			for (int i = 0; i < WORD_SIZE / 2; i++) s1 += 'a';
			for (int i = 0; i < WORD_SIZE + 4; i++) s2 += 'z';
			pool.add_phrase(s1.c_str(), s2.c_str());
			pool.add_phrase(s2.c_str(), s1.c_str());
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
			pool.add_phrase(s1.c_str(), s2.c_str());
			pool.add_phrase(s2.c_str(), s1.c_str());
			int n = pool.get_max_phrase(0, s);
			Assert::AreEqual(1, n);
			Assert::AreEqual(s, s1 + ' ' + s2);
		}

	};
}