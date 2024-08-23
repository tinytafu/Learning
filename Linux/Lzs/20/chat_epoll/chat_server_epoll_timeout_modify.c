// epoll的聊天室
#include <sys/epoll.h>
#include <sys/socket.h>
#include <time.h>
#include <tytofu.h>
#define NUM 1024
// 与客户端通信的连接的数据类型
typedef struct element elem_t;
struct element {
  // 文件描述符
  int fd;
  // 活跃时间
  time_t now;
  // 当前通信的客户端地址
  struct sockaddr_in client_addr;
};
// 定义一个描述顺序表对数据类型
typedef struct sequence seq_list_t;
struct sequence {
  // 存储连接的物理结构
  elem_t *data;
  // 连接的个数
  int size;
};
// 初始化顺序表
void init_sequence(seq_list_t *seq_list) {
  if (seq_list == NULL)
    return;
  seq_list->data = (elem_t *)malloc(sizeof(elem_t) * NUM);
  for (int i = 0; i < NUM; i++) {
    seq_list->data[i].fd = -1;
    seq_list->data[i].now = -1;
    bzero(&seq_list->data[i].client_addr,
          sizeof(seq_list->data[i].client_addr));
  }
  seq_list->size = 0;
}
// 输出顺序表中连接的文件描述符
void print_sequence(seq_list_t *seq_list) {
  if (seq_list == NULL || seq_list->data == NULL || seq_list->size == 0)
    return;
  for (int i = 0; i < seq_list->size; i++) {
    printf("%d ", seq_list->data[i].fd);
  }
  printf("\n");
}
// 尾部插入
void push_back(seq_list_t *seq_list, int fd, time_t now,
               struct sockaddr_in client_addr) {
  if (seq_list == NULL || seq_list->data == NULL || seq_list->size > NUM)
    return;
  seq_list->data[seq_list->size].fd = fd;
  seq_list->data[seq_list->size].now = now;
  seq_list->data[seq_list->size].client_addr = client_addr;
  seq_list->size++;
}
// 任意位置删除
void delete_pos(seq_list_t *seq_list, int pos) {
  if (seq_list == NULL || seq_list->data == NULL || seq_list->size == 0)
    return;
  // 若尾部删除
  if (pos == seq_list->size - 1) {
    seq_list->size--;
    return;
  } else {
    int start = pos;
    while (start <= seq_list->size - 1) {
      seq_list->data[start].fd = seq_list->data[start + 1].fd;
      seq_list->data[start].now = seq_list->data[start + 1].now;
      seq_list->data[start].client_addr = seq_list->data[start + 1].client_addr;
      start++;
    }
    seq_list->size--;
    return;
  }
}
int main(int argc, char *argv[]) {
  //./chat_server_epoll_timeout 192.168.199.148 2626
  ARGS_CHECK(argc, 3);
  // 打开socket文件对象
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sockfd, -1, "socket");
  // 设置 ip + port
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);
  // 忽略TIME_OUT
  int reuse = 1;
  int ret_setsockopt =
      setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
  ERROR_CHECK(ret_setsockopt, -1, "setsockopt");
  // 绑定ip+port到sockfd
  int ret_bind =
      bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  ERROR_CHECK(ret_bind, -1, "bind");
  // 开启监听
  int ret_listen = listen(sockfd, 1024);
  ERROR_CHECK(ret_listen, -1, "listen");
  // 存储数据的缓冲区
  char buf[4096] = {0};
  // 定义存储连接数据的顺序表
  seq_list_t sequence;
  // 初始化顺序表
  init_sequence(&sequence);
  // 定义存储连接的文件描述符与顺序表中连接的下标的映射关系
  int fd_to_index[1024];
  for (int i = 0; i < 1024; i++)
    fd_to_index[i] = -1;
  // 调用epoll_create创建一个epoll实例->监听集合 就绪集合
  int epfd = epoll_create(526);
  ERROR_CHECK(epfd, -1, "epoll_create");
  // 当监听集合中有事件就绪的时候,内核会将就绪集合中的
  // 数据拷贝到用户态,因此需要在用户态定义一个存储就绪集合
  // 的数据结构,使用数组即可
  struct epoll_event ready_set[1024] = {0};
  // 将监听的对象添加到epoll实例中的监听集合,目前只需要监听sockfd即可
  // 设置监听对象属性
  struct epoll_event event;
  event.events = EPOLLIN;
  event.data.fd = sockfd;
  int ret_epoll_ctl = epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
  ERROR_CHECK(ret_epoll_ctl, -1, "epoll_ctl");
  // 定义保存客户端信息的对象
  struct sockaddr_in client_addr;
  socklen_t length = sizeof(client_addr);
  // 保存超时或者事件就绪的时间
  time_t now;
  while (1) {
    // 调用epoll_wait开启等待进行轮询
    int fd_number = epoll_wait(epfd, ready_set, 1024, 1000);
    now = time(NULL);
    printf("%s\n", ctime(&now));
    ERROR_CHECK(fd_number, -1, "epoll_wait");
    // fd_number是就绪集合中的个数,只需要对ready_set遍历即可
    // 因为ready_set中都是就绪的事件
    for (int i = 0; i < fd_number; i++) {
      if (ready_set[i].data.fd == sockfd) {
        int netfd = accept(sockfd, (struct sockaddr *)&client_addr, &length);
        ERROR_CHECK(netfd, -1, "accept");
        // 将此连接建立的通信socket的文件描述符添加到监听集合
        event.events = EPOLLIN;
        event.data.fd = netfd;
        int ret_epoll_ctl = epoll_ctl(epfd, EPOLL_CTL_ADD, netfd, &event);
        ERROR_CHECK(ret_epoll_ctl, -1, "epoll_ctl");
        // 将此连接添加到哈希表建立映射关系
        fd_to_index[netfd] = sequence.size;
        // 将此连接添加到顺序表
        push_back(&sequence, netfd, now, client_addr);
      } else {
        // 这个循环的目的是为了知道此时就绪的文件对象在顺序表中的下标.
        // 且还是对未就绪的对象遍历了一次,这样的效率就和select差不多了
        // 浪费了epoll的高性能
        // 但其实通过哈希表中的映射关系就可以找到下标,无需在循环一次.
        int netfd = ready_set[i].data.fd;
        // 利用netfd找到在顺序表对应的下标
        int index = fd_to_index[netfd];
        // 更新就绪时间
        sequence.data[index].now = time(NULL);
        bzero(buf, sizeof(buf));
        // 读取读缓冲区的数据
        int ret_recv = recv(sequence.data[index].fd, buf, sizeof(buf), 0);
        ERROR_CHECK(ret_recv, -1, "recv");
        if (ret_recv == 0) {
          // 移除监听列表
          int ret_epoll_ctl =
              epoll_ctl(epfd, EPOLL_CTL_DEL, sequence.data[index].fd, NULL);
          ERROR_CHECK(ret_epoll_ctl, -1, "epoll_ctl");
          // 关闭通信文件对象
          close(sequence.data[index].fd);
          // 移除映射关系
          fd_to_index[sequence.data[index].fd] = -1;
          // 将其从顺序表删除
          delete_pos(&sequence, index);
          // 若关闭的文件对象的下标在顺序表的最后一个,
          // 那么可直接映射关系,不需要考虑覆盖问题
          // 这个size是删除后的,所以不需要减去1
          if (sequence.size != index) {
            // 移除映射关系的同时,还需要考虑哈希表中其他文件对象的映射关系
            // 还是需要考虑使用循环遍历删除后剩余的顺序表元素
            // 使用顺序表剩余的元素的文件描述符去遍历哈希表,使它们的值都减去1
            // 做到与顺序表删除一个元素之后的一一对应
            for (int j = 0; j < sequence.size; j++) {
              fd_to_index[sequence.data[j].fd] -= 1;
            }
          }
          // 将其从顺序表中移除
          continue;
        }
        for (int j = 0; j < sequence.size; j++) {
          if (index != j) {
            // 这里strcat不出现段错误的原因是name存储的是一块堆内存,inet_ntoa函数
            // 返回的是保存若干字符数据的堆内存的首地址,是可被修改的区域
            // 但是若name存储的是可读区域中的首地址,那么就出现段错误
            /* char *name =
            inet_ntoa(sequence.data[j].client_addr.sin_addr); char
            *client_name = strcat(name, ": "); */
            // 发送端口号
            int ret_send = send(
                sequence.data[j].fd, &sequence.data[j].client_addr.sin_port,
                sizeof(sequence.data[j].client_addr.sin_port), 0);
            ERROR_CHECK(ret_send, -1, "send");
            // 发送客户端ip
            ret_send = send(sequence.data[j].fd,
                            &sequence.data[j].client_addr.sin_addr,
                            sizeof(sequence.data[j].client_addr.sin_addr), 0);
            ERROR_CHECK(ret_send, -1, "send");
            // 发送实际数据
            ret_send = send(sequence.data[j].fd, buf, ret_recv, 0);
            ERROR_CHECK(ret_send, -1, "send");
          }
        }
      }
    }
    // 查看各个连接上来的客户端是否超时
    for (int i = 0; i < sequence.size; i++) {
      if (now - sequence.data[i].now > 10) {
        // 移除监听集合
        int ret_epoll_ctl =
            epoll_ctl(epfd, EPOLL_CTL_DEL, sequence.data[i].fd, NULL);
        ERROR_CHECK(ret_epoll_ctl, -1, "epoll_ctl");
        // 关闭文件对象
        close(sequence.data[i].fd);
        // 移除哈希表映射
        fd_to_index[sequence.data[i].fd] = -1;
        // 在顺序表移除此元素
        delete_pos(&sequence, i);
        // 移除之后需要考虑哈希表映射问题
        if (sequence.size != i) {
          for (int j = 0; j < sequence.size; j++) {
            fd_to_index[sequence.data[j].fd] -= 1;
          }
        }
      }
    }
  }
  return EXIT_SUCCESS;
}
