#include "stdafx.h"
#include "CppUnitTest.h"

#include <string>

#include "count_char.h"

using std::string;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(TestCountChar)
	{
	private:
		CharCounter counter;
		void count(string s) {
			for (unsigned int i = 0; i < s.size(); i++) counter.count(s[i]);
			counter.count_eof();
		}

	public:
		
		TEST_METHOD(TestEmptyStream)
		{
			count("");
			Assert::AreEqual(counter.get_char_num(), 0);
			Assert::AreEqual(counter.get_line_num(), 1);
		}

		TEST_METHOD(TestNormalStream)
		{
			count("hi hello\nhello\n\n");
			Assert::AreEqual(13, counter.get_char_num());
			Assert::AreEqual(4, counter.get_line_num());
		}

		TEST_METHOD(TestStrangeChar)
		{
			for (int i = 0; i < 129; i++) {
				counter.count(char(127 + i));
				counter.count(-1);
			}
			for (int i = 0; i < 32; i++) {
				counter.count(char(i));
				counter.count(-1);
			}
			counter.count_eof();
			Assert::AreEqual(0, counter.get_char_num());
			Assert::AreEqual(2, counter.get_line_num());
		}

		TEST_METHOD(TestMultiple)
		{
			count("hi, this\n\n\n");
			count("is tonn");
			count("ny....");
			Assert::AreEqual(21, counter.get_char_num());
			Assert::AreEqual(6, counter.get_line_num());
		}

	};
}