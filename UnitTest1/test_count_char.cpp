#include "stdafx.h"
#include "CppUnitTest.h"

#include "../WordCounting/include/count_char.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(TestCountChar)
	{
	private:
		CharCounter counter;

	public:
		
		TEST_METHOD(TestEmptyStream)
		{
			char s[] = "";
			for (int i = 0; i < strlen(s); i++) counter.count(s[i]);
			counter.count(EOF);
			Assert::AreEqual(counter.get_char_num(), 0);
			Assert::AreEqual(counter.get_line_num(), 1);
		}

		TEST_METHOD(TestNormalStream)
		{
			char s[] = "hi hello\nhello\n\n";
			for (int i = 0; i < strlen(s); i++) counter.count(s[i]);
			counter.count(EOF);
			Assert::AreEqual(counter.get_char_num(), 13);
			Assert::AreEqual(counter.get_line_num(), 4);
		}

		TEST_METHOD(TestStrangeChar)
		{
			char s[130];
			for (int i = 0; i < 129; i++) s[i] = char(i + 127);
			for (int i = 0; i < 129; i++) counter.count(s[i]);
			counter.count('\0');
			counter.count(EOF);
			Assert::AreEqual(counter.get_char_num(), 0);
			Assert::AreEqual(counter.get_line_num(), 2);
		}

		TEST_METHOD(TestMultiple)
		{
			char s1[] = "hi, this\n\n\n";
			char s2[] = "is tonn";
			char s3[] = "ny....";
			for (int i = 0; i < strlen(s1); i++) counter.count(s1[i]);
			counter.count(EOF);
			for (int i = 0; i < strlen(s2); i++) counter.count(s2[i]);
			counter.count(EOF);
			for (int i = 0; i < strlen(s3); i++) counter.count(s3[i]);
			counter.count(EOF);
			Assert::AreEqual(counter.get_char_num(), 21);
			Assert::AreEqual(counter.get_line_num(), 6);
		}

	};
}