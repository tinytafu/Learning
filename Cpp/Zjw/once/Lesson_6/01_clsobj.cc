//认识构造函数,熟悉对象定义过程

#include <cstring>
#include <iostream>
using namespace std;
class human {
  public:
    human(int m_age = 10,const char* m_name = "无名") {
      /*编译器帮你写的代码*/
      /*为h1的m_age成员变量分配内存空间,初始值为随机数*/
      /*为h1的m_name成员变量分配内存空间,初始值为随机数*/
      /*自己写的代码*/
      cout << "我是构造函数" << endl;
      strcpy(this->m_name, m_name);
      this->m_age = m_age;
    }
    void getinfo() const {
      cout << "m_age = " << m_age << endl;
      cout << "m_name = " << m_name << "\n";
    }
  private:
    int m_age;
    char m_name[64];
};


int main () {
  human h1(22,"wangshuai");//1.为对象h1分配内存空间2.利用构造函数参数调用特定构造函数
  h1.getinfo();

}
