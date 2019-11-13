#include "Server.h"
//#include "OperationManager.h"

Server::Server(utility::string_t url) : m_listener(url)
{
	m_listener.support(methods::GET, std::bind(&Server::handle_get, this, std::placeholders::_1));
	m_listener.support(methods::POST, std::bind(&Server::handle_post, this, std::placeholders::_1));

}


//Scope of get/post requests in "requests.txt"




//get request
void Server::handle_get(http_request message)
{
	ucout << message.to_string() << std::endl;

	if (message.relative_uri().path() == U("/api/cards"))
	{
		message.reply(status_codes::OK, "All cards are mine");
	}
	else if (message.relative_uri().path() == U("/api/transactions"))
	{
		message.reply(status_codes::OK, "There is no transactions yet!!!");
	}
	else if (message.relative_uri().path() == U("/api/template"))
	{
		message.reply(status_codes::OK, "Is it template?");
	}
	else if (message.relative_uri().path() == U("/api/user_infotmation"))
	{
		message.reply(status_codes::OK, "No users - no information!");
	}
	else if (message.relative_uri().path() == U("/"))
	{
		concurrency::streams::fstream::open_istream(U("../static/index.html"), std::ios::in).then([=](concurrency::streams::istream is)
			{
				message.reply(status_codes::OK, is, U("text/html")).then([](pplx::task<void> t)
					{
						try
						{
							t.get();
						}
						catch (...)
						{
							//
						}
					});
			}).then([=](pplx::task<void>t)
				{
					try
					{
						t.get();
					}
					catch (...)
					{
						message.reply(status_codes::InternalError, U("Internal eror!!!"));

					}
				});
	}
	else if (message.relative_uri().path() == U("/js/chunk-vendors.e5d2513f.js"))
	{
		concurrency::streams::fstream::open_istream(U("../static/js/chunk-vendors.e5d2513f.js"), std::ios::in).then([=](concurrency::streams::istream is)
			{
				message.reply(status_codes::OK, is, U("text/javascript")).then([](pplx::task<void> t)
					{
						try
						{
							t.get();
						}
						catch (...)
						{
							//
						}
					});
			}).then([=](pplx::task<void>t)
				{
					try
					{
						t.get();
					}
					catch (...)
					{
						message.reply(status_codes::InternalError, U("Internal eror!!!"));
					}
				});
	}
	else if (message.relative_uri().path() == U("/js/app.265fb8e6.js"))
	{
		concurrency::streams::fstream::open_istream(U("../static/js/app.265fb8e6.js"), std::ios::in).then([=](concurrency::streams::istream is)
			{
				message.reply(status_codes::OK, is, U("text/javascript")).then([](pplx::task<void> t)
					{
						try
						{
							t.get();
						}
						catch (...)
						{
							//
						}
					});
			}).then([=](pplx::task<void>t)
				{
					try
					{
						t.get();
					}
					catch (...)
					{
						message.reply(status_codes::InternalError, U("Internal eror!!!"));
					}
				});
	}
	else if (message.relative_uri().path() == U("/css/app.04b83c62.css"))
	{
		concurrency::streams::fstream::open_istream(U("../static/css/app.04b83c62.css"), std::ios::in).then([=](concurrency::streams::istream is)
			{
				message.reply(status_codes::OK, is, U("text/css")).then([](pplx::task<void> t)
					{
						try
						{
							t.get();
						}
						catch (...)
						{
							//
						}
					});
			}).then([=](pplx::task<void>t)
				{
					try
					{
						t.get();
					}
					catch (...)
					{
						message.reply(status_codes::InternalError, U("Internal eror!!!"));
					}
				});
	}
	else if (message.relative_uri().path() == U("/css/chunk-vendors.055718c6.css"))
	{
	concurrency::streams::fstream::open_istream(U("../static/css/chunk-vendors.055718c6.css"), std::ios::in).then([=](concurrency::streams::istream is)
		{
			message.reply(status_codes::OK, is, U("text/css")).then([](pplx::task<void> t)
				{
					try
					{
						t.get();
					}
					catch (...)
					{
						//
					}
				});
		}).then([=](pplx::task<void>t)
			{
				try
				{
					t.get();
				}
				catch (...)
				{
					message.reply(status_codes::InternalError, U("Internal eror!!!"));
				}
			});
	}
	else
	{
		concurrency::streams::fstream::open_istream(U("../static/index.html"), std::ios::in).then([=](concurrency::streams::istream is)
			{
				message.reply(status_codes::OK, is, U("text/html")).then([](pplx::task<void> t)
					{
						try
						{
							t.get();
						}
						catch (...)
						{
							//
						}});
			}).then([=](pplx::task<void>t)
				{
					try
					{
						t.get();
					}
					catch (...)
					{
						message.reply(status_codes::InternalError, U("Internal eror!!"));
					}
				});
	}

};


