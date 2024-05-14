#include <iostream>
using namespace std;

int& get(int ref_a) {
  return ref_a;
}

int main () {
  int a = 30;
  int& ref = get(a);
  cout << "ref is " << ref << std::endl;
}
