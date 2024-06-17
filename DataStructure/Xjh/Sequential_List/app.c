#include "seq_list.h"

/*测试顺序表算法*/
int main () {
  /*创建一个描述顺序表的数据类型的对象*/
  seq_list_t seq_list_object;
  /*定义顺序表的容量*/
  size_t capicity_object = 5;
  /*初始化顺序表*/
  init_seq_list_object(&seq_list_object, capicity_object);
  printf("seq_list_object->size = %zu\nseq_list->capicity_object = %zu\n",seq_list_object.size,seq_list_object.capicity);
  /*使用头部插入算法插入数据到顺序表*/
  for(size_t i = 0;i < 5;i++) {
    push_front_in_seq_list(&seq_list_object, i);
  }
  /*输出顺序表的数据元素的数据*/
  print_seq_list(&seq_list_object);
  /*在顺序表尾部插入数据*/
  insert_in_seq_list(&seq_list_object, 1, 5);
  print_seq_list(&seq_list_object);
  // /*使用尾部插入算法插入数据到顺序表*/
  // for (size_t i = 1;i < 3;i++)
  //   push_back_in_seq_list(&seq_list_object, i);
  // /*输出顺序表的数据元素的数据*/
  // print_seq_list(&seq_list_object);
  // /*在顺序表第2个位置上插入数据10*/
  // insert_in_seq_list(&seq_list_object, 2, 10);
  // /*输出顺序表的数据元素的数据*/
  // print_seq_list(&seq_list_object);
  //
}
