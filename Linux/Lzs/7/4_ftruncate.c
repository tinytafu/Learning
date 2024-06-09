// 指定文件大小
// 若指定大小小于实际文件大小,则保留前面,清空后面
// 若指定大小大于实际文件大小,则保留文件内容,后面补二进制0 -- 文件空洞
#include <tytofu.h>

int main(int argc, char **argv) {
  // 程序如何执行:tf file2_backup
  ARGS_CHECK(argc, 2);
  // 打开文件
  int fd = open(argv[1], O_RDWR);
  // 检查文件是否打开失败
  ERROR_CHECK(fd, -1, "open");
  // 指定文件大小
  int ret = ftruncate(fd, 78);
  ERROR_CHECK(ret, -1, "ftruncate");
  close(fd);
}
