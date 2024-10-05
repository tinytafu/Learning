// 体会名字空间指令和名字空间声明的区别
#include <iostream>
using std::cout;
using std::endl;

namespace ns1 {
  int g_value = 0;
  int g_other = 0;
}

namespace ns2 {
   int g_value = 0;
  int g_other = 0;
}

int main () {
  //名字空间指令:ns1中的所有实体在当前作用域内可见
  using namespace ns1;
  //名字空间声明:ns2中的某个实体引入到当前作用域内
  using ns2::g_value;
  g_value = 10000;
  cout << "ns1::g_value: " << ns1::g_value << " ns2::g_value: " << ns2::g_value << endl;
  
  g_other = 20000;
  cout << "ns1::g_other: " << ns1::g_other << " ns2::g_other: " << ns2::g_other << endl;
  return 0;
}
