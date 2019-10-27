#include "pch.h"
#include "CppUnitTest.h"
#include "CommonDeposit.h"
#include "CommonClient.h"
#include "CommonCard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(EntitiesTests)
	{
	public:

		TEST_METHOD(CommonDepositCreation)
		{
			CommonDeposit cd = CommonDeposit(2000, std::string("19-10-2019"), std::string("02-12-2020"));

			Assert::AreEqual(cd.getEndDate(), std::string("02-12-2020"));
			Assert::AreEqual(cd.getStartDate(), std::string("19-10-2019"));

			cd.setEndDate(std::string("04-12-2020"));
			cd.setStartDate(std::string("28-10-2019"));

			Assert::AreEqual(cd.getEndDate(), std::string("04-12-2020"));
			Assert::AreEqual(cd.getStartDate(), std::string("28-10-2019"));
		}

		TEST_METHOD(CommonClientCreation)
		{
			CommonClient cc = CommonClient("John Doe", "john.doe@gmail.com", "test");

			Assert::AreEqual(cc.getName(), std::string("John Doe"));
			Assert::AreEqual(cc.getEmail(), std::string("john.doe@gmail.com"));
			Assert::AreEqual(cc.getPassword(), std::string("test"));

			cc.setEmail("test@test.com");
			cc.setPassword("121212");
			cc.setWebToken("testtoken");

			Assert::AreEqual(cc.getEmail(), std::string("test@test.com"));
			Assert::AreEqual(cc.getPassword(), std::string("121212"));
			Assert::AreEqual(cc.getWebToken(), std::string("testtoken"));
		}

		TEST_METHOD(CommonCardCreation)
		{
			const unsigned short testCVV = 320;
			const unsigned short testPIN = 1233;

			CommonCard ccard = CommonCard("123123123123123123", testCVV, testPIN);

			Assert::AreEqual(ccard.getNumber(), std::string("123123123123123123"));
			Assert::AreEqual(ccard.getCVV(), testCVV);
			Assert::AreEqual(ccard.getPIN(), testPIN);

			ccard.setBalance(1200.0);

			Assert::AreEqual(ccard.getBalance(), 1200.0);

			ccard.setName("MyCard");
			Assert::AreEqual(ccard.getName(), std::string("MyCard"));
		}
	};
}
