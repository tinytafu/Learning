#include <cstdio>
#include <cstring>
#include <iostream>


void test_struct() {
  struct student {
    int age;
    char name[64];
    void print() {
      age = 10;
      strcpy(name, "wangshuai");
      printf("age is %d\nname is %s\n",age,name);
    }
  };
  student s1;
  s1.print();
}

void test_union() {
  union Data {
    int a : 4;//位字段 占用4位 0.5字节
    unsigned int b : 32;//位字段 占用32位 4字节
    long c; // 非位字段 假设double的大小为8字节
  };
  Data data;
  data.c = 0x1234567889900102;
  std::cout << std::hex << data.b << std::endl;
  // printf("data.b is %x\n",data.b);
  union {
    int age;
    char num[4];
  };//匿名联合体,主要体现的是联合体中所有成员的内存排布方式(共用同一块内存空间)
  age = 0x12345678;
  std::cout << std::hex << (int)num[0] << (int)num[1] << (int)num[2] << (int)num[3] << std::endl;//小端字节序
}

void test_enum() {
  enum Color {
    red,
    blue,
    black,
  };
  Color color = red;
  // Color c1 = 0; //can not
  std::cout << "color is " << color << std::endl;
}

void test_bool() {
  bool is_old ='\0';// false;
  is_old = "";//true; address of storing '\0';
  is_old = NULL;//false
  std::cout << "is_old is " << is_old << std::endl;
  bool is_right = false;
}
int main () {
  // test_bool();
  // test_enum();
  // test_union();
  // test_struct();


}
