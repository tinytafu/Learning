#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
void test() {
  char a[10];
  cin.getline(a, 10, ' ');
  if (cin.fail()) {
    cout << "输入的字符太长\n";
    return;
  } else if (cin.good()) {
    cout << a << endl;
  }
}
int main() {
  test();
  return 0;
}
