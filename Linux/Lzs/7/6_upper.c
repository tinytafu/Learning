// 将文件中的小写字符转为大写字符 -- 使用mmap
#include <tytofu.h>

int main(int argc, char **argv) {
  // 程序如何执行:tf file5
  ARGS_CHECK(argc, 2);
  // 打开文件
  int fd = open(argv[1], O_RDWR);
  // 检查文件是否打开失败
  ERROR_CHECK(fd, -1, "open");

  // 指定文件大小
  int ret = ftruncate(fd, 58);
  ERROR_CHECK(ret, -1, "ftruncate");
  // 文件对象与内核在当前进程对应的虚拟地址空间中创建的内存空间建立映射
  char *buf;
  buf = (char *)mmap(NULL, 58, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  ERROR_CHECK(buf, MAP_FAILED, "mmap");

  // 可以对文件对象中的内容进行随机访问
  // 循环检测文件对象中的每个字符,如果处于'a' - 'z'中,将其转换为大写
  for (int i = 0; i < 58; i++) {
    if (buf[i] >= 'a' && buf[i] <= 'z')
      buf[i] -= 32;
  }
  munmap(buf, 58);
  close(fd);
}
