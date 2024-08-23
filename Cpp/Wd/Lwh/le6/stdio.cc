// 标准输入输出流
#include <iostream>
#include <istream>
#include <limits>
#include <string>
#include <unistd.h>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::string;
void checkState(const istream &is) {
  cout << "goodbit: " << is.good() << endl;
  cout << "badbit : " << is.bad() << endl;
  cout << "failbit: " << is.fail() << endl;
  cout << "eofbit : " << is.eof() << endl;
}
void test() {
  int number = -1;
  // 检查标准输入流对象cin的状态
  checkState(std::cin);
  std::cin >> number;
  checkState(std::cin);
  // 如果发生错误,可以重置流的状态进行下一次输入
  std::cin.clear();
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  string line;
  cin >> line;
  cout << "line: " << line;
}
void readnumber() {
  cout << "pls enter a number: " << endl;
  int number = -1;
  while (cin >> number, !cin.eof()) {
    if (cin.bad()) {
      cout << "cin is broken!\n";
      return;
    } else if (cin.fail()) {
      // 重置cin的状态
      cin.clear();
      // 清空缓冲区
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      cout << "pls enter a number: " << endl;
      continue;

    } else {
      cout << "number: " << number << endl;
      break;
    }
  }
}
void test_cout() {
  for (int i = 0; i < 1024; i++) {
    cout << 'a';
  }
  cout << 'b';
  sleep(1);
}
int main() {
  test_cout();
  return 0;
}
