#include <tytofu.h>

int main(int argc, char *argv[]) {
  // 检查参数个数
  ARGS_CHECK(argc, 3);

  // 打开socket文件
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sockfd, -1, "sockfd");

  // 设置需要连接的ip + port
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);

  // 连接服务器
  int ret_connect =
      connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  ERROR_CHECK(ret_connect, -1, "connect");

  // 设置监听集合
  fd_set ready_set;
  fd_set monitor_set;
  FD_ZERO(&monitor_set);
  // 添加监听对象到监听集合
  FD_SET(STDIN_FILENO, &monitor_set);
  FD_SET(sockfd, &monitor_set);
  char buf[4096] = {0};
  while (1) {
    FD_ZERO(&ready_set);
    memcpy(&ready_set, &monitor_set, sizeof(monitor_set));
    int ret = select(sockfd + 1, &ready_set, NULL, NULL, NULL);
    if (FD_ISSET(sockfd, &ready_set)) {
      // 读取socket文件对象内的读缓冲区的数据
      bzero(buf, sizeof(buf));
      ssize_t rret = recv(sockfd, buf, sizeof(buf), 0);
      ERROR_CHECK(rret, -1, "recv");
      // 判断是否读取的为0
      if (rret == 0) {
        break;
      }
      // 将读取到的数据发送到标准输出
      ssize_t wret = write(STDOUT_FILENO, buf, rret);
      ERROR_CHECK(wret, -1, "write");
    }
    if (FD_ISSET(STDIN_FILENO, &ready_set)) {
      // 读取标准输入中的数据
      bzero(buf, sizeof(buf));
      ssize_t rret = read(STDIN_FILENO, buf, sizeof(buf));
      ERROR_CHECK(rret, -1, "read");
      // 将读取到的数据发送到socket文件对象中的写缓冲区
      ssize_t wret = send(sockfd, buf, rret, 0);
      ERROR_CHECK(wret, -1, "send");
    }
  }
  return EXIT_SUCCESS;
}
