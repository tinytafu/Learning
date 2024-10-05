// 类型转换构造函数
#include <iostream>
using std::cout;
using std::endl;
using std::string;
class cat {
public:
  cat(const char *f_name) : m_name(f_name) {}
  void talk() { cout << m_name << ": miao miao ~~~" << endl; }

private:
  string m_name;
  friend class dog;
};
class dog {
public:
  dog(const char *f_name) : m_name(f_name) {}
  explicit dog(const cat &that) : m_name(that.m_name) {
    cout << "类型构造函数 -- 自定义转换" << endl;
  }
  dog(const dog &that) : m_name(that.m_name) {
    cout << "dog的拷贝构造函数" << endl;
  }
  void talk() { cout << m_name << ": wang wang ~~~" << endl; }

private:
  string m_name;
};
int main() {
  // create cat object
  cat tinycat("thnywhite");
  tinycat.talk();
  dog tinydog = static_cast<dog>(tinycat);
  tinydog.talk();
}
