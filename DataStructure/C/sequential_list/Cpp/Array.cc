#include <cstdlib>
#include <cstring>
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;
class Array {
public:
  Array(const int size = 10) : mpArr{new int[size]{}}, mCap{size}, mCur{0} {}

public:
  // 尾部插入
  void push_back(const int val) {
    if (mCap == mCur) {
      // 扩容
      expand(2 * mCap);
    }
    mpArr[mCur] = val;
    mCur++;
  }
  // 尾部删除
  void pop_back() {
    if (mCur == 0)
      return;
    mCur--;
  }

  // 打印数据
  void show() {
    for (int i = 0; i < mCur; i++) {
      cout << mpArr[i] << " ";
    }
    cout << endl;
  }

public:
  friend ostream &operator<<(ostream &os, const Array &arr);

private:
  void expand(const int size) {
    int *p = new int[size]{};
    memcpy(p, mpArr, sizeof(int) * mCur);
    delete[] mpArr;
    mpArr = p;
    mCap = size;
  }

private:
  int *mpArr; // 指向存储数据的堆内存
  int mCap;   // 顺序表的容量
  int mCur;   // 顺序表中实际的元素个数
};

ostream &operator<<(ostream &os, const Array &arr) {
  os << "mCap: " << arr.mCap << " mCur: " << arr.mCur;
  return os;
}
int main() {
  srand((unsigned int)time(NULL));
  Array arr;
  cout << arr << endl;
  for (int i = 0; i < 10; i++) {
    arr.push_back(rand() % 10);
  }
  cout << arr << endl;
  arr.show();
  for (int i = 0; i < 2; i++) {
    arr.push_back(rand() % 100);
  }
  cout << arr << endl;
  arr.show();
  arr.pop_back();
  cout << arr << endl;
  arr.show();
  arr.pop_back();
  cout << arr << endl;
  arr.show();
}
