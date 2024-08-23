// 线性表的顺序存储 -- 顺序表
#include <cstdlib>
#include <cstring>
#include <iostream>
using std::cout;
using std::endl;

class Array {
public:
  Array(unsigned int capacity = 10)
      : _capacity{capacity}, _size{0}, _ptr{new int[_capacity]{}} {}
  ~Array() {
    delete[] _ptr;
    _ptr = nullptr;
  }

public:
  /*末尾增加元素*/
  void push_back(int val) {
    /*判断是否数组容量满了,如果满了则进行2倍扩容*/
    if (_capacity == _size)
      expand(2 * _capacity);
    _ptr[_size] = val;
    _size += 1;
  }
  /*末尾删除元素*/
  void pop_back() {
    /*判断动态数组是否为空*/
    if (_size == 0)
      return;
    _size -= 1;
  }
  /*根据位置插入元素*/
  void insert(int pos, int val) {
    /*1.判断插入位置是否合法 [0,_size]*/
    if (pos < 0 || pos > _size)
      return;
    /*2.判断动态数组是否满了*/
    if (_size == _capacity)
      expand(2 * _capacity);
    int start = _size - 1;
    while (pos <= start) {
      _ptr[start + 1] = _ptr[start];
      start--;
    }
    _ptr[pos] = val;
    _size += 1;
  }
  /*根据位置删除元素*/
  void erase(int pos) {
    /*1.判断删除的位置是否合法[0,_szie -1]或是否为空*/
    if (pos < 0 || pos > _size - 1 || _size == 0)
      return;
    int start = pos;
    while (start <= _size - 1) {
      _ptr[start] = _ptr[start + 1];
      start++;
    }
    _size -= 1;
  }
  /*根据给定的值查找元素所在的位置*/
  int find(int val) {
    /*1.判断动态数组是否为空*/
    if (_size == 0)
      return -1;
    for (int i = 0; i < _size; i++) {
      if (val == _ptr[i])
        return i;
    }
    return -1;
  }
  /*显示数组中数据元素的值*/
  void show() {
    if (_size == 0)
      return;
    for (int i = 0; i < _size; i++)
      cout << _ptr[i] << " ";
    cout << endl;
  }
  friend std::ostream &operator<<(std::ostream &os, const Array &that);

private:
  /*数组扩容*/
  void expand(unsigned int size) {
    /*1.先申请一块sizeof(元素类型) * size大小的内存块*/
    int *tmp = new int[size]();
    /*2.将原先内存空间数据元素的数据拷贝到新的内存空间中*/
    memcpy(tmp, _ptr, sizeof(int) * _size);
    /*3.释放原来的堆内存*/
    delete[] _ptr;
    /*4.指向新申请的堆内存*/
    _ptr = tmp;
    /*5.更改动态数组的容量*/
    _capacity = size;
  }

private:
  // 指向保存数据元素的一块连续的堆内存
  unsigned int _capacity;
  int _size;
  int *_ptr;
};
std::ostream &operator<<(std::ostream &os, const Array &that) {
  os << "size: " << that._size << endl << "capacity: " << that._capacity;
  return os;
}
