#include <iostream>
#include "string.h"
#include <locale>
#include <vector>
#include <sstream>
#include <yhirose-cpp-httplib-30b7732/httplib.h>
using namespace httplib;
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
    list<package> pack;
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
        // Создаём клиент и привязываем к домену. Туда пойдут наши запросы
	Client cli(url);
  // Отправляем get-запрос и ждём ответ, который сохраняется в переменной res
  auto res = cli.Get("/api/"+method+"/"+branch+"?arch="+arch);
  // res преобразуется в true, если запрос-ответ прошли без ошибок
  if (res) {
    // Проверяем статус ответа, т.к. может быть 404 и другие
    if (res->status == 200) {
      // В res->body лежит string с ответом сервера
      std::cout << res->body << std::endl;
      return res->body;       
           
    }else{
      std::cout << "Status code: " << res->status << std::endl;
      return "";
    }
  }
  else {
    auto err = res.error();
    std::cout << "Error code: " << err << std::endl;  
    return "";
  }
};
list_json writeListJSON(string json_str,string branch){
    // Парсим строку и получаем объект JSON
  json j = json::parse(json_str);
  list_json ljs;
  // Достаём значения
  ljs.branch = branch;
  cout << "branch " << ljs.branch << endl;
  ljs.packages = j["pack"]; 
  int leng = ljs.packages.size();
  cout << "{ "<< endl;
  for (int i=0; i < leng; i++){
	  cout << "name " << ljs.packages[i].name<< endl;
  	  cout << "epoch " << ljs.packages[i].epoch<< endl;
  	  cout << "version " << ljs.packages[i].version<< endl;
  	  cout << "release " << ljs.packages[i].release<< endl;
  	  cout << "arch " << ljs.packages[i].arch<< endl;
  	  cout << "disttag " << ljs.packages[i].disttag<< endl;
  	  cout << "buildtime " << ljs.packages[i].buildtime<< endl;
  	  cout << "source " << ljs.packages[i].source<< endl;
  };
  cout << "}"<< endl;
  return ljs;
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