//post request
void Server::handle_post(http_request message)
{
	srand(time(0));
	IOperationManager* op = OperationManager::getInstance();
	ucout << "Request   " << message.to_string() << std::endl << std::endl;

	if (message.relative_uri().path() == U("/api/make_transaction"))
	{
		//Key
		//sender_card receiver_card sum description

		json::value json_value = message.extract_json().get();

		//ñonverting
		string_t key_sender_number(U("sender_card"));
		string_t key_receiver_number(U("receiver_card"));
		string_t key_description(U("description"));
		string_t key_sum(U("sum"));

		


		string_t db_sender_number = json_value.at(key_sender_number).as_string();
		string_t db_receiver_number = json_value.at(key_receiver_number).as_string();
		string_t db_description = json_value.at(key_description).as_string();
		string_t db_sum = json_value.at(key_sum).as_string();

		//ucout << "Sum " << db_sum
		//double_t trans_sum = json_value.at(key_sum).as_double();
		//unsigned long trans_sum_in_long = trans_sum;
		//ucout << "Double "<<trans_sum << std::endl;
		//ucout << "Unsigned long " << trans_sum_in_long << std::endl;


		std::string sender_card_number = utility::conversions::to_utf8string(db_sender_number);
		std::string receiver_card_number = utility::conversions::to_utf8string(db_receiver_number);
		std::string description = utility::conversions::to_utf8string(db_description);

		std::string trans_sum = utility::conversions::to_utf8string(db_sum);
		unsigned long s = std::stol(trans_sum);
		//std::cout << "Unsigned long " << s;

		DefferedICard sender_card = op->getCard(sender_card_number);
		DefferedICard receiver_card = op->getCard(receiver_card_number);

		if (op->cardExist(receiver_card_number))
		{
			DefferedICard sender_card = op->getCard(sender_card_number);
			DefferedICard receiver_card = op->getCard(receiver_card_number);
			unsigned long current_sender_card_balance = sender_card->getBalance();
			unsigned long current_receiver_card_card_balance = receiver_card->getBalance();
			//std::cout << "!!!!!!!! " << current_sender_card_balance << std::endl;
			//std::cout << "&&&&&&&& " << current_receiver_card_card_balance << std::endl;

			sender_card->setBalance(current_sender_card_balance - s);
			receiver_card->setBalance(current_receiver_card_card_balance + s);

			message.reply(status_codes::OK, "Transaction succsesfull");
		}
		else
		{
			message.reply(status_codes::OK, "No receiver card");
		}

	}
	else if (message.relative_uri().path() == U("/api/make_template"))
	{
		message.reply(status_codes::OK, "Make transaction!!!");
	}
	else if (message.relative_uri().path() == U("/api/create_card"))
	{
		//Key
		//card_name user_email

		json::value json_value = message.extract_json().get();

		//ñonverting
		string_t key_name(U("card_name"));
		string_t key_email(U("user_email"));

		string_t db_name = json_value.at(key_name).as_string();
		string_t db_email = json_value.at(key_email).as_string();

		std::string card_name = utility::conversions::to_utf8string(db_name);
		std::string card_email = utility::conversions::to_utf8string(db_email);

		unsigned int pin = rand() % 8998 + 1001;
		unsigned int cvv = rand() % 898 + 101;
		//std::gmtime
		std::string endDate("23/10/2023");
		std::string card_number("5168745893028147");


		/*std::cout << "Card number " << card_number << std::endl;
		std::cout << "CVV " << cvv << std::endl;
		std::cout << "Pin " << pin << std::endl;
		std::cout << "Card name " << card_name << std::endl;
		std::cout << "End date " << endDate << std::endl;
		std::cout << "Card email " << card_email << std::endl;*/

		
		DefferedICard card = DefferedICard(card_number, cvv, pin, card_name, endDate);
		DefferedIUser u = op->getUser(card_email);
		u->addCard(card_number);
		op->addCard(card);

		string_t json_card_name = key_name;
		string_t json_card_number = utility::conversions::to_string_t(card_number);
		string_t json_end_date = utility::conversions::to_string_t(endDate);
		/// json_card_number = utility::conversions::to_string_t(card_number);

	/*	time_t time(NULL);
		struct tm* ptm;
		gmtime_s(ptm, rawtime);
		std::cout << "This year " << ptm->tm_year << std::endl;*/

		//ptm = gmtime(&rawtime);
		//string_t v = utility::conversions::to_string_t()
		std::string balance = std::to_string(card->getBalance());
		//string_t json_balance = utility::conversions::to_string_t(balance);
		string_t json_balance(U("500"));

		json::value reply = json::value();
		reply[U("card_name")] = json::value(json_card_name);
		reply[U("card_number")] = json::value(json_card_number);
		reply[U("card_expiration")] = json::value(json_end_date);
		reply[U("card_balance")] = json::value(json_balance);

		ucout << "Reply " << reply << std::endl;

		message.reply(status_codes::OK, reply);
	}
	else if (message.relative_uri().path() == U("/api/recover_password"))
	{
		message.reply(status_codes::OK, "No password!!!");
	}
	else if (message.relative_uri().path() == U("/api/registrate"))
	{
		//Keys
		//user_name user_email user_password

		//converting http_request into json
		json::value json_value = message.extract_json().get();

		//ñonverting
		string_t key_name(U("user_name"));
		string_t key_mail(U("user_email"));
		string_t key_password(U("user_password"));
		
		string_t db_name = json_value.at(key_name).as_string();
		string_t db_mail = json_value.at(key_mail).as_string();
		string_t db_pass = json_value.at(key_password).as_string();

		std::string user_name = utility::conversions::to_utf8string(db_name);
		std::string user_email = utility::conversions::to_utf8string(db_mail);
		std::string user_pass = utility::conversions::to_utf8string(db_pass);
		std::string user_webtoken = "webtoken";//TODO

		//json::value reply = json::value(U("succses"));
		////Validation: if user exists
		//string_t ac(U("Access-Control-Allow-Origin"));
		//message.headers().add(ac, true);
		if (!op->userExist(user_email))
		{
			DefferedIUser user = DefferedIUser(user_webtoken, user_name, user_pass, user_email);
			op->addUser(user);
			message.reply(status_codes::OK, U("true"));
		}
		else
		{
			message.reply(status_codes::OK, "User already exists");
		}
	}
	else if (message.relative_uri().path() == U("/api/authorize"))
	{
		//Keys
		//user_email user_password

		//converting http_request into json
		json::value json_value = message.extract_json().get();

		//ñonverting
		string_t key_email(U("email"));
		string_t key_password(U("password"));

		string_t db_mail = json_value.at(key_email).as_string();
		string_t db_pass = json_value.at(key_password).as_string();

		std::string user_email = utility::conversions::to_utf8string(db_mail);
		std::string user_pass = utility::conversions::to_utf8string(db_pass);
		std::string user_webtoken = "webtoken";//TODO


		//Validation: if user exists
		if (op->userExist(user_email))
		{
			DefferedIUser user = op->getUser(user_email);
			
			if (user->getPassword() == user_pass)
			{
				string_t json_user_name = utility::conversions::to_string_t(user->getName());
				string_t json_user_emal = utility::conversions::to_string_t(user->getEmail());
				

				json::value reply = json::value();
				reply[U("user_name")] = json::value(json_user_name);
				reply[U("user_email")] = json::value(json_user_emal);


				message.reply(status_codes::OK, U("true"));
			}
			else
			{
				message.reply(status_codes::OK,U("false"));
			}
		}
		else
		{
			message.reply(status_codes::OK, U("false"));
		}
	}

};