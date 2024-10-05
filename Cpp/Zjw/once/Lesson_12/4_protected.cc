#include <iostream>
using std::cout;
using std::endl;

class base {
public:
  void public_method() { cout << "base public method" << endl; }

protected:
  void protected_method() { cout << "base protected method" << endl; }

private:
  void private_method() { cout << "base private method" << endl; }
};

class derive : protected base {
public:
  void access_methon() {
    // 访问基类base的成员,看的是base类内部对成员的访问控制限定
    public_method();    // ok
    protected_method(); // ok
    // private_method();//error
  }
};
int main() {
  // 创建一个子类对象
  // 利用子类对象访问基类base的成员,这时候看的是子类derive对基类成员做的重新标记了
  derive d1;
  // d1.public_method(); // error,被derive重新标记为private了
  /* d1.protected_method();//error,保护成员只能在子类derive内部或者孙子类内部中访问
  d1.private_method();//error,私有成员只能在base内部访问 */
  d1.access_methon();
}
