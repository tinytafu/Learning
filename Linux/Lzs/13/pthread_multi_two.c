// 多个线程:输出的顺序大不相同

#include <tytofu.h>

static void *thread_start(void *arg) {
  long p = (long)arg;
  printf("p is %ld\n", p);
  return NULL;
}
int main(int argc, char *argv[]) {
  long i = 100;
  pthread_t tid1, tid2, tid3;
  pthread_create(&tid1, NULL, thread_start, (void *)i);
  i++;
  pthread_create(&tid2, NULL, thread_start, (void *)i);
  i++;
  pthread_create(&tid3, NULL, thread_start, (void *)i);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);
  return EXIT_SUCCESS;
}
