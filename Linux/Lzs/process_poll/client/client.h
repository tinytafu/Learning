#include <tytofu.h>
#define CHECK_MYSELF(ret, num)                                                 \
  {                                                                            \
    if (ret == num)                                                            \
      return num;                                                              \
  }
// 建立连接
int establishConnection(const char *ip, const char *port);
// 添加需要监听的文件对象到监听集合
int addMonitor(int epfd, int sockfd, struct epoll_event *event);
// 处理sockfd
int dealSockfd(int sockfd, char *buf, int buf_size);
int dealStdin(int stdinfd, int sockfd, char *buf, int buf_size);
