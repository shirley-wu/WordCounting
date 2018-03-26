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
			pool.add_word(s);
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
			pool.add_word(s);
			s = "Hello";
			pool.add_word(s);
			s = "hello233";
			pool.add_word(s);
			int n;
			n = pool.get_max_word(0, s);
			Assert::AreEqual(3, n);
			Assert::AreEqual(string("Hello"), s);
		}

		TEST_METHOD(TestPhrase) {
			string s1, s2, s;
			s1 = "hello";
			s2 = "World";
			pool.add_phrase(s1, s2);
			s1 = "Hello";
			s2 = "world";
			pool.add_phrase(s1, s2);
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
			pool.add_word(s11); pool.add_word(s12);
			pool.add_word(s21); pool.add_word(s22);
			pool.add_word(s31); pool.add_word(s32);
			pool.add_phrase(s11, s12); pool.add_phrase(s12, s12); pool.add_phrase(s11, s11);
			// 11
			pool.add_phrase(s11, s31); pool.add_phrase(s12, s32); pool.add_phrase(s11, s32);
			// 13
			pool.add_phrase(s31, s11); pool.add_phrase(s32, s12);
			// 31
			pool.add_phrase(s22, s21); pool.add_phrase(s21, s22);
			// 22
			pool.add_phrase(s12, s21);
			// 12
			pool.add_phrase(s32, s22);
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

	};
}