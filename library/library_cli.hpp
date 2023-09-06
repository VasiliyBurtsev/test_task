#include <iostream>
#include "string.h"
#include <locale>
#include <vector>
#include <sstream>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/uri.h>
#include <cpprest/json.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;
//using namespace library_cli;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;
using namespace web::json;
const string REST_API = "https://rdb.altlinux.org";
struct package
{
    string name;
    int epoch;
    string version;
    string release;
    string arch;
    string disttag;
    int buildtime;
    string source;
};
struct list_json
{
    string branch;
    package pack;
};
// В этой функции формируем ответ сервера на запрос
void gen_response(const Request& req, Response& res) {
  // Команда set_content задаёт ответ сервера и тип ответа:
  // Hello, World! - тело ответа
  // text/plain - MIME тип ответа (в данном случае обычный текст)
  res.set_content("Hello, World!", "text/plain");
}

auto onDataReceived(char* ptr, size_t size, size_t nmemb, void* userdata) -> size_t;

constexpr auto k_max_buffer_size = 4096;
string readJSONAPI(string url,string branch, string arch,string method){
auto requestJson = http_client(U(url)).request(methods::GET,uri_builder(U("api")).append_path(U(method+"/"+branch)).append_query(U("arch"), arch).to_string())
			// Get the response.
			.then([](http_response response) {
				// Check the status code.
				if (response.status_code() != 200) {
					throw std::runtime_error("Returned " + to_string(response.status_code()));
				}

				// Convert the response body to JSON object.
				return response.extract_json();
			})

			// Get the data field.
			.then([](value jsonObject) {
                
				return to_string(jsonObject[U("packages")]);
			});

			// Parse the user details.
			

			// Wait for the concurrent tasks to finish.
			try {
				requestJson.wait();
			} catch (const exception &e) {
				printf("Error exception:%s\n", e.what());
			};
};
void writeListJSON(string json_str){
    // Парсим строку и получаем объект JSON
  json j = json::parse(json_str);
  // Достаём значения
  string branch = j["branch"]; cout << "branch " << branch << endl;
  package pack = j["pack"]; cout << "pack " << endl;
  string name;
    int epoch;
    string version;
    string release;
    string arch;
    string disttag;
    int buildtime;
    string source;
  cout << "name " << j["pack"].name<< endl;
  cout << "epoch " << j["pack"].epoch<< endl;
  cout << "version " << j["pack"].version<< endl;
  cout << "release " << j["pack"].release<< endl;
  cout << "arch " << j["pack"].arch<< endl;
  cout << "disttag " << j["pack"].disttag<< endl;
  cout << "buildtime " << j["pack"].buildtime<< endl;
  cout << "source " << j["pack"].source<< endl;
  
};
bool IsReleaseMore(package pack1, package pack2){
	return pack1.release > pack2.release;
}
bool IsElemInList(list<binary_package> str_list, binary_package pack){
    return find (str_list.begin(), str_list.end(), pack) != str_list.end ();
};
void say_hello(){
    std::cout << "Hello, from test_rest_project!\n";
};
