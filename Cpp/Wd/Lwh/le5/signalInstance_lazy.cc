#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
using std::cout;
using std::endl;
using std::ostream;
using std::string;
class human {
public:
  static human *getInstance() {
    count++;
    if (human::_instance == nullptr)
      _instance = new human("wangshuai", 26);
    return _instance;
  }
  void releaseInstance() {
    count--;
    if (count == 0)
      delete _instance;
  }
  friend ostream &operator<<(ostream &os, const human &that);
  void init_object(const string name, const int age) {
    this->_name = name;
    this->_age = age;
  }
  static size_t getCount() { return count; }

private:
  human(const string name = "", const int age = 0) : _name{name}, _age{age} {
    cout << "human(const string name,const int age)" << endl;
  }

private:
  string _name;
  int _age;
  static human *_instance;
  static int count;
};
human *human::_instance = nullptr;
int human::count = 0;
ostream &operator<<(ostream &os, const human &that) {
  os << "name: " << that._name << endl << "age: " << that._age;
  return os;
}
int main() {
  human *ptr_one = human::getInstance();
  human *ptr_two = human::getInstance();
  cout << ptr_one << " " << ptr_two << endl;
  ptr_one->releaseInstance();
  ptr_two->releaseInstance();
  return 0;
}
