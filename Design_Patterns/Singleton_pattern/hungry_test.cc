// 饿汉模式 -- 程序启动就创建一个对象
// 调用两次拷贝构造
// 三次析构函数
// 1.在调用getInstance函数的时候会利用拷贝构造定义一个临时对象
// 2.随后调用拷贝构造函数定义h1

// 1.临时对象的销毁
// 2.h1的销毁
// 3.Instance的销毁
#include <cstring>
#include <iostream>
using std::cout, std::endl;

class human {
public:
  static human getInstance() { return human::Instance; }

public:
  human(const char *fName, const int fAge)
      : mName{new char[strlen(fName) + 1]{}}, mAge{fAge} {
    strcpy(this->mName, fName);
  }
  human(const human &that) {
    this->mName = new char[strlen(that.mName) + 1]{};
    strcpy(this->mName, that.mName);
    this->mAge = that.mAge;
    cout << "a" << endl;
  }
  human &operator=(const human &that) { return *this; }

public:
  ~human() {
    cout << "b" << endl;
    if (mName) {
      delete[] mName;
      mName = NULL;
    }
  }

private:
  char *mName;
  int mAge;
  static human Instance;
};
human human::Instance("wangshuai", 0);
int main() { human h1 = human::getInstance(); }
