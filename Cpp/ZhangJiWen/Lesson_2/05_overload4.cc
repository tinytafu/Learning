//重载解析,根据一些重载函数的形参与实际调用重载函数传入的实参的类型匹配度决定调用
//那个重载函数

#include <iostream>
using namespace std;
void foo(char *c,short s) {//完全匹配
  cout << "1.foo(char *,short)" << endl;
}
void foo(const char *cc,short s){//常量匹配 char *可以隐式转换为const char*
  cout << "2.foo(const char *,short )" << endl;
}

void foo(char *c,int s){//升级匹配 -- short向int转换不会影响精度
  cout << "3.foo(char *,int)" << endl;
}
void foo(char *c, char ch) {//标准匹配 -- short向char转换会影响精度
  cout << "4.foo(char *,char)" << endl;
}
void foo(char *s,...){//省略号匹配 -- 最低的优先级解析
  cout << "5.foo(char *,...)" << endl;
}
int main () {
  char ch = 'a';
  char *ptr_ch = &ch;
  short s = 20;
  foo(ptr_ch,s);
}
