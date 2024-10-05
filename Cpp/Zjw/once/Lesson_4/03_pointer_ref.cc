//指针和引用

#include <cstdio>
#include <iostream>

int main () {
  int a = 10,b = 20;
  //指针一开始可以不初始化,但是引用必须要初始化
  int* ptr_a = &a;
  int& ref_a = a;//必须要初始化
  
  ptr_a = &b;//指针在初始化之后可以随意更改指向的对象
  ref_a = b;//引用是不可以的,这是使用b的值给ref_a引用的对象赋值,就是给a赋值
  /*指针可以为NULL*/
  ptr_a = NULL;
  /*引用为空无意义*/
  //ref_a = NULL
  
  /*存在指向指针的指针*/
  int** ptr_ptr_a = &ptr_a;
  /*不存在二级引用*/
  // int&& ref_ref_a =  ref_a;

  /*存在对指针的引用*/
  int*& rpa = ptr_a;
  /*不存在指向引用的指针*/
  // (int&)* pra = ref_a;
  ptr_a = &ref_a;//这个是指向ref_a引用的对象,可不是指向引用
  /*存在指针数组*/
  int* arr[2] = {&a,&b};
  /*不存在引用数组*/
  // int& arr_ref = {a,b};
  
  /*存在对数组的引用*/
  int* (&ref_arr)[2] = arr;
  for(int i = 0;i < sizeof(ref_arr) / sizeof(ref_arr[0]);i++) {
    printf("ref_arr[%d] = %p\n",i,ref_arr[i]);
  }
}
