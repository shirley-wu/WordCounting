#include "stdafx.h"
#include "CppUnitTest.h"

#include "../WordCounting/include/count_word.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(TestCountWord)
	{
	private:
		
	public:
		
		TEST_METHOD(TestCertain1)
		{
			int i = 0;
			Assert::AreEqual(i, 0);
		}

	};
}