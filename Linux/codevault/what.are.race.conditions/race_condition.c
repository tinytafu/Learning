#include <tytofu.h>

long global = 0;

void *routine(void *arg) {
  for (int i = 0; i < 10000; i++) {
    global++;
    // read global;
    // increment;
    // write global
  }
  return NULL;
}
int main() {
  pthread_t t1, t2;
  // 创建第一个线程
  if (pthread_create(&t1, NULL, routine, NULL) != 0)
    return 1;
  if (pthread_create(&t2, NULL, routine, NULL) != 0)
    return 1;
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  printf("global is %ld\n", global);
  return EXIT_SUCCESS;
}
