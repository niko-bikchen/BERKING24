#pragma once
#include "OperationManager.h"
//#include <string>
#include <algorithm>
#include <sstream>
//#include <iostream>
//#include <random>
#include <random>
#include <ctime>
//#include "cpprest/details/http_helpers.h"


#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "cpprest/asyncrt_utils.h"
#include "cpprest/filestream.h"

//#include <http_client.h> 
//#include <ppltasks.h>

#include "cpprest/asyncrt_utils.h"
#include "cpprest/containerstream.h"
#include "cpprest/filestream.h"
#include "cpprest/http_client.h"
#include "cpprest/producerconsumerstream.h"
#include "cpprest/rawptrstream.h"


//using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;
using namespace concurrency;
using namespace web::http::client;



class Server
{
public:
	Server() {}
	Server(utility::string_t url);

	pplx::task<void> open() { return m_listener.open(); }
	pplx::task<void> close() { return m_listener.close(); }

private:

	void handle_get(http_request message);
	void handle_post(http_request message);

	http_listener m_listener;
};