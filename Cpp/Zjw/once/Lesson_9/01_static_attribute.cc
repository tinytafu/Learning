#include <iostream>
using namespace std;

class human {
public:
  human(int f_age = 0) : m_age(f_age) {}

  // 非静态成员函数
  void foo() {
    // 访问静态成员变量 --OK
    cout << "m_id is " << m_id << endl;
    // 访问非静态成员变量 --OK
    cout << "m_age is " << m_age << endl;
    // 访问静态成员函数 --OK
    set_mid(20);
  }
  // 静态成员函数
  static void set_mid(int f_id) {
    // 访问静态成员变量 --OK
    f_id = 20;
    // 访问非静态成员变量 -- ERROR
    /* m_age = 20; */
    // 访问非静态成员函数 -- ERROR
    /* foo(); */
  }
  static int m_id;

private:
  int m_age;
};

// 定义静态成员变量
int human::m_id = 10;

int main() {
  human h1;
  // 通过对象访问静态成员变量
  cout << "m_id is " << h1.m_id << endl;
  // 通过类名去访问
  cout << "m_id is " << human::m_id << endl;
}
