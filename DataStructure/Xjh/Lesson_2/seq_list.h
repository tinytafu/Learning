#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
/*静态顺序表

顺序表的最大容量
#define SEQ_SIZE 1024

元素类型
typedef int elem_t;

描述一个顺序表: 顺序表如何存储,顺序表大小
struct sequence{
  数组形式存储数据
  elem_t data[SEQ_SIZE];
  顺序表的长度
  int length;
};
*/
/*-----动态顺序表-----*/

/*数据元素类型*/
typedef int elem_t;

/*描述和管理一个顺序表
 * 1.顺序表数据元素如何存储
 * 2.顺序表有效数据个数
 * 3.顺序表容量空间大小*/
typedef struct sequence_list {
  /*以指针形式保存在堆上申请的内存空间的首地址以管理数据*/
  elem_t* data;
  /*顺序表有效数据的个数*/
  size_t size;
  /*顺序表容量空间的大小*/
  size_t capicity;
}seq_list_t;

/*-----Initialize Start-----*/

/*-----seq_list_t pointer-----*/
void init_seq_list_pointer(seq_list_t** seq_list,size_t capicity);

/*-----seq_list object*/
void init_seq_list_object(seq_list_t* seq_list,size_t capicity);

/*-----Initialize End*/

/*-----print seq_list -----*/

void print_seq_list(seq_list_t* seq_list);

/*-----print seq_list-----*/

/*-----Insert Start-----*/

/*1.头部插入*/
void push_front_in_seq_list(seq_list_t* seq_list,elem_t element);
/*2.尾部插入*/
void push_back_in_seq_list(seq_list_t* seq_list,elem_t element);
/*3.除头尾外,任意位置的插入*/
void insert_in_seq_list(seq_list_t* seq_list,int pos,elem_t element);

/*-----Insert End*/

/*-----Erase Start-----*/

/*1.头部删除*/
void pop_front_in_seq_list(seq_list_t* seq_list);
/*2.尾部删除*/
void pop_back_in_seq_list(seq_list_t* seq_list);
/*3.除头尾外,任意位置的删除*/
void erase_in_seq_list(seq_list_t* seq_list,int pos);
/*-----Erase End*/

#endif
