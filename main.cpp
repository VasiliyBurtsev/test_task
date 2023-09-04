#include <library_cli.сpp>
using namespace std;

int main(int, char**){
    setlocale(LC_ALL,"");
    //system("CLS");
    //say_hello();
    string js_str = readList(REST_API,"p10", "i586","export/branch_binary_packages");
       //system("pause");
    return 0;
}