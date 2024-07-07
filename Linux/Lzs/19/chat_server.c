#include <tytofu.h>

int main(int argc, char *argv[]) {
  //./chat_server 0.0.0.0 46464
  ARGS_CHECK(argc, 3);
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sockfd, -1, "socket");
  // 设置需要绑定的ip+port
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);
  // 绑定之前无视TIME_WAIT
  int optval = 1;
  int ret_setsockopt =
      setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
  ERROR_CHECK(ret_setsockopt, -1, "setsockopt");
  // 调用bind绑定ip+port到socket
  int ret_bind =
      bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  ERROR_CHECK(ret_bind, -1, "bind");
  // 调用listen开始侦听,此时socket文件对象数据结构被重新构建
  // 一个是半连接的队列
  // 一个是全连接的队列
  int ret_listen = listen(sockfd, 50);
  ERROR_CHECK(ret_listen, -1, "listen");

  // 设置监听集合,就绪集合
  fd_set monitor_set;
  fd_set ready_set;
  // 初始化监听集合,就绪集合
  FD_ZERO(&monitor_set);
  FD_ZERO(&ready_set);
  // 将需要监听的对象添加到监听集合
  FD_SET(sockfd, &monitor_set);
  // 设置保存数据的数组和保存新连接的通信socket描述符
  char buf[4096];
  int netfd[4] = {0};
  for (int i = 0; i < 4; i++) {
    netfd[i] = -1;
  }
  int index = 0;
  while (1) {
    memcpy(&ready_set, &monitor_set, sizeof(monitor_set));
    select(10, &ready_set, NULL, NULL, NULL);
    if (FD_ISSET(sockfd, &ready_set)) {
      int ret_accept = accept(sockfd, NULL, NULL);
      ERROR_CHECK(ret_accept, -1, "accept");
      // 超出服务器构建通信socket数量,关闭新建的通信socket文件对象
      if (index > 3) {
        close(ret_accept);
        continue;
      }
      netfd[index] = ret_accept;
      // 清空就绪集合
      FD_ZERO(&ready_set);
      // 将新的通信socket文件对象的描述符加入监听集合
      FD_SET(netfd[index], &monitor_set);
      index++;
      continue;
    }
    for (int i = 0; i < index; i++) {
      if (FD_ISSET(netfd[i], &ready_set)) {
        bzero(buf, sizeof(buf));
        // 读取通信socket文件对象中的读缓冲区
        ssize_t rret = recv(netfd[i], buf, sizeof(buf), 0);
        ERROR_CHECK(rret, -1, "recv");
        // 如果rret为0,则对端的写端关闭,客户端退出,在服务端关闭对应的文件对象
        if (rret == 0) {
          // 关闭文件对象
          close(netfd[i]);
          // index减去一
          index--;
          // 直接退出此次循环,进行下一次轮询
          break;
        }
        for (int j = 0; j < index; j++) {
          if (j == i)
            continue;
          else {
            // 将读取到的数据分别发送给其他通信socket文件对象内的写缓冲区
            ssize_t wret = send(netfd[j], buf, rret, 0);
            ERROR_CHECK(wret, -1, "send");
          }
        }
      }
    }
  }
  return EXIT_SUCCESS;
}
