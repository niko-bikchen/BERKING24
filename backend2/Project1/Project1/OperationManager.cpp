#include "OperationManager.h"




OperationManager * OperationManager::_op = 0;

void OperationManager::do_addUser(const DefferedIUser& u)
{
	
	//constructing document representation of the User
	bsoncxx::builder::basic::document doc;
	doc.bsoncxx::builder::basic::sub_document::append(bsoncxx::builder::basic::kvp("name", u->getName()));
	doc.bsoncxx::builder::basic::sub_document::append(bsoncxx::builder::basic::kvp("password", u->getPassword()));
	doc.bsoncxx::builder::basic::sub_document::append(bsoncxx::builder::basic::kvp("email", u->getEmail()));
	doc.bsoncxx::builder::basic::sub_document::append(bsoncxx::builder::basic::kvp("webtoken", u->getWebToken()));

	//Adding cards
	std::list<std::string>cards = u->getCards();
	std::list<std::string>::iterator i;
	auto array_builder = bsoncxx::builder::basic::array{};
	for (i = cards.begin(); i != cards.end(); ++i)
	{
		array_builder.bsoncxx::builder::basic::sub_array::append(*i);
	}
	doc.bsoncxx::builder::basic::sub_document::append(bsoncxx::builder::basic::kvp("cards", array_builder));

	//Adding the user
	mongocxx::collection coll = _db["users"];
	coll.insert_one(doc.view());
	return;
}

DefferedIUser OperationManager::do_getUser(std::string email) 
{
	//retriving User from bd
	mongocxx::collection coll = _db["users"];
	auto cursor = coll.find(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("email", email)));
	bsoncxx::document::view userView;
	for (auto&& doc : cursor) 
	{
	userView = doc;
	}
	//creating user
	DefferedIUser u = DefferedIUser(userView["webtoken"].get_utf8().value.to_string(),
		userView["name"].get_utf8().value.to_string(),
		userView["password"].get_utf8().value.to_string(),
		userView["email"].get_utf8().value.to_string());
	bsoncxx::v_noabi::types::b_array cards = userView["cards"].get_array();
	bsoncxx::array::view arrayView = bsoncxx::array::view(cards);
	bsoncxx::array::view::iterator i;
	for (i = arrayView.begin(); i != arrayView.end(); ++i)
	{
		u->addCard((*i).get_utf8().value.to_string());
	}

	return u;
}



DefferedISaveDeposit OperationManager::do_getSaveDeposit(std::string num) 
{

	//retriving User from bd
	mongocxx::collection coll = _db["deposits"];
	auto cursor = coll.find(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("card_number", num)));
	bsoncxx::document::view depositView;
	for (auto&& doc : cursor)
	{
		depositView = doc;
	}
	//creating user
	DefferedISaveDeposit dp = DefferedISaveDeposit(depositView["card_number"].get_utf8().value.to_string(),
		                               depositView["start_date"].get_utf8().value.to_string(),
		                               depositView["end_date"].get_utf8().value.to_string(),
		                               stol(depositView["balance"].get_utf8().value.to_string()) );
	

	return dp;
}


void OperationManager::do_update() 
{
}

void OperationManager::do_addSaveDeposit(const DefferedISaveDeposit & dp)
{
	//constructing document representation of the User
	bsoncxx::builder::basic::document doc;
	doc.bsoncxx::builder::basic::sub_document::append(bsoncxx::builder::basic::kvp("card_number", dp->getCardNum()));
	doc.bsoncxx::builder::basic::sub_document::append(bsoncxx::builder::basic::kvp("start_date", dp->getStartDate()));
	doc.bsoncxx::builder::basic::sub_document::append(bsoncxx::builder::basic::kvp("end_date", dp->getEndDate()));
	doc.bsoncxx::builder::basic::sub_document::append(bsoncxx::builder::basic::kvp("balance", std::to_string(dp->getBalance()) ));
	
	//Adding the deposit
	mongocxx::collection coll = _db["deposits"];
	coll.insert_one(doc.view());
	return;
}

