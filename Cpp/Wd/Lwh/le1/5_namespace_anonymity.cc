/*匿名命名空间*/
#include <iostream>
using std::cout;
using std::endl;

/*实体只具备内部链接属性
 * 在链接阶段不会为具备内部链接属性的实体
 * 进行符号解析*/
namespace {
int value = 10;
void show() { cout << "show()" << endl; }
} // namespace
