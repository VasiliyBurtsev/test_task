#include <library_cli.сpp>
using namespace std;

int main(int, char**){
    setlocale(LC_ALL,"");
    //system("CLS");
    //say_hello();
    string REST_API = "http://rdb.altlinux.org";
         string method = "export/branch_binary_packages";
         string branch = "p10";
         string arch = "i586";
		 string js_str = readJSONAPI(REST_API,branch,arch,method);
       //system("pause");
    return 0;
}
