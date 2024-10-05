// 继承的基本特点
// 子类对象包含了基类子对象
// 子类内部可以直接访问基类的所有非私有成员
#include <iostream>
using std::cout;
using std::endl;

// 创建一个基类
class base {
public:
  int m_a;
  void pub_fun() { cout << "base.pub_fun" << endl; }

protected:
  int m_b;
  void pro_fun() { cout << "base.pro_fun" << endl; }

private:
  int m_c;
  void pri_fun() { cout << "base.pri_fun" << endl; }
};
// 创建一个类继承自base
// 1.公有继承
// class derive : public base {
// 2.保护继承
// class derive : protected base {
// 3.私有继承
class derive : private base {
public:
  // 定义一个成员函数对base基类中成员的访问
  void access() {
    // 访问基类中public修饰下的成员
    cout << m_a << endl;
    pub_fun();
    // 访问基类中protected修饰下的成员
    cout << m_b << endl;
    pro_fun();
    // 访问基类中private修饰下的成员
    /* cout << m_c << endl; // error
    pri_fun();           // error */
  }

private:
  int m_d;
};

int main() {
  // 创建一个子类derive的对象
  derive d1;
  d1.access();
}
