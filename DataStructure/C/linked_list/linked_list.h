// 数据元素类型
typedef int elem_t;
// 链表结点类型
typedef struct node {
  elem_t data;
  struct node *next;
} node_t;

/*初始化链表*/
void init_linked_list(node_t **pphead);
/*打印链表的数据*/
void print_linked_list(node_t *phead);

/*链表头部插入数据元素*/
void insert_at_beginning(node_t **pphead, elem_t data);
/*链表头部删除数据元素*/
void delete_from_beginning(node_t **pphead);

/*链表尾部插入数据元素*/
void insert_at_end(node_t **pphead, elem_t data);
/*链表尾部删除数据元素*/
void delete_from_end(node_t **pphead);

/*删除某个数据元素的后一个数据元素*/
void delete_after(node_t *cur);
/*删除特定位置上的数据元素*/
void delete_at_pos(node_t **pphead, int pos);

/*---------------------题目---------------------------*/
/*1.反转链表*/
node_t *reversal(node_t *phead);
node_t *reversal_two(node_t *phead);
