#include <tytofu.h>

int main() {
  if (fork()) {
    return 0;
  } else {
    while (1) {
      sleep(1);
    }
  }
}
