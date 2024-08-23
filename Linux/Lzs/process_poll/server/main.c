#include <tytofu.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  //./main 192.168.199.148 2626
  ARGS_CHECK(argc, 3);
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sockfd, -1, "sockfd");
  struct sockaddr_in serverAddr = {.sin_family = AF_INET,
                                   .sin_port = htons(atoi(argv[2])),
                                   .sin_addr.s_addr = inet_addr(argv[1])};
  int reuse = 1;
  int ret_setsockopt =
      setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
  ERROR_CHECK(ret_setsockopt, -1, "setsockopt");
  int ret_bind =
      bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  ERROR_CHECK(ret_bind, -1, "bind");
  int ret_listen = listen(sockfd, 1024);
  ERROR_CHECK(ret_listen, -1, "listen");
  int netfd = accept(sockfd, NULL, NULL);
  ERROR_CHECK(netfd, -1, "accept");
  int epfd = epoll_create(1);
  ERROR_CHECK(epfd, -1, "epfd");
  struct epoll_event event = {
      .data.fd = netfd,
      .events = EPOLLIN,
  };
  int ret_epoll_ctl = epoll_ctl(epfd, EPOLL_CTL_ADD, netfd, &event);
  ERROR_CHECK(ret_epoll_ctl, -1, "epoll_ctl");
  event.events = EPOLLIN;
  event.data.fd = STDIN_FILENO;
  ret_epoll_ctl = epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
  ERROR_CHECK(ret_epoll_ctl, -1, "epoll_ctl");
  char buf[4096] = {0};
  struct epoll_event readySet[2] = {0};
  while (1) {
    bzero(readySet, sizeof(readySet));
    int readyNum = epoll_wait(epfd, readySet, 2, -1);
    ERROR_CHECK(readyNum, -1, "epoll_wait");
    for (int i = 0; i < readyNum; i++) {
      if (readySet[i].data.fd == netfd) {
        int ret = recv(netfd, buf, sizeof(buf), 0);
        if (ret == 0)
          exit(-1);
        ERROR_CHECK(ret, -1, "recv");
        int ret_write = write(STDOUT_FILENO, buf, ret);
        ERROR_CHECK(ret_write, -1, "write");
      } else {
        int ret_read = read(STDIN_FILENO, buf, sizeof(buf));
        ERROR_CHECK(ret_read, -1, "read");
        int ret_send = send(netfd, buf, ret_read, 0);
        ERROR_CHECK(ret_send, -1, "send");
      }
    }
  }
  return EXIT_SUCCESS;
}
