//名字空间 -- 为了划分更精细的逻辑空间(单元)

#include <iostream>
#include "02_nameconf.hpp"

//定义wangshuai名字空间中的变量和函数
int wangshuai::a = 20;
int wangshuai::add(int a,int b){
  return a + b;
}
//表示工行
namespace ICBC {
  int g_money = 0;
  void save(int money) {
    g_money += money;
  }
  void pay(int money) {
    g_money -= money;
  }
}

namespace ICBC {
  void print() {
    std::cout << "Hello ICBC!" << std::endl;
  }
}
//表示建行
namespace CCB {
  int g_money = 0;
  void save(int money) {
    g_money += money;
  }
  void pay(int money) {
    g_money -= money;
  }
}

int main () {
  //调用工行作用域下的save对工行卡进行存钱
  ICBC::save(1000);
  //调用工行作用域下的pay对工行卡进行取钱
  ICBC::pay(200);
  //输出工行卡的余额
  std::cout << "ICBC::g_money is " << ICBC::g_money << std::endl;
  
  //调用建行作用域下的save对工行卡进行存钱
  CCB::save(1000);
  //调用建行作用域下的pay对工行卡进行取钱
  CCB::pay(200);
  //输出建行卡的余额
  std::cout << "CCB::g_money is " << CCB::g_money << std::endl;
  ICBC::print();
  std::cout << "wangshuai::add is " << wangshuai::add(10, 20) << std::endl;
}
