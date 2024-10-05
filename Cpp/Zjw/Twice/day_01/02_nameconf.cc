// 体会 名字空间可以划分更精细的逻辑空间(单元) 能够有效避免标识符冲突的问题
#include <iostream>

namespace ICBC {
//声明
extern int g_money; 
void save(int money);
} // namespace ICBC
namespace CCB {
// 声明
extern int g_money;
void save(int money);
void pay(int money);
} // namespace CCB

// ICBC定义
int ICBC::g_money = 0;
void ICBC::save(int money) { g_money += money; }
// CCB定义
int CCB::g_money = 0;
void CCB::save(int money) { g_money += money; }
void CCB::pay(int money) { g_money -= money; }

// ICBC合并
namespace ICBC {
void pay(int money) { g_money -= money; }
} // namespace ICBC

int main() {
  ICBC::save(1000);
  ICBC::pay(500);
  std::cout << "工行卡余额: " << ICBC::g_money << std::endl;

  CCB::save(2000);
  CCB::pay(300);
  std::cout << "建行卡余额: " << CCB::g_money << std::endl;
}
