// 读取stdin的数据 -- 读取设备文件 阻塞
#include <tytofu.h>
int main() {
  // 如何执行程序: tf
  // 定义一块内存空间存储空间
  char buf[1024];
  // 重置内存空间中的数据为'\0'
  memset(buf, 0, sizeof(buf));
  // 读取stdin文件对象中的数据
  ssize_t sret = read(0, buf, sizeof(buf) - 1);
  // 判断是否读取错误
  ERROR_CHECK(sret, -1, "read");
  // 根据读取到的数据长度,将换行符设置'\0'
  buf[sret - 1] = '\0';
  // 输出buf和sret的值
  printf("buf is %s\nsret is %ld\n", buf, sret);
}
