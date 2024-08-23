// 原始字面量 -- 主要解决的是字符串字面量中有转义字符或者换行连接符
#include <iostream>
using std::cout;
using std::endl;
using std::string;

int main() {
  cout << "----------1.转义字符-------------" << endl;
  //\h,\w,\t都会被认为是一个转义字符,转义成功就表达转移后的意思
  // 转义失败会将\去掉,不影响h,w的输出,但是与本来的字面量表达的意思不符
  string str = "D:\hello\world\test.c";
  cout << str << endl;
  // 使用\分别先对\进行转义,但是又太麻烦
  str = "D:\\hello\\world\\test.c";
  cout << str << endl;
  // 使用C++11的原始字面量
  str = R"(D:\hello\world\test.c)";
  cout << str << endl;
  cout << "----------2.换行-------------" << endl;
  str = "hello"
        "world"
        "wangshuai"
        "huamengjun"
        "wangmi";
  cout << str << endl;
  str = "hello\
         world\
         wangshuai\
         huamengjun\
         wangmi";
  cout << str << endl;
  // 使用C++11的原始字面量
  str = R"(hello
world
wangshuai
huamengjun
wangmi)";
  cout << str << endl;
  cout << "----------3.加备注,两边一致-------------" << endl;
  str = R"wangshuai(D:\hello\world\test.c)wangshuai";
  cout << str << endl;
}
