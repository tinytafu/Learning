#include <iostream>
using std::cout;
using std::endl;

enum color{
  red,
  green,
  blue,
};
int main (){
  enum color c1 = red;
  /*enum color c2 = 0;整数类型的表达式不可作为枚举类型的初始化表达式*/
  cout << "c1: " << c1 << endl;
  return 0;
}
