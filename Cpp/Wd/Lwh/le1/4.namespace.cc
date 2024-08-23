/*命名空间嵌套,别名*/
#include <iostream>
using namespace std;

namespace tofu {
int val = 10;
namespace ws {
int val = 20;
namespace bread {
int val = 30;
}
} // namespace ws
} // namespace tofu

int main() {
  cout << "tofu::val: " << tofu::val << endl;
  cout << "tofu::ws::val: " << tofu::ws::val << endl;
  cout << "tofu::ws::bread::val: " << tofu::ws::bread::val << endl;
  // 设置别名
  namespace tytofu = tofu::ws::bread;
  cout << "tytofu::val: " << tytofu::val << endl;
  return 0;
}
