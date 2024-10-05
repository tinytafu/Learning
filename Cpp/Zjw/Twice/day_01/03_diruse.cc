// 名字空间指令
#include <iostream>
using namespace std;

namespace ns {
  int g_value = 10;
}

/*int g_value = 20;*/
int main (){
  //int g_value = 20;/*define table in main*/
  using namespace ns;/*从这行代码开始,ns中的所有实体在当前作用域内可见 declare table in main*/

  g_value = 1000;
  cout << "ns::g_value: " <<  ns::g_value << endl;
  return 0;
}
