//*和->操作符重载
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::string;

class ptr {
public:
  // 构造函数
  ptr() : m_age(new int(10)) {}
  // 析构函数
  ~ptr() {
    // 释放动态资源
    delete m_age;
    cout << "调用了ptr类的析构函数" << endl;
  }
  void foo() { cout << "调用了foo函数" << endl; }

private:
  int *m_age;
};

class ptr_auto {
public:
  // 构造函数
  ptr_auto() : m_ptr(new ptr) {}
  // 析构函数
  ~ptr_auto() {
    // 释放m_ptr指向的堆内存
    delete m_ptr;
    cout << "调用了ptr_auto类的析构函数" << endl;
  }
  ptr_auto(ptr_auto &that) : m_ptr(that.m_ptr) { that.m_ptr = NULL; }
  ptr &operator*() { return *m_ptr; }
  ptr *operator->() { return m_ptr; }

private:
  ptr *m_ptr;
};

int main() {
  // 定义一个指向ptr类型的指针类型的变量
  // ptr *obj = new ptr;
  // (*obj).foo();
  // obj->foo();
  // ptr *obj2 = obj;
  // (*obj2).foo();
  // obj2->foo();
  // delete obj2;
  ptr_auto auto_obj;
  (*auto_obj).foo();
  auto_obj->foo();
  ptr_auto obj = auto_obj;

  (*auto_obj).foo();
}
