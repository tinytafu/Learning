//类的声明和定义分开写
#include <cstring>
#include <iostream>
using namespace std;
class human {
  public:
    human(int m_age = 10,const char* m_name = "无名");//声明
    void getinfo() const ;//声明
  private:
    int m_age;//成员变量声明
    char m_name[64];//成员变量声明
};

void human::getinfo() const {//成员函数定义
      cout << "m_age = " << m_age << endl;
      cout << "m_name = " << m_name << "\n";
}
human::human(int m_age,const char* m_name){//成员函数定义
      /*编译器帮你写的代码*/
      //成员变量定义 
      /*在this所指向的内存空间中,定义m_age成员变量分配内存空间,初始值为随机数*/
      /*在this所指向的内存空间中,定义m_name成员变量分配内存空间,初始值为随机数*/
      /*自己写的代码*/
      cout << "我是构造函数" << endl;
      strcpy(this->m_name, m_name);
      this->m_age = m_age;

} 
int main () {
  human h1(22,"wangshuai");//1.为对象h1分配内存空间2.利用构造函数参数调用特定构造函数
  h1.getinfo();

}
