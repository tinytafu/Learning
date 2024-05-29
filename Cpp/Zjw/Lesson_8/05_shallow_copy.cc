// 浅拷贝
#include <cstring>
#include <iostream>
using std::cout;
using std::endl;

class human {
public:
  human(const char *f_psz = "wangshuai") : m_psz(new char[strlen(f_psz) + 1]) {
    strcpy(m_psz, f_psz);
  }
  /*自定义的拷贝构造函数*/
  human(const human &that) : m_psz(new char[strlen(that.m_psz) + 1]) {
    /*内容拷贝*/
    strcpy(m_psz, that.m_psz);
  }
  /*自定义的拷贝赋值函数*/
  human &operator=(const human &that) {
    if (this != &that) {
      /*将this指向的对象中的m_psz指向的内存空间释放*/
      delete[] this->m_psz;
      this->m_psz = new char[strlen(that.m_psz) + 1];
      strcpy(this->m_psz, that.m_psz);
    }
    return *this;
  }
  char *c_str() const { return this->m_psz; }
  ~human() { delete[] this->m_psz; }

private:
  char *m_psz;
};

int main() {
  human h1("wangshuai");
  human h2 = h1;
  cout << "address of h1.m_psz is " << reinterpret_cast<void *>(h1.c_str())
       << endl;
  cout << "address of h2.m_psz is " << reinterpret_cast<void *>(h2.c_str())
       << endl;
  human h3;
  h3 = h2;
  cout << "address of h3.m_psz is " << reinterpret_cast<void *>(h3.c_str())
       << endl;
  cout << "address of h2.m_psz is " << reinterpret_cast<void *>(h2.c_str())
       << endl;
}
