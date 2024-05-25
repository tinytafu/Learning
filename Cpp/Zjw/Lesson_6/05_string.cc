#include <iostream>
#include <cstring>
using namespace std;

class tofu_string {
public:
  tofu_string(const char *psz = "") : m_psz(new char[strlen(psz) + 1]) {
    /*char* m_psz = new char[strlen(psz) + 1]*/
    cout << "this is a constructor function with default argument" << endl;
    strcpy(m_psz, psz);
  }
  tofu_string(const tofu_string &that)
      : m_psz(new char[strlen(that.m_psz) + 1]) {
    /*char* m_psz = new char[strlen(that.m_psz) + 1]*/
    cout << "this is a copy constructor function" << endl;
    strcpy(m_psz, that.m_psz);
  }
  tofu_string &operator=(const tofu_string &that) {
    if (this != &that) {
      delete[] this->m_psz;
      this->m_psz = new char[strlen(that.m_psz) + 1];
      strcpy(this->m_psz, that.m_psz);
    }
    cout << "this is copy and assignment function" << endl;
    return *this;
  }
  const char *c_str() const { return this->m_psz; }
  ~tofu_string() { delete[] m_psz; }

private:
  char *m_psz;
};
int main() {
  //1.call constructor function with default argument
  tofu_string ts1;
  cout << "ts1 is " << ts1.c_str() << endl;
  tofu_string ts2("hello world");
  cout << "ts2 is " << ts2.c_str() <<endl;
  //2.call copy constructor function
  tofu_string ts3 = ts2;//--> tofu_string s2(s1);
  cout << "ts3 is " << ts3.c_str() << endl;
  cout << "&ts3->m_psz is " << reinterpret_cast<void*>(const_cast<char*>(ts3.c_str())) << endl;
  cout << "&ts2->m_psz is " << reinterpret_cast<void*>(const_cast<char*>(ts2.c_str())) << endl;

  //3.call copy and assignment function
  tofu_string ts4;//-->3.1call constructor function with default argument
  ts4 = ts3;//-->3.2 call copy and assignment function
  cout << "ts4 is " << ts4.c_str() << endl;
  cout << "&ts4->m_psz is " << reinterpret_cast<void*>(const_cast<char*>(ts4.c_str())) << endl;
  cout << "&ts3->m_psz is " << reinterpret_cast<void*>(const_cast<char*>(ts3.c_str())) << endl;
  //4.RVO
  tofu_string ts5 = "hello wangshuai";
  cout << "ts5 is " << ts5.c_str() << endl;
  //5.call copy and assignment function
  tofu_string ts6;//5.1 call constructor function with default argument
  ts6 = "wangshuai";//5.2 call copy and assignment function
}
