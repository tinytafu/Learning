// 饿汉模式 -- 程序启动就创建一个对象
#include <cstring>
#include <iostream>
using std::cout;
using std::endl;

class human {
public:
  static human &getInstance() { return human::Instance; }
  void init_object(const char *fName, const int fAge) {
    delete[] this->mName;
    this->mName = new char[strlen(fName) + 1]{};
    strcpy(this->mName, fName);
    this->mAge = fAge;
  }
  void show() {
    cout << "mName: " << this->mName << endl;
    cout << "mAge: " << this->mAge << endl;
  }
  ~human() {
    if (this->mName) {
      delete[] this->mName;
      this->mName = nullptr;
    }
  }

private:
  human(const char *fName = "", const int fAge = 0)
      : mName{new char[strlen(fName) + 1]{}}, mAge{fAge} {
    strcpy(this->mName, fName);
  }
  human(const human &that) = delete;
  human &operator=(const human &that) = delete;

private:
  char *mName;
  int mAge;
  static human Instance;
};
human human::Instance;
int main() {
  human::getInstance().init_object("wangshuai", 20);
  human::getInstance().show();
}
