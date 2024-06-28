#include <iostream>
using std::cout;
using std::endl;
using std::ostream;
using std::string;
class student;
class human {
private:
  int m_age;
  string m_name;

public:
  // 定义一个参数带有默认值的构造函数
  human(int f_age = 0, string f_name = "wuming")
      : m_age(f_age), m_name(f_name) {
    cout << "human的无参构造函数" << endl;
  }
  // 自定义一个拷贝构造函数
  human(/*human* this*/ const human &that)
      : m_age(that.m_age), m_name(that.m_name) {
    cout << "human的拷贝构造函数" << endl;
  }
  // 自定义一个拷贝赋值函数
  human &operator=(/*human *this*/ const human &that) {
    this->m_age = that.m_age;
    this->m_name = that.m_name;
    cout << "human的拷贝赋值函数" << endl;
    return *this;
  }
  friend ostream &operator<<(ostream &os, const human &that);
  friend ostream &operator<<(ostream &os, const student &that);
  // 自定义的析构函数
  ~human(/*human* this*/) { cout << "human的析构函数" << endl; }
};
class student : public human {
private:
  int m_id;

public:
  // 自定义的构造函数
  student(int f_age = 0, string f_name = "", int f_id = 0)
      : human(f_age, f_name), m_id(f_id) {
    cout << "student的无参构造函数" << endl;
  }
  // 自定义一个拷贝构造函数
  student(const student &that) : human(that), m_id(that.m_id) {
    cout << "student的拷贝构造函数" << endl;
  }
  // 自定义一个拷贝赋值函数
  student &operator=(const student &that) {
    /* human *poi = this;
    const human &ref = that;
    *poi = that; */
    *((human *)this) = (const human &)that;
    this->m_id = that.m_id;
    cout << "student的拷贝赋值函数" << endl;
    return *this;
  }
  // 自定义的析构函数
  ~student() { cout << "student的析构函数" << endl; }
  friend ostream &operator<<(ostream &os, const student &that);
};
// 写一个<<运算符重载的函数,用于处理human类型对象信息的输出
ostream &operator<<(ostream &os, const human &that) {
  os << "m_age is " << that.m_age << "\n"
     << "m_name is " << that.m_name;
  return os;
}
ostream &operator<<(ostream &os, const student &that) {
  os << "m_age is " << that.m_age << "\n"
     << "m_name is " << that.m_name << "\n"
     << "m_id is " << that.m_id;
  return os;
}

int main() {
  student s1;
  // cout << s1 << endl;
  student s2(25, "wangshuai", 20220);
  // cout << s2 << endl;
  student s3(s2);
  // cout << s3 << endl;
  s1 = s3;
  cout << s1 << endl;
}
