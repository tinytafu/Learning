//this参数
#include <cstring>
#include <iostream>

using namespace std;

class human {
  public:
    /*设置成员属性*/
    void set_attribute(/*human* this*/const int m_age = 20,const char *m_name = "小儿") {
      /*安全检查*/
      if(m_age < 20){
        cout << "年龄不可低于20!\n";
        exit(-1);
      }else if(!(strcmp(this->m_name, m_name))) {
        cout << "你才是小儿!\n";
        exit(-1);
      }
      /*成员属性赋值*/
      this->m_age = m_age;
      strcpy(this->m_name, m_name);
    }
    /*获取成员属性*/
    int get_age_attribute(/*human* this*/) {
      return this->m_age;
    }
    char *get_name_attribute(/*human *this*/) {
      return this->m_name;
    }
private:
  int m_age;
  char m_name[64];
};
// 以上的代码是模拟类的设计者(主要)
//--------------------------------
// 以下的代码模拟用户(使用类的人)

int main() {
  human h1;
  h1.set_attribute(/*&h1*/25,"wangshuai");
  cout << "h1.m_age = " << h1.get_age_attribute(/*&h1*/) << endl;
  cout << "h1.m_name = " << h1.get_name_attribute(/*&h1*/) << endl;
  human h2;
  h2.set_attribute(/*&h2*/24,"huamengjun");
  cout << "h2.m_age = " << h2.get_age_attribute(/*&h2*/) << endl;
  cout << "h2.m_name = " << h2.get_name_attribute(/*&h2*/) << endl;
}
