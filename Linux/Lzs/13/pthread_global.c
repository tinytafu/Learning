// 多线程访问.data段的数据
#include <tytofu.h>
int global = 10;

static void *thread_start(void *arg) {
  printf("global is %d\n", global);
  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t tid;
  // 创建一个子线程
  pthread_create(&tid, NULL, thread_start, NULL);
  // 对global进行修改
  global = 11;
  printf("main global is %d\n", global);
  pthread_join(tid, NULL);
  return EXIT_SUCCESS;
}
