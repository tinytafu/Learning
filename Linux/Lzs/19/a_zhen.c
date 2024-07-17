#include <string.h>
#include <tytofu.h>
#define NUM 1024
int main(int argc, char *argv[]) {
  // 检查参数个数
  ARGS_CHECK(argc, 3);
  // 打开socket文件
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sockfd, -1, "socket");

  // 设置ip + port
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);

  // 允许重用
  int reuse = 1;
  int ret_setsockopt =
      setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
  ERROR_CHECK(ret_setsockopt, -1, "setsockopt");

  // 将ip+port绑定到sockfd
  int ret_bind =
      bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  ERROR_CHECK(ret_bind, -1, "bind");

  // 侦听
  int ret_listen = listen(sockfd, 50);
  ERROR_CHECK(ret_listen, -1, "listen");

  // 创建监听集合和就绪集合
  fd_set monitor_set;
  fd_set ready_set;
  // 初始化监听集合
  FD_ZERO(&monitor_set);
  // 将监听的对象添加到监听集合
  FD_SET(sockfd, &monitor_set);
  // 创建一个数据结构保存需要与连接的客户端
  // 进行通信的通信文件对象描述符
  int netfd[NUM];
  for (int i = 0; i < NUM; i++) {
    // 在未建立通信对象之前,将数据元素的值都初始化-1
    netfd[i] = -1;
  }
  // 下一个描述符所在的netfd下标
  int index = 0;
  // 创建一个哈希表 -- 使用netfd中保存的文件描述符作为下标
  // 下标对应的值为netfd的下标 -- 比如文件描述符5在netfd的下标1
  // 那么在哈希表中下标就是5 值就是1
  int fdToindex[NUM];
  for (int i = 0; i < NUM; i++) {
    fdToindex[i] = -1;
  }
  while (1) {
    // 将监听集合的数据拷贝到就绪集合用于select监听
    memcpy(&ready_set, &monitor_set, sizeof(fd_set));
    select(1024, &ready_set, NULL, NULL, NULL);
    // 若监听到sockfd就绪,全连接中有连接
    if (FD_ISSET(sockfd, &ready_set)) {
      // 取出连接,创建一个通信socket对象与客户端通信
      int ret_accept = accept(sockfd, NULL, NULL);
      ERROR_CHECK(ret_accept, -1, "accept");
      // netfd保存文件描述符
      netfd[index] = ret_accept;
      // fdToindex建立文件描述符与netfd下标的key value关系
      fdToindex[ret_accept] = index;
      // 将通信socket对象加入到监听集合
      FD_SET(netfd[index], &monitor_set);
      // 下标加1
      index++;
    }
  }
  return EXIT_SUCCESS;
}
