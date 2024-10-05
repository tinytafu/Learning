// 简易版的容器
#include <iostream>
using std::cout;
using std::endl;
using std::string;
#define NUM 10
class Sequence {
public:
  // 无参构造函数
  Sequence() : data{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, count(0) {}

  // 插入数据
  void push_back(const size_t data) {
    if (NUM == count)
      cout << "FULL." << endl;
    this->data[count] = data;
    count++;
  }
  // 删除数据
  void pop_back() {
    if (0 == count)
      cout << "Empty." << endl;
    else
      count--;
  }
  //[]操作符重载函数
  int &operator[](size_t number) { return data[number]; }
  //[]操作符重载函数
  const int &operator[](size_t number) const { return data[number]; }
  // 获取容器中的数据个数
  size_t get_count() const { return count; }

private:
  // 存储容器中的数据
  int data[NUM];
  // 容器中的数据个数
  size_t count;
};

int main() {
  /*-----非常容器-----*/
  // 创建一个容器
  // Sequence seq;
  // // 查看容器中的数据个数
  // cout << "count = " << seq.get_count() << endl;
  // // 插入10个数据
  // for (int i = 0; i < 10; i++)
  //   seq.push_back(i);
  // cout << "插入数据后: count = " << seq.get_count() << endl;
  // // 删除末尾元素
  // seq.pop_back();
  // cout << "删除数据后: count = " << seq.get_count() << endl;
  // // 使用[]操作符修改容器中的元素
  // int cnt = 1000;
  // for (int i = 0; i < 10; i++)
  //   seq[i] = cnt++;
  // for (int i = 0; i < 10; i++)
  //   cout << "容器中下标为" << i << "的元素: " << seq[i] << endl;
  /*-----非常容器-----*/
  /*-----常容器-----*/
  const Sequence const_seq;
  /*-----常容器-----*/
  // 构造函数中初始化了容器中的数据,访问容器中的元素
  for (int i = 0; i < 10; i++) {
    cout << const_seq[i] << endl;
  }
  // const_seq[0] = 9999;
}
