#include <iostream>
using std::cout;
using std::endl;
struct rectangle {
  int length;
  int brandth;
  double s;
};
int main() {
  struct rectangle r1 = {.length = 10, .brandth = 15, .s = 0};
  r1.s = r1.brandth * r1.length;
  cout << "r1.s is " << r1.length * r1.brandth << endl;
  cout << sizeof(r1) << endl;
  return 0;
}
