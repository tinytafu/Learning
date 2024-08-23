// 拷贝构造函数
#include <cstring>
#include <iostream>
using std::cout;
using std::endl;

class computer {
public:
  // 自定义的有参构造函数
  computer(const char *brand = "", const double price = 0)
      : _brand{new char[strlen(brand) + 1]{}}, _price{price} {
    cout << "computer(const char*,const double)" << endl;
    strcpy(this->_brand, brand);
    total_price += this->_price;
  }

  // 自定义拷贝构造函数
  computer(const computer &that)
      : _brand{new char[strlen(that._brand) + 1]{}}, _price{that._price} {
    strcpy(this->_brand, that._brand);
    total_price += this->_price;
    cout << "computer(const computer& that)" << endl;
  }
  // 自定义的赋值运算符重载函数
  computer &operator=(const computer &that) {
    cout << "computer& operator=(const computer&)" << endl;
    if (this != &that) {
      if (this->_brand) {
        delete[] this->_brand;
      }
      this->_brand = new char[strlen(that._brand) + 1]{};
      strcpy(this->_brand, that._brand);
      this->_price = that._price;
    }
    return *this;
  }
  // 自定义的析构函数
  ~computer() {
    cout << "~computer" << endl;
    if (this->_brand) {
      delete[] this->_brand;
      this->_brand = nullptr;
    }
    total_price -= this->_price;
  }

public:
  void print() const {
    cout << "_brand: " << this->_brand << endl;
    cout << "_price: " << this->_price << endl;
  }
  void test() const { *(this->_brand) = 'a'; }
  static double getTotalPrice() { return total_price; }

private:
  char *_brand;
  double _price;
  // 静态成员
  static double total_price;
};
// 静态成员的定义与初始化
double computer::total_price = 0;

void test() {
  computer c1("xiaomi", 2200);
  c1.print();
  cout << "----------" << endl;
  computer c2("huawei", 3300);
  c2.print();
  cout << "----------" << endl;
  cout << computer::getTotalPrice() << endl;
}
void test1() {
  computer c1{"xiaomi", 2200};
  computer c2{c1};
  c1.print();
  c2.print();
}
void test2() {}

int main() {
  test1();
  return 0;
}
