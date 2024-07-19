#include "sequential_list.h"
#include <stdio.h>
#include <stdlib.h>

/*初始化顺序表*/
void init_seq_list(seq_list_t *seq_list, unsigned int capacity) {
  if (seq_list == NULL)
    return;
  // 初始化顺序表,为其申请capacity个数据元素的内存空间
  seq_list->data = (elem_t *)malloc(sizeof(elem_t) * capacity);
  // 初始化顺序表容量
  seq_list->capacity = capacity;
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
/*查找顺序表特定的数据,返回所在顺序表位置*/
int find_seq_list(seq_list_t *seq_list, elem_t data) {
  // 若指向描述顺序表对象的指针为NULL或顺序表为NULL
  if (seq_list == NULL || seq_list->data == NULL)
    return -1;
  // 遍历顺序表并比较每个位置上的数据是否和data一致
  for (int i = 0; i < seq_list->size; i++) {
    if (seq_list->data[i] == data) {
      return i + 1;
    }
  }
  return -1;
}

/*在顺序表头部插入数据*/
void insert_at_beginning(seq_list_t *seq_list, elem_t data) {
  // 判断seq_list是否为空
  if (seq_list == NULL)
    return;
  // 判断顺序表是否满了,若满了则一倍扩容
  if (seq_list->size == seq_list->capacity) {
    // 将容量扩大一倍
    seq_list->capacity *= 2;
    // 定义临时变量保存申请新空间的地址
    elem_t *tmp =
        (elem_t *)realloc(seq_list->data, sizeof(elem_t) * seq_list->capacity);
    // 判断是否为空
    if (NULL == tmp)
      return;
    // 将临时变量的值赋值给seq_list->data
    seq_list->data = tmp;
  }
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
  // 若seq_list为空
  if (seq_list == NULL) {
    return;
  }
  // 若顺序表满了,则一倍扩容
  if (seq_list->capacity == seq_list->size) {
    // 将容量扩大一倍
    seq_list->capacity *= 2;
    // 定义临时变量保存申请新空间的地址
    elem_t *tmp =
        (elem_t *)realloc(seq_list->data, sizeof(elem_t) * seq_list->capacity);
    // 判断是否为空
    if (NULL == tmp)
      return;
    // 将临时变量的值赋值给seq_list->data
    seq_list->data = tmp;
  }
  // 若顺序表无数据元素,则size为0.可直接使用size作为下标.
  // 若顺序表有数据元素,进行的是尾部插入,也可使用size作为下标
  // 毕竟size是等于数据元素的个数的.但是在顺序表中数据元素的存储是从下标为0
  // 开始的
  seq_list->data[seq_list->size] = data;
  // 将顺序表的大小加1
  seq_list->size++;
  return;
}
/*在顺序表中头部删除数据*/
void delete_from_beginning(seq_list_t *seq_list) {
  // 若seq_list为NULL,顺序表为空
  if (seq_list == NULL || seq_list->size == 0) {
    return;
  }
  // 若顺序表中只有一个数据元素
  if (seq_list->size == 1) {
    seq_list->size--;
    return;
  }
  // 若顺序表有多个数据元素
  // 定义指向顺序表中需要被覆盖数据的数据元素的下标[0,seq_list->size - 2]
  int start = 0;
  // 当start小于等于seq_list->size - 1进行循环
  while (start <= seq_list->size - 2) {
    // 移动数据元素
    seq_list->data[start] = seq_list->data[start + 1];
    // 向后移动元素下标一位
    start++;
  }
  seq_list->size--;
  return;
}
/*在顺序表中尾部删除数据*/
void delete_from_end(seq_list_t *seq_list) {
  // 若seq_list为NULL或者顺序表为空
  if (seq_list == NULL || seq_list->data == NULL)
    return;
  // 删除尾部数据
  seq_list->size--;
  return;
}

/*在顺序表中的某个位置插入数据*/
void insert_at_pos(seq_list_t *seq_list, int pos, elem_t data) {
  // 若顺序表为空,则寻求其他方法先插入数据
  if (seq_list == NULL || seq_list->data == NULL)
    return;
  // 若插入位置不在可控范围[1,seq_list->size + 1]
  if (pos < 1 || pos > seq_list->size + 1) {
    return;
  }
  // 若pos == 1则是头部插入
  if (pos == 1) {
    insert_at_beginning(seq_list, data);
    return;
  }
  // 若pos == seq_list->size + 1 则是尾部插入
  if (pos == seq_list->size + 1) {
    insert_at_end(seq_list, data);
    return;
  }
  // 若插入位置在[2,seq_list->size]
  // 定义end保存顺序表尾部元素下标
  int end = seq_list->size - 1;
  while (end >= pos - 1) { // pos - 1为插入位置实际在顺序表中的下标
    seq_list->data[end + 1] = seq_list->data[end];
    end--;
  }
  // 插入数据
  seq_list->data[pos - 1] = data;
  seq_list->size++;
}
/*删除顺序表中某个位置上的数据*/
void delete_at_pos(seq_list_t *seq_list, int pos) {
  // 若seq_list和顺序表为空
  if (seq_list == NULL || seq_list->data == NULL)
    return;
  // 若删除位置不在可控范围内[1,seq_list->size]
  if (pos < 1 || pos > seq_list->size)
    return;
  // 若pos == 1,则头部删除
  if (pos == 1) {
    delete_from_beginning(seq_list);
    return;
    // 若pos == seq_list->size,则尾部删除
  } else if (pos == seq_list->size) {
    delete_from_end(seq_list);
    return;
  }
  // 若删除位置在[2,seq_list->size - 1]
  // 定义start保存pos所在顺序表的实际下标
  int start = pos - 1;
  // 定义after保存pos所在顺序表的后一个数据元素的下标
  int after = pos;
  while (start <= seq_list->size - 2) {
    seq_list->data[start] = seq_list->data[after];
    start++;
    after++;
  }
  seq_list->size--;
  return;
}
