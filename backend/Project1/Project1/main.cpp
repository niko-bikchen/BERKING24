#include <iostream>
#include "ICard.h"
#include "Card.h"
#include "IUser.h"
#include "User.h"
#include "ISaveDeposit.h"
#include "SaveDeposit.h"
#include "IOperationManager.h"
#include "OperationManager.h"
#include "DefferedICard.h"



int main()
{
	mongocxx::instance instance{}; // This should be done only once.
	mongocxx::uri uri("mongodb://localhost:27017");
	mongocxx::client client(uri);
	mongocxx::database db = client["preRelease"];

	//User
	/*IOperationManager* op = OperationManager::init(db);
	DefferedIUser u = op->getUser("test4");
	DefferedICard newCard = op->getCard("1092-1717");
	DefferedICard cardNum = DefferedICard("7777-1717", 123, 321, "LOL", "NOTNOW", {}, {}, 1000);
	op->addCard(cardNum);
	u->addCard("7777-1717");
	std::vector<DefferedICard> cards = op->getAllUsersCards("test4");
	std::vector<DefferedICard>::iterator i;
	for (i = cards.begin(); i != cards.end(); ++i)
	{
		std::cout << *((*i).operator->()) << std::endl;
	}*/

	//DefferedICard card = op->getCard("FINALTEST");
	//DefferedICard card2= card;
	//DefferedISaveDeposit dp = op->getSaveDeposit("UPDATED");
	/*dp->setBalance(100);
	dp->setCard("DDDD");
	dp->setEndDate("DDDFFF");
	dp->setStartDate("EEEEE");*/
	//card->setName("WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWw");
	//card2->setName("YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY");
	//user->addCard("MISCUSO");
	//user->setEmail("UPFATED");
	//user->setName("MISCUSO");
	//->setPassword("MISCUSO");
	//user->setWebToken("MISCUSO");
	/*std::list<std::string> l = { "HAAA","HAAA","HAAA" };
	user->addCard("PRIVET");*/
	//DefferedIUser u = DefferedIUser("test4", "test4", "test4", "test4");
	//u->addCard("lol");
	//u->addCard("kek");
	//DefferedIUser u2=(op->getUser("test4"));
	//std::cout << (*u2.operator->()) << std::endl;
    //op->addUser(user);
	/*DefferedISaveDeposit dep = op->getSaveDeposit("FINALTEST");
	dep->setBalance(5555);
	dep->setCard("UPDATED");
	dep->setEndDate("UPDATED");
	dep->setStartDate("UPDATED");*/
	//op->addSaveDeposit(dep);
	//DefferedICard c = op->getCard("lel");
	//std::cout << (*c.operator->()) << std::endl;
	//c->setBalance(5000);
	//c->setCVV(1000);
	//c->setDate("ooooooooooo");
	//c->setName("KEEEEEEEEEEK");
	//////op->addCard(c);
	////c->setName("UPDATED");
	//Card::Transaction tr = Card::Transaction("tr", "tr", "tr", 1000, "tr");
	//std::vector<Card::Transaction> vtr = { tr };
	//c->setTransactions(vtr);
	//c->setTemplates(vtr);
	////c->addTemplate(tr);
	
	//op->deleteCard("1092-1717");
	//DefferedICard c = DefferedICard("1092-1717", 123, 321, "KEK", "NOW", {}, {},1000);
	//op->addCard(c);
	//DefferedICard c = op->getCard("1092-1717");
	//std::cout << *c.operator->() << std::endl;
	//op->deleteCard("7777-1717");
	//DefferedICard c2 = DefferedICard("7777-1717", 123, 321, "LOL", "NOTNOW", {}, {}, 1000);
	//DefferedISaveDeposit sd = DefferedISaveDeposit("1092-1717", "12.12.12", "13.13.13", 1000);
	//op->addSaveDeposit(sd);
	//op->addCard(c);
	//op->addCard(c2);
	//DefferedIUser u = op->getUser("UPFATED");
	//op->deleteCard("1092-1717");
	//u->addCard("1092-1717");
	//u->addCard("7777-1717");
	//std::list<std::string> list =  std::list<std::string>();
	//u->setCards(list);
	//DefferedIUser u2 = op->getUser("test4");
	//u2->setCards(list);
	//std::cout << op->cardExist("1092 - 1717") << std::endl;
	//u->deleteCard("1092-1717");
	//u->addCard("1092-1717");
	//op->deleteCard("FINALTEST");

	//Deposit
	//ISaveDeposit* s = new SaveDeposit("deposit","deposit","deposit",1000);
	////op->addSaveDeposit(*s);
	//ISaveDeposit* s2 = &(op->getSaveDeposit("deposit"));
	//std::cout << *s2 << std::endl;
	//mongocxx::collection coll = db["deposits"];
	//DefferedISaveDeposit d = DefferedISaveDeposit("7777-1717", "deposit", "deposit", 1000);
	//op->addSaveDeposit(d);
	//op->deleteDeposit("7777-1717",true);
	//DefferedICard c = op->getCard("7777 - 1717");
	//std::cout <<*c.operator->() << std::endl;
	//DefferedICard c = DefferedICard("cardDEF", 111111, 222222, "cardDEF", "cardDEF", {}, {});
	//Card::Transaction tr = Card::Transaction("tr", "tr", "tr", 1000, "tr");
	//DefferedICard c = op->getCard("7777-1717");
	//c->addTemplate(tr);
	//c->deleteTemplate(tr); 
	////Card::Transaction tr2 = Card::Transaction("tr2", "tr2", "tr2", 1000, "tr2");
	////c->addTemplate(tr);
	////c->addTransaction(tr2);
	////op->addCard(c);
	//DefferedICard c2 = op->getCard("cardDEF");
	////ICard* c2 = &op->getCard("card");
	//mongocxx::collection coll = db["cards"];
	mongocxx::collection coll = db["users"];
	auto cursor = coll.find({});
	for (auto&& doc : cursor) {
		std::cout << bsoncxx::to_json(doc) << std::endl;
	}
	auto coll2 = db["cards"];
	auto cursor2 = coll2.find({});
	for (auto&& doc : cursor2) {
		std::cout << bsoncxx::to_json(doc) << std::endl;
	}
	auto coll3 = db["deposits"];
	auto cursor3 = coll3.find({});
	for (auto&& doc : cursor3) {
		std::cout << bsoncxx::to_json(doc) << std::endl;
	}
	/*c2->setDate("RESETED");
	
	
	cursor = coll.find({});
	for (auto&& doc : cursor) {
		std::cout << bsoncxx::to_json(doc) << std::endl;
	}*/
	/*DefferedICard defCard = makeCard();
	std::cout << (*defCard.operator->()) << std::endl;*/

	//Transactions
	/*Card::Transaction tr = Card::Transaction("tr","tr","tr",1000,"tr");
	auto array_builder = bsoncxx::builder::basic::array{};
	array_builder.append(transactionToDocument(tr));
	bsoncxx::builder::basic::document doc;
	doc.append(kvp("lol", array_builder));
	bsoncxx::document::view docView = doc.view();
	std::vector<Card::Transaction> vec = documentToTransactions(docView["lol"].get_array());
	std::cout << "kek" << std::endl;*/
	system("pause");
	return 0;
}