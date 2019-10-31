#include "pch.h"
#include "CppUnitTest.h"
#include "CommonDeposit.h"
#include "CommonClient.h"
#include "CommonCard.h"
#include "CardManager.h"
#include "ClientManager.h"
#include "DepositManager.h"
#include "Registration.h"
#include "Authorization.h"
#include "Terminal.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Entities)
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

	TEST_CLASS(Managers)
	{
	public:
		TEST_METHOD(CardAndClientManagersTest)
		{
			CardManager cardManager = CardManager();
			ClientManager clientManager = ClientManager();

			clientManager.addClient("John Doe", "john.doe@gmail.com", "test");
			const IClient& cc = clientManager.getClient("john.doe@gmail.com");

			cardManager.createCard(cc, "123123123123123123", 1231, 320);
			cardManager.makeTransaction(cc, "123123123123123123", cc, "123123123123123123", 2000.0);

			Assert::AreEqual(static_cast<size_t>(2000),
			                 cardManager.getCard(cc, "123123123123123123").getTransaction("123123123123123123").
			                             _amountOfMoney);
			Assert::AreEqual(2000.0, cardManager.checkMoney(cc, "123123123123123123"));

			cardManager.withdrawMoney(cc, "123123123123123123", 1000.0);

			Assert::AreEqual(1000.0, cardManager.checkMoney(cc, "123123123123123123"));
			Assert::AreEqual(std::string("123123123123123123"), cardManager.getCards(cc).front().getNumber());

			cardManager.createTemplate("123123123123123123", "12312312312315555", 1000, "Test");
			Assert::AreEqual(
				std::string("12312312312315555"),
				cardManager.getCard(cc, "123123123123123123").getTemplate("12312312312315555")._receiverCardNum);

			cardManager.deleteCard(cc, "123123123123123123");

			Assert::IsTrue(cardManager.getCards(cc).empty());
		}

		TEST_METHOD(DepositManagerTest)
		{
			CommonClient cc = CommonClient("John Doe", "john.doe@gmail.com", "test");
			DepositManager dm = DepositManager();

			dm.makeSaveDeposit(2000.0, "28-05-2020", cc);
			Assert::AreEqual(std::string("28-05-2020"), dm.getContract(cc)._comD.getEndDate());
			Assert::AreEqual(static_cast<size_t>(2000), dm.getContract(cc)._comD.getOriginBalance());
		}
	};

	TEST_CLASS(RegistrationAndAuthorization)
	{
	public:
		TEST_METHOD(RegistrationAndAuthorizationTest)
		{
			Registration reg = Registration();
			reg.registrate("John Doe", "john.doe@gmail.com", "test");

			Assert::IsTrue(reg.clientAlreadyPresent("John Doe", "john.doe@gmail.com", "test"));

			Authorization auth = Authorization();
			auth.authorize("John Doe", "john.doe@gmail.com", "test");

			Assert::IsTrue(auth.credentialsAreValid("John Doe", "john.doe@gmail.com", "test"));
		}
	};

	TEST_CLASS(BankTerminal)
	{
		TEST_METHOD(TerminalTests)
		{
			Terminal terminal = Terminal();
			CardManager cardManager = CardManager();
			ClientManager clientManager = ClientManager();

			clientManager.addClient("John Doe", "john.doe@gmail.com", "test");
			const IClient& cc = clientManager.getClient("john.doe@gmail.com");

			cardManager.createCard(cc, "123123123123123123", 1231, 123);

			terminal.isCardValid("123123123123123123", 1231);
		}
	};
}
