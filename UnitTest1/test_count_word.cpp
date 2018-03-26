#include "stdafx.h"
#include "CppUnitTest.h"

#include <string>

#include "../WordCounting/include/count_word.h"
using std::string;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(TestCountWord)
	{
	private:
		WordCounter counter;
		void count(string s) {
			for (int i = 0; i < s.size(); i++) counter.count(s[i]);
			counter.count(EOF);
		}

	public:

		TEST_METHOD(TestEmptyStream)
		{
			string s = "";
			count(s);
			Assert::AreEqual(0, counter.get_word_num());
			int n = counter.get_max_word(0, s);
			Assert::AreEqual(-1, n);
		}

		TEST_METHOD(TestNotWord)
		{
			string s = "hi hi23iii";
			for (int i = 0; i < s.size(); i++) counter.count(s[i]);
			counter.count(EOF);
			Assert::AreEqual(0, counter.get_word_num());
		}

		TEST_METHOD(TestWord)
		{
			string s = "Hello 233 hello234515 ./,./,/./, hello13415132151 hihihi heLLo HelLo23333";
			count(s);
			Assert::AreEqual(6, counter.get_word_num());
			int n;
			n = counter.get_max_word(0, s);
			Assert::AreEqual(5, n);
			Assert::AreEqual(string("HelLo23333"), s);
			n = counter.get_max_word(1, s);
			Assert::AreEqual(1, n);
			Assert::AreEqual(string("hihihi"), s);
		}

		TEST_METHOD(TestStrangeChar)
		{
			for (int i = 0; i < 129; i++) counter.count(char(i + 127));
			counter.count('\0');
			counter.count(EOF);
			Assert::AreEqual(0, counter.get_word_num());
		}

		TEST_METHOD(TestPhrase) {
			string s1 = "hello Hello hihI helLo hIHi helLO HiHi", s;
			count(s1);
			int n;
			n = counter.get_max_phrase(0, s);
			Assert::AreEqual(3, n);
			Assert::AreEqual(string("Hello hihI"), s);
			n = counter.get_max_phrase(1, s);
			Assert::AreEqual(2, n);
			Assert::AreEqual(string("hIHi helLO"), s);
			n = counter.get_max_phrase(2, s);
			Assert::AreEqual(1, n);
			Assert::AreEqual(string("hello Hello"), s);
		}

		TEST_METHOD(TestMultipleFile) {
			string s1 = "hello linda";
			string s2 = "hello linda hello";
			count(s1);
			count(s2);
			int n;
			string s;
			n = counter.get_max_phrase(0, s);
			Assert::AreEqual(2, n);
			Assert::AreEqual(string("hello linda"), s);
			n = counter.get_max_phrase(1, s);
			Assert::AreEqual(1, n);
			Assert::AreEqual(string("linda hello"), s);
			n = counter.get_max_phrase(2, s);
			Assert::AreEqual(-1, n);
		}

	};
}