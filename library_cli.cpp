#include <library/library_cli.hpp>
using namespace std;
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
      return res->status;
    }
  }
  else {
    auto err = res.error();
    std::cout << "Error code: " << err << std::endl;  
    return res->err;    
  }
};
void writeListJSON(string json_str){
    // Парсим строку и получаем объект JSON
  json j = json::parse(json_str);
  // Достаём значения
  request_args request_args = j["request_args"]; cout << "request_args " << endl;
  cout << "arch " << j["request_args"]["arch"] << endl;
  int length = j["length"];
  cout << "length " << length << endl;
  list<package> packages = j["packages"]; cout << "packages" << endl;
  int n = packages.size();
  for (int i = 0; i < n; i++){
    cout << "package[" << i+1 << "] = " << endl;
    cout << "{" << enl;
    cout << "name " << packages[i].name << endl;
    cout << "epoch " << packages[i].epoch<< endl;
    cout << "version " << packages[i].version<< endl;
    cout << "release " << packages[i].release<< endl;
    cout << "arch " << packages[i].arch<< endl;
    cout << "disttag " << packages[i].disttag<< endl;
    cout << "buildtime " << packages[i].buildtime<< endl;
    cout << "source " << packages[i].source<< endl; 
    cout << "}" << enl; 
  }
};

bool IsElemInList(list<binary_package> str_list, binary_package pack){
    return find (str_list.begin(), str_list.end(), pack) != str_list.end ();
};


