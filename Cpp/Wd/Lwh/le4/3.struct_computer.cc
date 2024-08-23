#include <cstring>
#include <iostream>
using std::cout;
using std::endl;
/*struct与class的主要差别就是默认的访问控制限定符,前者是public,后者是private*/
struct computer {
  /*public:*/
  void setBrand(const char *brand);
  void setPrice(const float price);
  void print();

private:
  char _brand[20];
  float _price;
};
/*类成员函数setBrand的定义*/
void computer::setBrand(const char *brand) {
  bzero(_brand, sizeof(_brand));
  strcpy(_brand, brand);
}
/*类成员函数setPrice的定义*/
void computer::setPrice(const float price) { _price = price; }
/*类成员函数print的定义*/
void computer::print() {
  cout << "_brand: " << _brand << endl;
  cout << "_price: " << _price << endl;
}
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
