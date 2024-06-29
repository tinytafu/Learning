#include "sequential_list.h"
#include <stdio.h>
#define CAPACITY 20

int main() {
  // 定义一个描述顺序表的对象
  seq_list_t seq_list;
  // 初始化顺序表
  init_seq_list(&seq_list, CAPACITY);
  // 插入5个数据
  for (int i = 0; i < 5; i++) {
    /*头部插入
     insert_at_beginning(&seq_list, i);*/
    /*尾部插入*/
    insert_at_end(&seq_list, i);
    // 每插入一个数据,打印一遍顺序表中的数据元素的数据
    print_seq_list(&seq_list);
  }
}
