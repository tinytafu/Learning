// constexpr修饰对象
#include <iostream>
using std::cout;
using std::endl;
struct T {
  int m_i;
};
/*const可以修饰函数形参的原因是是因为const修饰的对象,它们所需要的初始化表达式
 * 可以是编译时常量,也可以是运行时常量.
 * 1.当它是编译时常量的时候,const修饰的对象
 * 本身也是一个常量表达式
 * 2.当它是运行时常量的时候,const修饰的对象
 * 是一个具备只读属性的变量*/
/*constexpr不可以修饰函数形参的原因是constexpr修饰的对象,它们所需要的初始化表达式
 * 必须是一个编译时常量,而函数是必须在运行期间才可以计算的.*/
void func(const int var) {
  const int num = 20;
  constexpr int variable = 30;
  // int array[var] = {0};
  int arr[variable]{1, 2, 23, 4};
  for (int i = 0; i < 4; i++)
    cout << arr[i] << endl;
}
int main() {
  cout << "-------------1.修饰基本类型的对象-------------" << endl;
  cout << "-------------编译阶段计算对象的值-------------" << endl;
  const int num = 20;
  cout << "num is " << num << endl;
  constexpr double var = 20.22;
  cout << "var is " << var << endl;
  cout << "-------------2.初始化表达式中不可有运行时计算数据的对象-----------"
       << endl;
  cout << "-------------"
          "也就是说必须使用常量表达式对constexpr修饰的对象进行初始化------"
       << endl;
  float f1 = 2.2f;
  // constexpr float variable = f1 + 2.2;//error
  cout << "-------------2.也可自定义类型的对象-------------" << endl;
  constexpr struct T t1 {
    .m_i = 10
  };
  cout << "t1.m_i is " << t1.m_i << endl;
  func(10);
}
