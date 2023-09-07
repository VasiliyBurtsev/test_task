#include <iostream>
#include "string.h"
#include <locale>
#include <vector>
#include <list>
#include <sstream>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
using namespace web::http;
using namespace web::http::client;
using namespace web;
using namespace std;


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
list_json readJSONAPI(string url,string branch, string arch,string method){
        // Создаём клиент и привязываем к домену. Туда пойдут наши запросы
      string full_url = url+"/api/"+method+"/"+branch;
      string full_url_s;
      if (arch != null || arch != ""){
        full_url_s = full_url + "?arch="+arch;
      }
      else {
        full_url_s = full_url;
      };
    uri url(full_url_s);
    http_client client(url);
    http_request req;

    req.set_method(methods::GET);
    pplx::task<json::value> requestTask = client.request(req).then([](http_response response)
    {
    
        json::value jsonObject;
        try
        {

            if ( response.status_code() == status_codes::OK )
            {
                response.headers().set_content_type(L"application/json"); // Set headers to receive content type as JSON 
                jsonObject = response.extract_json().get();
            }
        }
        catch (const http_exception& e)
        {
            cout << e.error_code().message() << "\n";
        }
        
        return jsonObject; // returned a json value
    
    });

    json::array packages = requestTask.get().at(L"packages").as_array(); // We get the returned response here
    list_json js;
    js.branch = branch;
    js.pack = packages.as_list();
    return js;
    for (size_t i = 0; i < dataseries.size(); i++)
    {
        auto timepoint = dataseries[i].at(L"timepoint");
        wcout << timepoint << endl;
    }
	/*Client cli(url);
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
  }*/
};
void writeListJSON(list_json ljs){
    
   // Достаём значения
  ljs.branch = branch;
  cout << "branch " << ljs.branch << endl;
   
  cout << "{ "<< endl;
  for (package p : ljs.pack){
	  cout << "name " << p.name<< endl;
  	  cout << "epoch " << p.epoch<< endl;
  	  cout << "version " << p.version<< endl;
  	  cout << "release " << p.release<< endl;
  	  cout << "arch " << p.arch<< endl;
  	  cout << "disttag " << p.disttag<< endl;
  	  cout << "buildtime " << p.buildtime<< endl;
  	  cout << "source " << p.source<< endl;
  };
  cout << "}"<< endl;  
};
bool IsReleaseMore(package pack1, package pack2){
	return pack1.release > pack2.release;
}
bool IsElemInList(list<package> str_list, package pack){
    return find (str_list.begin(), str_list.end(), pack) != str_list.end ();
};



