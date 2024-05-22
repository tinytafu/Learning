// 类：抽取事物特征的规则
#include <cstring>
#include <iostream>

using namespace std;

// struct
class human {
  public:
    /*设置成员属性*/
    void set_attribute(const int m_age = 20,const char *m_name = "小儿") {
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
    int get_age_attribute() {
      return this->m_age;
    }
    char *get_name_attribute() {
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
  human h1; // 定义一个struct human类型的的对象 1.分配内存空间2.若有初始化就初始化
  h1.set_attribute(25,"wangshuai");
  cout << "h1.m_age = " << h1.get_age_attribute() << endl;
  cout << "h1.m_name = " << h1.get_name_attribute() << endl;
  // 对对象中的属性赋值
  // h1.m_age = 20;
  // strcpy(h1.m_name, "wangshuai");
  // cout << "h1.m_age = " << h1.m_age << " h1.m_name = " << h1.m_name << endl;
}
