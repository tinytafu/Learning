#include <sys/socket.h>
#include <tytofu.h>
#define NUM 100
// 顺序表中的元素类型
typedef struct element elem_t;
struct element {
  int fd;
  time_t time_now;
  struct sockaddr_in client_addr;
};
// 定义描述顺序表的类型
typedef struct sequence seq_list_t;
struct sequence {
  elem_t *data;
  int size;
};
// 初始化顺序表
void init_sequence(seq_list_t *seq_list) {
  if (seq_list == NULL)
    return;
  seq_list->data = (elem_t *)malloc(sizeof(elem_t) * NUM);
  for (int i = 0; i < NUM; i++) {
    seq_list->data[i].fd = -1;
    seq_list->data[i].time_now = 0;
  }
  seq_list->size = 0;
}
// 输出顺序表中数据元素中的fd
void print_sequence(seq_list_t *seq_list) {
  if (seq_list == NULL || seq_list->data == NULL || seq_list->size == 0) {
    return;
  }
  for (int i = 0; i < seq_list->size; i++) {
    printf("%d ", seq_list->data[i].fd);
  }
  printf("\n");
}
// 尾部插入
void push_back(seq_list_t *seq_list, int fd, time_t now,
               struct sockaddr_in *client_addr) {
  if (seq_list == NULL || seq_list->data == NULL || seq_list->size == NUM)
    return;
  seq_list->data[seq_list->size].fd = fd;
  seq_list->data[seq_list->size].time_now = now;
  seq_list->data[seq_list->size].client_addr = *client_addr;
  seq_list->size++;
}
// 任意位置删除
void delete_pos(seq_list_t *seq_list, int pos) {
  if (seq_list == NULL || seq_list->data == NULL || seq_list->size == 0)
    return;
  // 如果pos在尾部
  if (pos == seq_list->size - 1) {
    seq_list->size--;
    return;
  } else {
    int start = pos;
    while (start <= seq_list->size - 1) {
      seq_list->data[start].fd = seq_list->data[start + 1].fd;
      seq_list->data[start].time_now = seq_list->data[start + 1].time_now;
      seq_list->data[start].client_addr = seq_list->data[start + 1].client_addr;
      start++;
    }
    seq_list->size--;
    return;
  }
}
int main(int argc, char *argv[]) {
  //./chat_server_select_timeout 192.168.199.148 2626
  // 检查命令行参数个数
  ARGS_CHECK(argc, 3);
  // 打开socket文件对象,用于监听连接
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sockfd, -1, "socket");
  // 设置服务器ip + port并绑定到sockfd
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);
  // 绑定
  int ret_bind =
      bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  ERROR_CHECK(ret_bind, -1, "bind");
  // 监听客户端连接
  int ret_listen = listen(sockfd, 1024);
  ERROR_CHECK(ret_listen, -1, "listen");
  // 定义用户态缓冲区
  char buf[4096] = {0};
  // 定义监听集合、就绪集合
  fd_set monitor_set, ready_set;
  // 初始化集合
  FD_ZERO(&ready_set);
  FD_ZERO(&monitor_set);
  // 将监听对象添加到监听集合
  FD_SET(sockfd, &monitor_set);
  // 定义存储通信对象的描述符和等待时间的顺序表
  seq_list_t sequence;
  // 初始化顺序表
  init_sequence(&sequence);
  // 定义一个哈希表建立文件描述符与顺序表下标的映射关系,这样根据
  // 描述符可以找到在顺序表的位置
  int fd_to_index[NUM];
  for (int i = 0; i < NUM; i++)
    fd_to_index[i] = -1;
  // 设置select的超时时间
  struct timeval time_n;
  time_n.tv_sec = 1;
  time_n.tv_usec = 0;
  // 定义保存客户端ip+port的对象
  struct sockaddr_in client_addr;
  socklen_t length = sizeof(client_addr);
  // 定义保存获取就绪时间的对象
  time_t now;
  while (1) {
    // 将监听集合的数据拷贝到就绪集合
    memcpy(&ready_set, &monitor_set, sizeof(fd_set));
    // 调用select
    int ret_select = select(1024, &ready_set, NULL, NULL, &time_n);
    now = time(NULL);
    // printf("%s\n", ctime(&now));
    // 若超时导致select就绪,所有客户端不发送消息或者无连接
    if (ret_select == 0) {
      // 检查各个连接的就绪时间是否超时
      // 无连接时,sequence.size为0
      for (int i = 0; i < sequence.size; i++) {
        // 若此连接的就绪时间与当前时间只差等于10秒,则踢掉客户端
        if ((now - sequence.data[i].time_now) >= 10) {
          /* printf("%s:%d is disconnected!\n",
                 inet_ntoa(sequence.data[i].client_addr.sin_addr),
                 ntohs(sequence.data[i].client_addr.sin_port)); */
          // 从监听集合中移除
          FD_CLR(sequence.data[i].fd, &monitor_set);
          // 关闭文件对象
          close(sequence.data[i].fd);
          // 从顺序表中删除
          delete_pos(&sequence, i);
          // 移除哈希表中的映射
          fd_to_index[sequence.data[i].fd] = -1;
        }
      }
      continue;
    }
    if (FD_ISSET(sockfd, &ready_set)) {
      // 从sockfd中的全连接队列中取出一个连接建立与相应客户端对应的通信socket
      int netfd = accept(sockfd, (struct sockaddr *)&client_addr, &length);
      // 获取此连接的就绪时间
      now = time(NULL);
      // 将此连接添加到监听集合中
      FD_SET(netfd, &monitor_set);
      // 将此文件描述符与顺序表的下标进行映射,注意顺序
      // 由于添加到顺序表的函数中会将size加1,那么
      // 映射关系就不正确了
      fd_to_index[netfd] = sequence.size;
      // 将此连接对应的各个属性添加到顺序表中
      push_back(&sequence, netfd, now, &client_addr);
      /* printf("%s:%d:%s is connected!\n",
             inet_ntoa(sequence.data[sequence.size - 1].client_addr.sin_addr),
             ntohs(sequence.data[sequence.size - 1].client_addr.sin_port),
             ctime(&now)); */
      continue;
    }
    for (int i = 0; i < sequence.size; i++) {
      if (sequence.data[i].fd != -1 &&
          FD_ISSET(sequence.data[i].fd, &ready_set)) {
        now = time(NULL);
        // 更新此连接的就绪时间
        sequence.data[i].time_now = now;
        /* printf("%s:%d:%s update time\n",
               inet_ntoa(sequence.data[i].client_addr.sin_addr),
               ntohs(sequence.data[i].client_addr.sin_port), ctime(&now)); */
        // 读取通信文件对象中读缓冲区的数据
        bzero(buf, sizeof(buf));
        ssize_t ret_recv = recv(sequence.data[i].fd, buf, sizeof(buf), 0);
        ERROR_CHECK(ret_recv, -1, "recv");
        // 若读取的数据为0
        if (ret_recv == 0) {
          printf("%s:%d exit proactively!\n",
                 inet_ntoa(sequence.data[i].client_addr.sin_addr),
                 ntohs(sequence.data[i].client_addr.sin_port));
          // 将此连接移除监听集合
          FD_CLR(sequence.data[i].fd, &monitor_set);
          // 关闭此连接对应的文件对象
          close(sequence.data[i].fd);
          // 删除此下标对应的顺序表元素
          delete_pos(&sequence, i);
          // 将哈希表中的映射关系移除
          fd_to_index[sequence.data[i].fd] = -1;
          continue;
        }
        // 检查其他连接是否超时,若超时则踢掉客户端不进行发送数据
        // 检查各个连接的就绪时间是否超时
        // 无连接时,sequence.size为0
        for (int i = 0; i < sequence.size; i++) {
          // 若此连接的就绪时间与当前时间只差等于10秒,则踢掉客户端
          if ((now - sequence.data[i].time_now) >= 10) {
            /* printf("%s:%d is disconnected!\n",
                   inet_ntoa(sequence.data[i].client_addr.sin_addr),
                   ntohs(sequence.data[i].client_addr.sin_port)); */
            // 从监听集合中移除
            FD_CLR(sequence.data[i].fd, &monitor_set);
            // 关闭文件对象
            close(sequence.data[i].fd);
            // 从顺序表中删除
            delete_pos(&sequence, i);
            // 移除哈希表中的映射
            fd_to_index[sequence.data[i].fd] = -1;
          }
        }
        for (int j = 0; j < sequence.size; j++) {
          if (sequence.data[j].fd != -1 && i != j) {
            int ret_send = send(sequence.data[j].fd, buf, ret_recv, 0);
            ERROR_CHECK(ret_send, -1, "send");
          }
        }
      }
    }
  }
  return EXIT_SUCCESS;
}
