//对比名字空间指令与名字空间声明
#include <iostream>
using namespace std;
namespace ns {
  int value = 0;
  int other = 0;
}
namespace ns1 {
  int value = 0;
  int other = 0;
}

int main () {
  //使用名字空间指令
  using namespace ns;//名字空间ns内的所有标识符在main函数作用域内可见
  //使用名字空间声明
  using ns1::value; // 名字空间ns1内的只有value一个标识符引入main函数作用域(相当于定义)
  value = 800;
  cout << "ns::value is " << ns::value << endl;
  cout << "ns1::value is " << ns1::value << endl;
  other = 200;
  cout << "ns::other is " << ns::other << std::endl;
  cout << "ns1::other is " << ns1::other << std::endl;
}
