#include <iostream>
using namespace std;

void cout() {
  int num = 1;
  printf("%d\n", num);
}

void test() {
  // 在当前作用域下与std::cout标识符都在可见表中
  // 使用时产生歧义
  // cout();
}
int main() { test(); }
