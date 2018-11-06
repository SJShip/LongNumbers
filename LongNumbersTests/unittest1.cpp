#include "stdafx.h"
#include "CppUnitTest.h"
#include "../LongNumbers/LongNumber.h"
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sjship;

namespace LongNumbersTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(IO_Streams)
		{
			std::stringstream sI, sO;
			std::string strTest = "1234567899876543210";

			sI << strTest;
			LongNumber longNumber;

			sI >> longNumber;
			sO << longNumber;

			Assert::AreEqual(strTest, sO.str());
		}

		TEST_METHOD(From_Int)
		{
			LongNumber n1 = 1234567890;
		}
	};
}