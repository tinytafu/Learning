#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <tytofu.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  //./chat_client 192.16.0.103 46464
  ARGS_CHECK(argc, 3);
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sockfd, -1, "socket");
  // 设置要连接的ip+port
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);
  // 开始连接
  int ret_connect =
      connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

  // 创建一个监听集合
  fd_set monitor_set;
  char buf[4096];
  while (1) {
    // 初始化监听集合
    FD_ZERO(&monitor_set);
    // 将需要监听的stdin和sockfd添加到监听集合
    FD_SET(STDIN_FILENO, &monitor_set);
    FD_SET(sockfd, &monitor_set);
    // 调用select开始轮询检测
    select(sockfd + 1, &monitor_set, NULL, NULL, NULL);
    if (FD_ISSET(sockfd, &monitor_set)) {
      bzero(buf, sizeof(buf));
      // 读取sockfd对应的文件对象中的读缓冲区
      ssize_t rret = recv(sockfd, buf, sizeof(buf), 0);
      ERROR_CHECK(rret, -1, "recv");
      if (rret == 0) {
        break;
      }
      // 将读取到的数据写入到stdout
      ssize_t wret = write(STDOUT_FILENO, buf, rret);
      ERROR_CHECK(wret, -1, "write");
    }
    if (FD_ISSET(STDIN_FILENO, &monitor_set)) {
      bzero(buf, sizeof(buf));
      // 读取stdin的数据
      ssize_t rret = read(STDIN_FILENO, buf, sizeof(buf));
      ERROR_CHECK(rret, -1, "read");
      // 将数据发送到sockfd对应的文件对象中的写缓冲区
      ssize_t wret = send(sockfd, buf, rret, 0);
      ERROR_CHECK(wret, -1, "send");
    }
  }
  return EXIT_SUCCESS;
}
