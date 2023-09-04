#include <library/library_cli.hpp>
using namespace std;
string readList(string url,string branch, string arch,string method){
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
      return res->status;
    }
  }
  else {
    auto err = res.error();
    std::cout << "Error code: " << err << std::endl;  
    return err;
  }
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

bool IsElemInList(list<binary_package> str_list, binary_package pack){
    return find (str_list.begin(), str_list.end(), pack) != str_list.end ();
};
void say_hello(){
    std::cout << "Hello, from test_rest_project!\n";
};
