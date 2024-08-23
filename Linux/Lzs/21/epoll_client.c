#include <strings.h>
#include <sys/epoll.h>
#include <tytofu.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  //./epoll_client 192.168.199.148 2626
  ARGS_CHECK(argc, 3);
  // 打开一个socket文件对象
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sockfd, -1, "socket");

  // 设置需要连接的ip+port
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);

  // 调用connect连接,发送第一次握手
  int ret_connect =
      connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  ERROR_CHECK(ret_connect, -1, "connect");

  // 使用epoll对需要监听的对象进行监听,当事件就绪时执行相应的操作
  // 创建一个epoll实例
  int epfd = epoll_create(1);
  ERROR_CHECK(epfd, -1, "epoll_create");
  // 将监听对象添加到epoll实例中的监听集合
  struct epoll_event event;
  event.events = EPOLLIN;
  event.data.fd = sockfd;
  int ret_epoll_ctl = epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
  ERROR_CHECK(ret_epoll_ctl, -1, "epoll_ctl");
  event.events = EPOLLIN;
  event.data.fd = STDIN_FILENO;
  ret_epoll_ctl = epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
  ERROR_CHECK(ret_epoll_ctl, -1, "epoll_ctl");
  // 由于当事件就绪的时候,操作系统会将epoll实例中的就绪集合的数据
  // 拷贝到用户态,因此需要在用户态创建一个数据结构进行保存
  struct epoll_event events[2];
  // 缓冲区
  char buf[11] = {0};
  // 编写一个eventloop
  while (1) {
    // 将用户态就绪集合清空
    bzero(events, sizeof(events));
    // 调用epoll_wait
    int readyNum = epoll_wait(epfd, events, 2, -1);
    ERROR_CHECK(readyNum, -1, "epoll_wait");
    // 当epoll_wait就绪时,利用返回值遍历就绪集合
    for (int i = 0; i < readyNum; i++) {
      if (events[i].data.fd == sockfd) {
        // 清空缓冲区
        bzero(buf, sizeof(buf));
        // 读取sockfd文件对象中的数据
        int ret_recv = recv(sockfd, buf, sizeof(buf), 0);
        if (ret_recv == 0)
          break;
        ERROR_CHECK(ret_recv, -1, "recv");
        // 将读取到的数据发送到stdout
        int ret_write = write(STDOUT_FILENO, buf, ret_recv);
        ERROR_CHECK(ret_write, -1, "write");
      } else if (events[i].data.fd == STDIN_FILENO) {
        // 清空缓冲区
        bzero(buf, sizeof(buf));
        // 读取stdin中的数据
        int ret_read = read(STDIN_FILENO, buf, sizeof(buf));
        // 去除换行符
        buf[ret_read - 1] = '\0';
        printf("ret_read is %d\n", ret_read);
        if (ret_read == 0)
          break;
        ERROR_CHECK(ret_read, -1, "read");
        // 将读取到的数据发送到sockfd对应的网络文件对象
        int ret_send = send(sockfd, buf, ret_read, 0);
        ERROR_CHECK(ret_send, -1, "send");
      }
    }
  }
  return EXIT_SUCCESS;
}
