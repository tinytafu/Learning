// 拷贝构造函数
#include <iostream>
using std::cout;
using std::endl;
using std::string;
class human {
public:
  human(int f_age = 0, string f_name = "wangshuai") {
    /*编译器做的事情
     * 1.int m_age;
     * 2.string m_name;*/
    /*自己做的事情*/
    m_age = f_age;
    m_name = f_name;
  }
  /*假设是编译器默认提供的拷贝构造函数
  human(const human &that) {
    //编译器做的事情
    //1.int m_age = that.m_age;
    //2.string m_name = that.m_name;
  }
  */
  human(const human &that) {
    std::cout << "自定义的拷贝构造函数" << std::endl;
    this->m_age = that.m_age;
    this->m_name = that.m_name;
    std::cout << "m_age is " << m_age << std::endl;
    cout << "m_name is " << m_name << endl;
  }
  void getinfo() {
    cout << "m_age is " << m_age << endl;
    cout << "m_age is " << m_name << endl;
  }

private:
  int m_age;
  string m_name;
};
void print(human h1) {
  cout << "文件作用域的函数" << endl;
  h1.getinfo();
}
human return_obejct() {
  human m;
  return m;
}
int main() {
  // human h1(20, "wangshuai");
  // print(h1);
  human h2 = return_obejct();
}
