// 读取目录项
#include <dirent.h>
#include <tytofu.h>

int main(int argc, char *argv[]) {
  ARGS_CHECK(argc, 2);
  // 打开一个目录
  DIR *dir;
  dir = opendir(argv[1]);
  ERROR_CHECK(dir, NULL, "opendir");

  // 读取打开的目录中的目录项
  struct dirent *pdirent;
  while ((pdirent = readdir(dir)) != NULL) {
    printf("%ld %ld %d %o %s\n", pdirent->d_ino, pdirent->d_off,
           pdirent->d_reclen, pdirent->d_type, pdirent->d_name);
  }

  closedir(dir);
}
