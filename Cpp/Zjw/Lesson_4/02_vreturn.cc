#include <iostream>
using namespace std;

//创建一个全局变量
int global_value = 10;

int& return_global_ref() {
  return global_value;
}
//创建一个静态变量
int& return_static_ref() {
  static int a = 120;
  cout << "a: " << a << " &a: " << &a << endl; 
  return a;
}
//创建一个堆对象
int& return_heap_ref() {
  int* ptr = new int(30);
  cout << "ptr: " << ptr << " *ptr: " << *ptr << endl;
  return *ptr;
}
int main () {
  //return_ref()本身就可以作为对global_value的引用,下面这个语句就是一个新的引用,引用了global_value
  int& ref_global = return_global_ref();
  cout << "ref_global: " << ref_global << " global_value: " << global_value << endl;
  cout << "&ref_global: " << &ref_global << " &global_value: " << &global_value << endl;

  int& ref_static = return_static_ref();
  cout << "ref_static: " << ref_static << " &ref_static: " << &ref_static << endl;

  int& ref_heap = return_heap_ref();
  cout << "ref_heap: " << ref_heap << "&ref_heap: " << &ref_heap << endl;

}
