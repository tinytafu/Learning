/*匿名空间中的实体是不进行符号解析的
 * 因此以此源文件编译汇编生成的目标文件不会在另外的目标文件中寻找到
 * 匿名命名空间中的实体*/
#include <iostream>
using std::cout;
using std::endl;
namespace tofu {
extern int value;
extern void show();
} // namespace tofu
int main() {
  cout << tofu::value << endl;
  return 0;
}
