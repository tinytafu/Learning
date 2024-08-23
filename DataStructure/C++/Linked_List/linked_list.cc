#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;
/*将结点类型定义在类内类外都是可以的*/
using node_t = struct node_s;
using elem_t = int;
struct node_s {
  node_s(elem_t val = 0) : data_{val}, next_{nullptr} {}
  elem_t data_;
  node_t *next_;
};

class Link {
public:
  Link(node_t *head = nullptr) : head_{head} {}
  ~Link() {
    node_t *cur = head_->next_;
    while (cur) {
      delete head_;
      head_ = cur;
      cur = cur->next_;
    }
    delete head_;
    head_ = nullptr;
  }

public:
  /*单链表的尾插法O(n)*/
  void insert_tail(elem_t val) {
    /*1.生成一个虚拟结点当做整个链表的头结点便于多种情况的尾部插入
     * 虚拟结点先需要保存头指针指向的结点地址便于头指针不会失去对整个链表的控制
     * 随后头指针指向这个虚拟结点*/
    node_t *dummy_node = new node_t{0};
    dummy_node->next_ = head_;
    head_ = dummy_node;
    /*2.进行尾部插入,结合尾结点的特点:地址域为nullptr,因此
     * 对整个链表进行遍历,如果某个结点的地址域为nullptr
     * 则这个结点就是尾部结点*/
    node_t *tail = head_;
    while (tail->next_ != nullptr)
      tail = tail->next_;
    /*3.生成一个要插入的结点*/
    node_t *new_node = new node_t{val};
    /*4.尾部结点的地址域存储这个新结点的地址*/
    tail->next_ = new_node;
    /*5.将虚拟结点释放,并使的头指针指向整个链表的头部*/
    head_ = dummy_node->next_;
    delete dummy_node;
  }
  /*单链表的头插法O(1)*/
  void insert_head(int val) {
    /*1.无需设置虚拟结点*/
    /*2.生成一个要插入的结点*/
    node_t *new_node = new node_t{val};
    /*3.新结点的next_存储原先头指针存储的首结点的地址*/
    new_node->next_ = head_;
    /*4.head_存储新结点的地址*/
    head_ = new_node;
  }
  /*根据给定的值删除特定结点:若重复只删除一个*/
  void remove_all(int val) {
    if (head_ == nullptr)
      return;
    /*利用虚拟结点*/
    node_t *dummy_node = new node_t{-1};
    dummy_node->next_ = head_;
    head_ = dummy_node;
    node_t *pre = head_;        /*指向虚拟结点*/
    node_t *cur = head_->next_; /*指向首结点*/
    while (cur != nullptr) {
      if (cur->data_ == val) {
        /*断开当前结点与前结点的链接*/
        pre->next_ = cur->next_;
        /*释放当前结点*/
        delete cur;
        break;
      } else {
        /*向后继续遍历*/
        pre = cur;
        cur = cur->next_;
      }
    }
    head_ = dummy_node->next_;
    delete dummy_node;
  }
  /*根据给定的值*/
  /*打印链表结点中的数据*/
  void show() {
    node_t *cur = head_;
    while (cur) {
      cout << cur->data_ << " ";
      cur = cur->next_;
    }
    cout << endl;
  }

private:
  node_t *head_; /*指向整个链表起始位置的头指针*/
};
void test() {
  Link link;
  srand((unsigned int)time(NULL));
  for (int i = 0; i < 10; i++) {
    link.insert_head(rand() % 100 + 1);
    link.show();
  }
  link.show();
}
int main() {
  test();
  return 0;
}
