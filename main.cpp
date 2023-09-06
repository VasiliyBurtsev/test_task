#include <library/library_cli.сpp>
using namespace std;

int main(int, char**){
    setlocale(LC_ALL,"");    
    string method = "export/branch_binary_packages";
    string branch1 = "";
    srting branch2 = "";
    string arch;
    cout << "Enter the first branch ";
    cin >> branch1;
    cout << "Enter the second branch ";
    cin >> branch2;
   string js_str1 = readJSONAPI(REST_API,branch1,arch,method);
   string js_str2 = readJSONAPI(REST_API,branch2,arch,method);
       //system("pause");
    return 0;
}
