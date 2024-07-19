// 为顺序表数据元素类型重定义名称
typedef int elem_t;
/*定义一个描述顺序表的类型
 * 1.包含用于存储顺序表元素的的动态数组
 * 2.包含用于存储顺序表大小的对象
 * 3.包含用于存储顺序表容量的对象
 */
typedef struct sequential_list {
  // 动态数组保存数据元素
  elem_t *data;
  // 保存顺序表的大小
  int size;
  // 保存顺序表的容量
  unsigned int capacity;
} seq_list_t;

/*初始化描述顺序表的对象中的成员*/
void init_seq_list(seq_list_t *seq_list, unsigned int capacity);
/*打印顺序表中数据元素的数据*/
void print_seq_list(seq_list_t *seq_list);
/*查找顺序表中是否包含特定数据的数据元素,返回所在顺序表位置*/
int find_seq_list(seq_list_t *seq_list, elem_t data);

/*在顺序表头部插入数据*/
void insert_at_beginning(seq_list_t *seq_list, elem_t data);
/*在顺序表尾部插入数据*/
void insert_at_end(seq_list_t *seq_list, elem_t data);

/*在顺序表头部删除数据*/
void delete_from_beginning(seq_list_t *seq_list);
/*在顺序表尾部删除数据*/
void delete_from_end(seq_list_t *seq_list);
/*在指定位置插入元素*/
void insert_at_pos(seq_list_t *seq_list, int pos, elem_t data);
/*在指定位置删除元素*/
void delete_at_pos(seq_list_t *seq_list, int pos);
