#include <iostream>
using std::cout;

int main () {
  bool is_old = false;
  bool is_right = true;
  cout << "is_old: " << is_old << "\n";
  cout << "is_right: " << is_right << "\n";
  /*整数/字符*/
  bool is_me = 20;//true
  cout << "is_me: " << is_me << "\n";
  is_me = 0;//false
  cout << "is_me: " << is_me << "\n";
  is_me = '\0';//false
  cout << "is_me: " << is_me << "\n";
  /*小数*/
  is_me = 0.00001;//true
  cout << "is_me: " << is_me << "\n";
  is_me = 0.0000;//false
  cout << "is_me: " << is_me << "\n";
  /*字符串*/
  is_me = "";//true is_me中存储的是空字符串所在的内存地址 非0
  cout << "is_me: " << is_me << "\n";
  return 0;
}
