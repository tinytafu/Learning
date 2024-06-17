#include <tytofu.h>

int main() {
  if (fork()) {
    while (1) {
      sleep(1);
    }
  } else {
    return 0;
  }
}
