#include <iostream>
using std::cout;

/*具名的联合体中的成员的可见性只在定义联合体的块作用域*/
union A{
  int num;
  char nums[4];
};
/*匿名的联合体中的成员可见性决定于匿名联合体的定义位置*/
int main (){
  A a1;
  a1.num = 0x12345678;
  cout << std::hex << (int)a1.nums[0] << " " << (int)a1.nums[1] << " ";
  cout << std::hex << (int)a1.nums[2] << " " << (int)a1.nums[3];
  return 0;
}
