// 申请堆内存
#include <cstdlib>
#include <iostream>
using namespace std;
int main() {
  int *ptr = (int *)malloc(sizeof(int));
  *ptr = 100;
  cout << *ptr << endl;
  free(ptr);
  ptr = nullptr;
  cout << "-------------" << endl;
  int *ptr_new = new int();
  cout << *ptr_new << endl;
  delete ptr_new;
  ptr_new = nullptr;
  cout << "-------------" << endl;
  int *ptr_arr = new int[3]();
  for (int i = 0; i < 3; i++) {
    cout << *ptr_arr << endl;
  }
  delete[] ptr_arr;
  ptr_arr = nullptr;
  cout << "-------------" << endl;
  char *ptr_char = new char[3]{'a', 'b', 'c'};
  for (int i = 0; i < 3; i++) {
    cout << ptr_char[i] << endl;
  }
  delete[] ptr_char;
  ptr_char = nullptr;
}
