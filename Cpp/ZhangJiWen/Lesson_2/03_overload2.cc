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
  using ns1::foo; // 将ns1中的foo函数引入到当前作用域  -- 在定义表
  char ch = 'a';
  char *ptr_ch = &ch;
  short s = 10;
  foo(ptr_ch, s); // 会调用那个呢?答案是ns1下的3.foo函数,因为会先去定义表寻找,
                  // 找到了就不会再去可见表寻找了
}
