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
			std::string strTest = "1234567899876543210809435609385496093048565436039603450093458690834509634588345769834576";

			sI << strTest;
			LongNumber longNumber;

			sI >> longNumber;
			sO << longNumber;

			Assert::AreEqual(strTest, sO.str());
		}

		TEST_METHOD(To_String)
		{
			// TODO: add support of negative numbers.
			LongNumber longNumber;
			std::string strTest = "1234567890";

			std::stringstream ss;
			ss << strTest;
			ss >> longNumber;

			Assert::AreEqual(strTest, longNumber.str());
		}

		TEST_METHOD(From_Int)
		{
			// TODO: add support of negative numbers.
			LongNumber n1 = 1234567890;
			std::string strTest = "1234567890";
			Assert::AreEqual(strTest, n1.str());
		}

		TEST_METHOD(From_LongLong)
		{
			// TODO: add support of negative numbers.
			LongNumber n1 = 123456789123456789;
			std::string strTest = "123456789123456789";
			Assert::AreEqual(strTest, n1.str());
		}

		TEST_METHOD(Assignment)
		{
			LongNumber a = 112233445566778899;
			LongNumber b;
			b = a;
			Assert::AreEqual(a.str(), b.str());
		}

		TEST_METHOD(CopyAssignment)
		{
			LongNumber a = 112233445566778899;
			LongNumber b = a;
			Assert::AreEqual(a.str(), b.str());
		}

		TEST_METHOD(Sum)
		{
			LongNumber a = 112233445566778899;
			LongNumber b = 994329857324959999;
			LongNumber s = a + b;
			std::string testString = "1106563302891738898";
			Assert::AreEqual(testString, s.str());
		}

		TEST_METHOD(IncrementOperator)
		{
			LongNumber a = 112233445566778899;
			a+= 994329857324959999;
			std::string testString = "1106563302891738898";
			Assert::AreEqual(testString, a.str());
			a++;
			testString = "1106563302891738899";
			Assert::AreEqual(testString, a.str());
		}

		TEST_METHOD(PostfixIncrement)
		{
			LongNumber a = 112233445566778899;
			std::string sA = a.str();

			LongNumber b = a++;

			Assert::AreEqual(sA, b.str());
		}
	};
}