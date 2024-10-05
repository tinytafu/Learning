#include "human.h"
#include <cstring>
#include <iostream>
using namespace std;

human::human(int m_age, const char *m_name) {
  /*编译器帮你写的代码*/
  // 成员变量定义
  /*在this所指向的内存空间中,定义m_age成员变量分配内存空间,初始值为随机数*/
  /*在this所指向的内存空间中,定义m_name成员变量分配内存空间,初始值为随机数*/
  /*自己写的代码*/
  cout << "我是构造函数" << endl;
  strcpy(this->m_name, m_name);
  this->m_age = m_age;
}
void human::getinfo() const {
  cout << "m_age = " << m_age << endl;
  cout << "m_name = " << m_name << "\n";
}
