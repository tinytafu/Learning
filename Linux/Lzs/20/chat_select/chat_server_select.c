// 基于select的聊天室
#include <string.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <tytofu.h>
#define NUM 1024
typedef struct sequence_list seq_list_t;
// 定义一个描述顺序表的结构体类型
struct sequence_list {
  int *netfd;
  int size;
};
// 初始化顺序表
void init_sequence(seq_list_t *seq_list) {
  if (seq_list == NULL)
    return;
  seq_list->netfd = (int *)malloc(sizeof(int) * NUM);
  for (int i = 0; i < NUM; i++) {
    seq_list->netfd[i] = -1;
  }
  seq_list->size = 0;
}
// 遍历顺序表
void print_sequence_list(seq_list_t *seq_list) {
  if (seq_list == NULL || seq_list->size == 0) {
    return;
  }
  for (int i = 0; i < seq_list->size; i++) {
    printf("%d ", seq_list->netfd[i]);
  }
  printf("\n");
}
// 尾部插入
void push_back(seq_list_t *seq_list, int fd) {
  if (seq_list == NULL || seq_list->netfd == NULL)
    return;
  seq_list->netfd[seq_list->size] = fd;
  seq_list->size++;
}
// 任意位置删除
void delete_pos(seq_list_t *seq_list, int pos) {
  if (seq_list == NULL)
    return;
  if (pos < 0 || pos > seq_list->size - 1)
    return;
  if (pos == seq_list->size - 1) {
    seq_list->size--;
    return;
  } else {
    int start = pos;
    while (start < seq_list->size - 1) {
      seq_list->netfd[start] = seq_list->netfd[start + 1];
      start++;
    }
    seq_list->size--;
    return;
  }
}
int main(int argc, char *argv[]) {
  //./chat_server_select 192.168.199.148 2626
  ARGS_CHECK(argc, 3);
  // 打开一个socket文件对象
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sockfd, -1, "sockfd");
  // 设置需要绑定的ip + port
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);
  // 忽略TIME_WAIT

  // 绑定ip + port到sockfd
  int ret_bind =
      bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  ERROR_CHECK(ret_bind, -1, "bind");
  // 监听连接
  int ret_listen = listen(sockfd, 100);
  ERROR_CHECK(ret_listen, -1, "listen");
  // 创建监听集合和就绪集合
  fd_set monitor_set, ready_set;
  // 初始化这两个集合
  FD_ZERO(&monitor_set);
  FD_ZERO(&ready_set);
  // 将此时管理半连接和全连接的文件对象添加到监听集合中
  FD_SET(sockfd, &monitor_set);
  // 创建一个存储与客户端通信的通信socket文件对象描述符
  seq_list_t sequence;
  // 初始化顺序表
  init_sequence(&sequence);
  // 创建一个哈希表,用来管理文件描述符与顺序表的下标的对应关系
  int fd_to_index[NUM];
  for (int i = 0; i < NUM; i++) {
    fd_to_index[i] = -1;
  }
  // 临时存储数据
  char buf[4096] = {0};
  while (1) {
    memcpy(&ready_set, &monitor_set, sizeof(fd_set));
    // 调用select
    int ret_select = select(1024, &ready_set, NULL, NULL, NULL);
    if (FD_ISSET(sockfd, &ready_set)) {
      int netfd = accept(sockfd, NULL, NULL);
      ERROR_CHECK(netfd, -1, "accept");
      // 将此通信文件对象添加到顺序表中
      push_back(&sequence, netfd);
      // 将此通信文件对象添加到监听集合
      FD_SET(netfd, &monitor_set);
      // 添加映射关系到哈希表
      fd_to_index[netfd] = sequence.size;
      continue;
    }
    for (int i = 0; i < sequence.size; i++) {
      if (sequence.netfd[i] != -1 && FD_ISSET(sequence.netfd[i], &ready_set)) {
        bzero(buf, sizeof(buf));
        int ret_recv = recv(sequence.netfd[i], buf, sizeof(buf), 0);
        ERROR_CHECK(ret_recv, -1, "recv");
        if (ret_recv == 0) {
          // 客户端断开
          // 将此文件描述符从监听集合移除
          FD_CLR(sequence.netfd[i], &monitor_set);
          // 关闭文件对象
          close(sequence.netfd[i]);
          // 删除顺序表中处于i位置的元素
          delete_pos(&sequence, i);
          // 移除哈希表中的映射关系
          fd_to_index[sequence.netfd[i]] = -1;
          continue;
        }
        for (int j = 0; j < sequence.size; j++) {
          if (sequence.netfd[i] != -1 && i != j) {
            int ret_send = send(sequence.netfd[j], buf, ret_recv, 0);
            ERROR_CHECK(ret_send, -1, "send");
          }
        }
      }
    }
  }
  return EXIT_SUCCESS;
}
