// 创建heap对象,不能创建栈对象
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::ostream;
using std::string;
class student {
public:
  student(const string name = "", const int age = 0) : _name{name}, _age{age} {
    cout << "student(const string,const int)" << endl;
  }

private:
  ~student() { cout << "~student()" << endl; }

public:
  friend ostream &operator<<(ostream &os, const student &that);

public:
  void *operator new(size_t count) {
    cout << "operator new(size_t count)" << endl;
    return malloc(count);
  }
  void operator delete(void *ptr) {
    cout << "operator delete()" << endl;
    free(ptr);
  }
  void release() { delete this; }

private:
  string _name;
  int _age;
};

ostream &operator<<(ostream &os, const student &that) {
  os << "name: " << that._name << endl << "age: " << that._age;
  return os;
}
void test() {
  /*析构函数私有化不可创建栈对象*/
  /*student s1("wangshuai",26);*/
  /*cout << s1 << endl;*/
  student *ptr = new student("wangshuai", 26);
  cout << *ptr << endl;
  cout << sizeof(*ptr) << endl;
  /*析构函数私有化不可使用delete*/
  /*delete ptr;*/
  ptr->release();
  return;
}
int main() {
  test();
  return 0;
}
