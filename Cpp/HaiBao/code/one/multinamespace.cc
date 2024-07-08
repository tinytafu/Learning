// 命名空间的合并和嵌套别名
#include <iostream>
using namespace std;
namespace ws {
int value = 10;
void funcA() { cout << "funcA" << endl; }
} // namespace ws

namespace ws {
// int value = 300;//error
void funcB() { cout << "funcB" << endl; }
} // namespace ws

namespace wd {
int value = 200;
namespace wa {
int value = 400;
} // namespace wa
} // end of namespace wd
int main() {
  namespace ww = wd::wa;
  cout << ww::value << endl;
}
