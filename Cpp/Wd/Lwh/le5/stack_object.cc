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
  ~student() { cout << "~student()" << endl; }
  friend ostream &operator<<(ostream &os, const student &that);

private:
  void *operator new(size_t count) {
    cout << "operator new(size_t count)" << endl;
    return malloc(count);
  }
  void operator delete(void *ptr) {
    cout << "operator delete()" << endl;
    free(ptr);
  }

private:
  string _name;
  int _age;
};

ostream &operator<<(ostream &os, const student &that) {
  os << "name: " << that._name << endl << "age: " << that._age;
  return os;
}
void test() {
  student s1("wangshuai", 26);
  cout << s1 << endl;
  /*student* ptr = new student("wangshuai",26); error*/
}
int main() {
  test();
  return 0;
}
