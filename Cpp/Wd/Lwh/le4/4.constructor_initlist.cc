#include <cstring>
#include <iostream>
#include <strings.h>
using std::cout;
using std::endl;

class computer {
public:
  computer() { cout << "computer()" << endl; }
  computer(const char *brand, const float price) : price_{price} {
    bzero(brand_, sizeof(brand_));
    strcpy(brand_, brand);
    cout << "computer(const char*,const float)" << endl;
  }
  void setBrand(const char *brand);
  void setPrice(const float price);
  void print();

private:
  char brand_[20];
  float price_;
};
void computer::setBrand(const char *brand) {
  bzero(brand_, sizeof(brand_));
  strcpy(brand_, brand);
}
void computer::setPrice(const float price) { price_ = price; }
void computer::print() {
  cout << "brand_: " << brand_ << endl;
  cout << "price_: " << price_ << endl;
}
void test() {
  /*调用无参构造函数*/
  computer c1;
  c1.setPrice(10000);
  c1.setBrand("xiaomi");
  c1.print();
  /*调用有参构造函数*/
  computer c2;
  c2.setBrand("apple");
  c2.setPrice(20000);
  c2.print();
}
int main() {
  test();
  return 0;
}
