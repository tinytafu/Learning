// 名字空间声明
#include <iostream>
using std::cout;
using std::endl;

namespace ns {
  int g_value = 0;
}
/*int g_value = 20;*/
/*using ns::g_value;*/
int main (){
  using ns::g_value;/*从这行代码开始,ns中的g_value实体引入当前作用域(相当于定义) define table in main*/
  int g_value = 10;
  /*g_value = 30;*/
  cout << "ns:g_value: " << ns::g_value << endl;
  return 0;
}
