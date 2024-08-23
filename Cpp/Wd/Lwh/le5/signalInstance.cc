#include <iostream>
#include <ostream>
#include <string>
using std::cout;
using std::endl;
using std::ostream;
using std::string;
class human {
public:
  static human &getInstance() { return _instance; }
  friend ostream &operator<<(ostream &os, const human &that);
  void init_object(const string name, const int age) {
    this->_name = name;
    this->_age = age;
  }

private:
  human(const string name = "", const int age = 0) : _name{name}, _age{age} {
    cout << "human(const string name,const int age)" << endl;
  }

private:
  string _name;
  int _age;
  static human _instance;
};
human human::_instance("wangshuai", 26);
ostream &operator<<(ostream &os, const human &that) {
  os << "name: " << that._name << endl << "age: " << that._age;
  return os;
}
int main() {
  human &ref = human::getInstance();
  human &ref1 = human::getInstance();
  cout << &ref << endl;
  cout << &ref1 << endl;
  cout << ref << endl;
  ref.init_object("tofu", 27);
  cout << ref << endl;
}
