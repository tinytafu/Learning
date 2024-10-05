/*C++中的结构体
 * 1.定义变量可省略struct关键字
 * 2.struct中可有成员函数*/
#include <iostream>
using std::cout;
using std::endl;
using std::string;
struct student {
  int age_;
  string name_;
  void print(){
    cout << "age_: " << age_ << endl;
    cout << "name_: " << name_ << endl;
  }
};

int main (){
  student s1 = {
    .age_ = 20,
    .name_ = "wangshuai",
  };
  cout << "s1.age_: " << s1.age_ << "\n" << "s1.name_: " << s1.name_ << endl;
  s1.print();
  return 0;
}
