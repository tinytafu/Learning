#include <cstring>
#include <iostream>
using std::cout;
using std::endl;

class computer {
public:
  void setBrand(const char *brand) { strcpy(_brand, brand); }
  void setPrice(const float price) { _price = price; }
  void print() {
    cout << "_brand: " << _brand << endl;
    cout << "_price: " << _price << endl;
  }

private:
  char _brand[20];
  float _price;
};

void test() {
  computer c1;
  c1.setBrand("apple");
  c1.setPrice(10000);
  c1.print();
  return;
}
int main() {
  test();
  return 0;
}
