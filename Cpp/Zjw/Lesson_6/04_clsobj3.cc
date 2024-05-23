//实例化

#include <iostream>
#include <cstring>
using namespace std;

class human{
  public:
    human(int m_age = 10,const char* m_name = "wuming"){
      cout << "我是带有缺省参数的构造函数" << endl;
      strcpy(this->m_name, m_name);
      this->m_age = m_age;
    }
    human(const human& obejct){
      this->m_age = obejct.m_age;
      strcpy(this->m_name, obejct.m_name);
      cout << "我是拷贝构造函数\n";
    }
    void getinfo() {
      cout << "m_age = " << m_age << endl;
      cout << "m_name = " << m_name << endl;
    }
  private:
    int m_age;
    char m_name[64];
};

int main () {
  //定义栈human类对象
  //1.调用带缺省参数的构造函数与无参数的构造函数
  // human h1;
  // h1.getinfo();
  //2.调用带缺省参数的构造函数与带其他参数的构造函数
  // human h2(29,"wangshuai");
  // h2.getinfo();
  //3.定义栈human类类型数组,调用的是带缺省参数的构造函数
  // human h3[3];
  // for(int i = 0;i < sizeof(h3) / sizeof(h3[0]);i++) {
    // h3[i].getinfo();
  // }
  //4.定义栈human类类型数组,都使用匿名对象对数组数据元素做初始化
  // human h4[3] = {human(23,"zhaoyun"),human(24,"guanyu")};
  // for(int i = 0;i < sizeof(h4) / sizeof(human);i++) {
  //   h4[i].getinfo();
  // }
  //5.定义栈human类类型数组
  // human h5[] = {human(23,"liubei"),human(24,"huangzhong")};
  // for(int i = 0;i < sizeof(h5) / sizeof(human);i++) {
  //   h5[i].getinfo();
  // }

  //在堆中定义或者销毁单个对象
  //1.在堆中定义单个对象,分配空间的同时自动调用带缺省参数的构造函数
  human* h6 = new human;
  h6->getinfo();
  
  //2.在堆中定义单个对象,分配空间的同时自动调用带缺省参数的构造函数
  human* h7 = new human();
  h6->getinfo();
  //3.在堆中定义human数组,分配空间的同时自动调用带缺省参数的构造函数
  human* h8 = new human[3];
  for(int i = 0;i < 3;i++){
    (h8++)->getinfo();
    //*(h8 + i)->getinfo();
    //h8[i].getinfo();
  }
  //4.在堆中定义human类型数组并使用带缺省参数的构造函数初始化
  human* h9  = new human[2]{human(22,"wusong"),human(23,"songjiang")};
  for(int i = 0;i < 2;i++) {
    h9[i].getinfo();
  }
  human* h10  = new human[]{human(22,"xiaoxuanfeng"),human(23,"sunwukong")};
  for(int i = 0;i < 2;i++) {
    h10[i].getinfo();
  }


  
}
