// 操作符重载

#include <iostream>
using std::cout;
using std::endl;
using std::string;
class human;
human operator+(const human &l, const human &r);
human operator-(const human &l, const human &r);
class human {
public:
  human(const int f_age = 0, const char *f_name = "")
      : m_age(f_age), m_name(f_name) {}
  void getinfo() {
    cout << "m_age is " << m_age << endl;
    cout << "m_name is " << m_name << endl;
  }
  // human add(human that) {
  //   return (human(this->m_age + that.m_age,
  //                 (this->m_name + "+" + that.m_name).c_str()));
  // }
  // human sub(human that) {
  //   return (human(this->m_age - that.m_age,
  //                 (this->m_name + "-" + that.m_name).c_str()));
  // }
  // /*成员加法运算符重载函数*/
  // human operator+(const human &that) const {
  //   /*只想让它们的年龄相加,名字取首字母加在一起*/
  //   return (human(this->m_age + that.m_age,
  //                 (this->m_name + "+" + that.m_name).c_str()));
  // }
  // /*成员减法运算符重载函数*/
  // human operator-(const human &that) const {
  //   /*只想让它们的年龄相加,名字取首字母加在一起*/
  //   return (human(this->m_age - that.m_age,
  //                 (this->m_name + "-" + that.m_name).c_str()));
  // }

private:
  int m_age;
  string m_name;
  friend human operator+(const human &l, const human &r);
  friend human operator-(const human &l, const human &r);
};

human operator+(const human &l, const human &r) {
  return human(l.m_age + r.m_age, (l.m_name + "+" + r.m_name).c_str());
}
human operator-(const human &l, const human &r) {
  return human(l.m_age - r.m_age, (l.m_name + "-" + r.m_name).c_str());
}

int main() {

  human h1(10, "wangshuai"), h2(20, "huamengjun");
  // 定义成员方法完成h1和h2之间的加法操作,实际就是对象的数据加减
  // human ret_add = h1.add(h2);
  // human ret_sub = h1.sub(h2);
  // ret_sub.getinfo();
  // ret_add.getinfo();
  human res_add = h1 + h2;
  human res_sub = h1 - h2;
  res_sub.getinfo();
  res_add.getinfo();
}
