#include "sequential_list.h"
#include <stdio.h>
#include <stdlib.h>

/*初始化顺序表*/
void init_seq_list(seq_list_t *seq_list, unsigned int capacity) {
  if (seq_list == NULL)
    return;
  // 初始化顺序表,为其申请capacity个数据元素的内存空间
  seq_list->data = (elem_t *)malloc(sizeof(elem_t) * capacity);
  // 初始化顺序表的大小为0
  seq_list->size = 0;
  return;
}

/*打印顺序表中的数据元素的数据*/
void print_seq_list(seq_list_t *seq_list) {
  if (seq_list == NULL)
    return;
  for (int i = 0; i < seq_list->size; i++) {
    printf("%d ", seq_list->data[i]);
  }
  printf("\n");
  return;
}
/*在顺序表头部插入数据*/
void insert_at_beginning(seq_list_t *seq_list, elem_t data) {
  // 判断seq_list是否为空
  if (seq_list == NULL)
    return;
  // 若顺序表无数据元素
  if (seq_list->size == 0) {
    // 在顺序表头部插入数据
    seq_list->data[0] = data;
    // 将顺序表的大小增加1
    seq_list->size++;
    return;
  }
  // 若顺序表中有一个以上数据元素,则需要将数据元素依次向后移动一位
  // 定义end变量存储顺序表中最后一个数据元素的下标,
  int end = seq_list->size - 1;
  // 要移动的元素就是从尾部元素下标到头部元素下标
  while (end >= 0) {
    // 将当前下标的数据元素的数据赋值给当前下标的后一个下标的数据元素
    seq_list->data[end + 1] = seq_list->data[end];
    // 依次移动,end--
    end--;
  }
  // 将data赋值给顺序表中的头部元素
  seq_list->data[0] = data;
  // 将顺序表的大小增加1
  seq_list->size++;
  return;
}

/*在顺序表中尾部插入数据*/
void insert_at_end(seq_list_t *seq_list, elem_t data) {
  if (seq_list == NULL)
    return;
  // 若顺序表无数据元素,则size为0.可直接使用size作为下标.
  // 若顺序表有数据元素,进行的是尾部插入,也可使用size作为下标
  // 毕竟size是等于数据元素的个数的.但是在顺序表中数据元素的存储是从下标为0
  // 开始的
  seq_list->data[seq_list->size] = data;
  // 将顺序表的大小加1
  seq_list->size++;
  return;
}