void OperationManager::do_addCard(const DefferedICard & c)
{
	//constructing document representation of the User
	bsoncxx::builder::basic::document doc;
	doc.bsoncxx::builder::basic::sub_document::append(bsoncxx::builder::basic::kvp("number_card", c->getNumber()));
	doc.bsoncxx::builder::basic::sub_document::append(bsoncxx::builder::basic::kvp("cvv", std::to_string(c->getCVV())));
	doc.bsoncxx::builder::basic::sub_document::append(bsoncxx::builder::basic::kvp("pin", std::to_string(c->getPIN())));
	doc.bsoncxx::builder::basic::sub_document::append(bsoncxx::builder::basic::kvp("name", c->getName()));
	doc.bsoncxx::builder::basic::sub_document::append(bsoncxx::builder::basic::kvp("date_end", c->getDate()));
	doc.bsoncxx::builder::basic::sub_document::append(bsoncxx::builder::basic::kvp("card_balance", std::to_string(c->getBalance())));
	doc.bsoncxx::builder::basic::sub_document::append(bsoncxx::builder::basic::kvp("transactions", bsoncxx::builder::basic::make_array()));
	doc.bsoncxx::builder::basic::sub_document::append(bsoncxx::builder::basic::kvp("templates", bsoncxx::builder::basic::make_array()));

	//Adding the deposit
	mongocxx::collection coll = _db["cards"];
	coll.insert_one(doc.view());
	return;
}

DefferedICard OperationManager::do_getCard(std::string number)
{
	//retriving Card from bd
	mongocxx::collection coll = _db["cards"];
	auto cursor = coll.find(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("number_card", number)));
	bsoncxx::document::view cardView;
	for (auto&& doc : cursor)
	{
		cardView = doc;
	}
	//creating card
	DefferedICard c = DefferedICard(cardView["number_card"].get_utf8().value.to_string(),
		std::stoi(cardView["cvv"].get_utf8().value.to_string()),
		std::stoi(cardView["pin"].get_utf8().value.to_string()),
		cardView["name"].get_utf8().value.to_string(),
		cardView["date_end"].get_utf8().value.to_string(),
		{},
		{});
	c->setBalance(stol(cardView["card_balance"].get_utf8().value.to_string()));
	c->setTransactions(documentToTransactions(cardView["transactions"].get_array()));
	c->setTemplates(documentToTransactions(cardView["templates"].get_array()));
	
	return c;
}
 bsoncxx::document::value  transactionToDocument(const ICard::Transaction& tr)
{
	return bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("trans_date", tr.getDate()),
		bsoncxx::builder::basic::kvp("senderCN", tr.getSenderCardNum()),
		bsoncxx::builder::basic::kvp("recieverCN", tr.getrecieverCardNum()),
		bsoncxx::builder::basic::kvp("sum", std::to_string(tr.getSum())),
		bsoncxx::builder::basic::kvp("description", tr.getDescription()));
}

std::vector<ICard::Transaction>& documentToTransactions(const bsoncxx::v_noabi::types::b_array& ar)
{
	std::vector<ICard::Transaction> *tr=new std::vector<ICard::Transaction>();
	bsoncxx::array::view arrayView = bsoncxx::array::view(ar);
	bsoncxx::array::view::iterator i;
	for (i = arrayView.begin(); i != arrayView.end(); ++i)
	{
		auto tran = (*i).get_value().get_document();
		bsoncxx::document::view trView = tran.view();
		(*tr).insert((*tr).begin(), 1, ICard::Transaction(trView["trans_date"].get_utf8().value.to_string(),
			trView["senderCN"].get_utf8().value.to_string(),
			trView["recieverCN"].get_utf8().value.to_string(),
			stol(trView["sum"].get_utf8().value.to_string()),
			trView["description"].get_utf8().value.to_string()));
	}
	return *tr;
}
