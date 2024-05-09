//测试当函数定义中不设置参数的时候,调用此参数是否可以?在gcc编译器下


#include <stdio.h>
#include <stdlib.h>
//是可以的,其实函数形参只是告诉调用者我需要参数的信息而已
void fun() {
  printf("可以的哦!\n");
}
//怎么让调用者不可以传入实参呢?
void fun_void(void) {
  printf("不可以的哦!\n");
}
int main () {
  fun(10 ,20,30);//参数也是入栈的,只不过没有被使用
  //fun_void(10,20,30);//这下别说void了,你只是没了解那么深
}
