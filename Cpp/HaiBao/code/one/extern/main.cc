#include <iostream>
using namespace std;
namespace wd {
extern int value;
extern void func();
} // namespace wd

int main() {
  using namespace wd;
  cout << value << endl;
  func();
}
