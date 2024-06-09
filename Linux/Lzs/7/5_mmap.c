// 建立磁盘文件(被打开的磁盘文件)与用户态内存区域之间的映射
#include <tytofu.h>

int main(int argc, char **argv) {
  // 程序如何执行:tf file4
  ARGS_CHECK(argc, 2);
  // 打开文件
  int fd = open(argv[1], O_RDWR);
  // 检查文件是否打开失败
  ERROR_CHECK(fd, -1, "open");
  // 指定文件大小
  int ret = ftruncate(fd, 10);
  ERROR_CHECK(ret, -1, "ftruncate");
  // 建立文件对象与用户态内存的映射
  char *buf;
  buf = (char *)mmap(NULL, 10, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  // 使用用户态内存随机访问 -- 读取文件内容
  for (int i = 0; i < 10; i++)
    printf("%c\n", buf[i]);
  // 随机修改第10个位置的字符为p
  buf[9] = 'p';
  // 释放内核在当前进程对应的虚拟地址空间创建的堆内存
  munmap(buf, 10);
  // 关闭文件对象
  close(fd);
}
