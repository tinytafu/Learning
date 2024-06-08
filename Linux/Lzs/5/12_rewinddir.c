// 记录目录流位置并恢复再次读取
#include <tytofu.h>
void seekdir(DIR *dir, long loc);
long telldir(DIR *dir);

int main(int argc, char *argv[]) {
  ARGS_CHECK(argc, 2);
  // 打开一个目录
  DIR *dir;
  dir = opendir(argv[1]);
  ERROR_CHECK(dir, NULL, "opendir");

  // 读取打开的目录中的目录项
  struct dirent *pdirent;
  // while ((pdirent = readdir(dir)) != NULL) {
  //   printf("%ld %ld %d %o %s\n", pdirent->d_ino, pdirent->d_off,
  //          pdirent->d_reclen, pdirent->d_type, pdirent->d_name);
  // }
  // 读取第一次
  pdirent = readdir(dir);
  ERROR_CHECK(pdirent, NULL, "readdir");

  // 记录当前目录流的位置
  long ret = telldir(dir);
  ERROR_CHECK(ret, -1, "telldir");

  // 再次读取一次
  pdirent = readdir(dir);
  ERROR_CHECK(pdirent, NULL, "readdir");

  // 恢复之前读取的位置,使下次readdir从这个位置开始读取
  seekdir(dir, ret);
  pdirent = readdir(dir);
  printf("name is %s\n", pdirent->d_name);
  // 重置目录流
  rewinddir(dir);
  // 重新读取
  pdirent = readdir(dir);
  printf("name is %s\n", pdirent->d_name);

  closedir(dir);
}
