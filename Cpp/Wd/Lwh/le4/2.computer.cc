#include <cstring>
#include <iostream>
using std::cout;
using std::endl;
/*在类中若有一个成员函数没有被实现,则整个类是类的声明而不是类的定义*/
class computer {
public:
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
