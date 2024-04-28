//函数重载
//同一作用域下 同名函数 形参列表中对应的参数类型不同
#include <iostream>
using namespace std;
void foo(char *c,short s){
  cout << "1.foo" << endl;
}
void foo(int i,double d) {
  cout << "2.foo" << endl;
}

void foo(const char *c,short s) {//const char*与char *是不同的类型
  cout << "3.foo" << endl;
}

void foo(double d,int i) {
  cout << "4.foo" << endl;
}

//int foo(double d,int i) {}//不构成重载,函数重载与返回值无关
//void foo(int d,double i){}//不构成重载,函数重载与形参名称无关

int main () {
  //在这些有着重载关系的同名函数,在调用的时候是根据实参与形参的类型进行匹配,
  //调用在最匹配的
  char ch = 'a';
  char *c = &ch;
  short s = 0;
  foo(c,s);//调用第一个
  const char *cc = c ;
  foo(cc,s);//调用第三个
  int i = 100;
  double d = 22.34;
  foo(i,d);//调用第二个
  foo(d,i);//调用第四个
}
