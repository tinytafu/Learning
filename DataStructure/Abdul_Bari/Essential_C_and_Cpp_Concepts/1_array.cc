#include <iostream>

int main() {
  int arr[10] = {0};
  // 1.使用变量
  for (int var : arr)
    std::cout << "var is " << var << std::endl;
  std::cout << "--------"
            << "\n";
  // 2.使用引用
  for (int &var : arr)
    std::cout << "var is " << var << std::endl;
}
