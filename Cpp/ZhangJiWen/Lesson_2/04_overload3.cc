// 不同作用域下
#include <iostream>
using namespace std;

// 将四个重载函数分属不同的作用域,那么ns命名空间中的两个foo函数构成重载,ns1命名空间
// 中的两个函数构成重载,但是ns与ns1之间的函数是隐藏关系.已经不符合重载条件了.
namespace ns {
void foo(char *c, short s) { cout << "1.foo" << endl; }
void foo(int i, double d) { cout << "2.foo" << endl; }
} // namespace ns
namespace ns1 {
void foo(const char *c, short s) { cout << "3.foo" << endl; }

void foo(double d, int i) { cout << "4.foo" << endl; }

} // namespace ns1

int main() {
  using namespace ns; // ns中的foo函数在当前作用域下可见 -- 在可见表中
  using namespace ns1; //ns1中的foo函数在当前作用域下可见  -- 在可见表
  char ch = 'a';
  char *ptr_ch = &ch;
  short s = 10;
  foo(ptr_ch, s); // 会调用那个呢?还是03_overload2.cc文件内的ns1中的3.foo吗?
                  // 答案是不是的,首先调用foo函数,会先去定义表中去寻找,但是定义表
                  // 此时是没有的,因此会去可见表中寻找,这时候1.foo 2.foo 3.foo 4.foo
                  // 不再相互隐藏,而是再次进行重载,会根据形参与实参的类型进行完全
                  // 匹配,最匹配的是1.foo,因此会调用1.foo
                  // 使用using ns::foo;using ns1::foo;将其引入到当前作用域
                  // 也就是在定义表中是与在可见表中是一样的道理,它们都再次实现重载
}
