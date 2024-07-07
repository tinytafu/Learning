#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <tytofu.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  //./a_qiang 192.168.0.103 2626
  ARGS_CHECK(argc, 3);
  // 打开socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sockfd, -1, "socket");
  // 设置要连接的ip和port
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);
  // 调用connect,发送第一次握手
  int ret_connect =
      connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  ERROR_CHECK(ret_connect, -1, "connect");

  // 设置监听集合
  fd_set ready_set;
  char buf[4096];
  while (1) {
    // 初始化监听集合
    FD_ZERO(&ready_set);
    // 添加监听对象
    FD_SET(sockfd, &ready_set);
    FD_SET(STDIN_FILENO, &ready_set);
    // 调用select
    select(sockfd + 1, &ready_set, NULL, NULL, NULL);
    if (FD_ISSET(sockfd, &ready_set)) {
      bzero(buf, sizeof(buf));
      // 读取通信socket文件对象中的读缓冲区
      ssize_t rret = recv(sockfd, buf, sizeof(buf), 0);
      ERROR_CHECK(rret, -1, "recv");
      // 若服务端断开,则客户端也终止
      if (rret == 0) {
        break;
      }
      // 将读取到的数据输出到stdout
      ssize_t wret = write(STDOUT_FILENO, buf, rret);
      ERROR_CHECK(wret, -1, "write");
    }
    if (FD_ISSET(STDIN_FILENO, &ready_set)) {
      bzero(buf, sizeof(buf));
      // 读取stdin中的数据
      ssize_t rret = read(STDIN_FILENO, buf, sizeof(buf));
      ERROR_CHECK(rret, -1, "read");
      // 将读取到数据发送到socket文件对象中的写缓冲区
      ssize_t wret = send(sockfd, buf, rret, 0);
      ERROR_CHECK(wret, -1, "send");
    }
  }
  return EXIT_SUCCESS;
}
