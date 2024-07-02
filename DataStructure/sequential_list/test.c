#include "sequential_list.h"
#include <math.h>
#include <stdio.h>
#define CAPACITY 5

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
  // 在插入5个元素
  for (int i = 0; i < 5; i++) {
    insert_at_beginning(&seq_list, 10);
    print_seq_list(&seq_list);
  }
  // 再插入一个元素
  insert_at_end(&seq_list, 20);
  // 打印顺序表中的数据
  print_seq_list(&seq_list);
  // 查看顺序表中实际元素个数和容量
  printf("size is %d,capacity is %d\n", seq_list.size, seq_list.capacity);
  printf("---------------------------------------------------------\n");
  // 头部删除5个元素
  for (int i = 0; i < 5; i++) {
    delete_from_beginning(&seq_list);
    print_seq_list(&seq_list);
  }
  // 尾部插入一个元素
  insert_at_end(&seq_list, 30);
  print_seq_list(&seq_list);
  printf("----------------------------------------------------------\n");
  // 尾部删除5个元素
  for (int i = 0; i < 5; i++) {
    delete_from_end(&seq_list);
    print_seq_list(&seq_list);
  }
  printf("size is %d,capacity is %d\n", seq_list.size, seq_list.capacity);
  insert_at_pos(&seq_list, 3, 12);
  print_seq_list(&seq_list);
  printf("size is %d,capacity is %d\n", seq_list.size, seq_list.capacity);
  insert_at_pos(&seq_list, 3, 10);
  print_seq_list(&seq_list);
  printf("size is %d,capacity is %d\n", seq_list.size, seq_list.capacity);
  insert_at_pos(&seq_list, 1, 3);
  print_seq_list(&seq_list);
  printf("size is %d,capacity is %d\n", seq_list.size, seq_list.capacity);
  printf("-----------------------------------------------------------\n");
  delete_at_pos(&seq_list, 1);
  print_seq_list(&seq_list);
  printf("size is %d,capacity is %d\n", seq_list.size, seq_list.capacity);
  delete_at_pos(&seq_list, 4);
  print_seq_list(&seq_list);
  printf("size is %d,capacity is %d\n", seq_list.size, seq_list.capacity);
  delete_at_pos(&seq_list, 2);
  print_seq_list(&seq_list);
  printf("size is %d,capacity is %d\n", seq_list.size, seq_list.capacity);
}
