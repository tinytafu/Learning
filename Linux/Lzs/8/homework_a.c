// 编写程序A和B,A向B发送文件的名称、大小、内容,程序B创建目录并保存文件
#include <dirent.h>
#include <sys/stat.h>
#include <tytofu.h>

int main(int argc, char **argv) {
  // 程序如何执行:tf 3.pipe
  ARGS_CHECK(argc, 2);
  // 打开管道文件的写端
  int fdw = open(argv[1], O_WRONLY);
  ERROR_CHECK(fdw, -1, "open");
  // 定义发送文件名称、大小、内容的同时以\为分割单位
  /*----------------------------------------------------*/
  // 将当前目录下的file2发送到程序B
  char buf[4096] = "../8/";
  /*找到file2的名称*/
  // 打开当前目录
  DIR *dp = opendir("../8");
  ERROR_CHECK(dp, NULL, "opendir");
  // 读取目录项
  // 定义一个保存读取到的目录项地址的指针变量
  struct dirent *dir = NULL;
  while (strcmp(((dir = readdir(dp))->d_name), "file2"))
    ;
  /*找到file2的名称*/

  // 保存文件大小
  size_t file_size;

  // 确定文件路径
  const char *pathname = strcat(buf, dir->d_name);
  // 元数据
  struct stat file_stat;
  int ret = stat(pathname, &file_stat);
  if (0 == ret) {
    // 判断是否是常规文件
    if (S_ISREG(file_stat.st_mode)) {
      file_size = file_stat.st_size;
    }
  }
  /*----------------------------------------------------*/
  // 打开此文件,将此文件的内容读取并写入到管道文件中
  int fdw_file = open(pathname, O_WRONLY);
  ERROR_CHECK(fdw_file, -1, "open");
  // 定义发送格式:.name:file_name.size:file size.content:file content
  // 将文件名称格式发送到3.pipe
  char format[3][20] = {".name", ".size", ".content"};
  ssize_t wret = write(fdw, strcat(format[0], dir->d_name),
                       strlen(strcat(format[0], dir->d_name)));
  ERROR_CHECK(wret, -1, "write");
  // 将文件大小格式发送到3.pipe
  ssize_t wret1 = write(fdw, strcat(format[1], dir->d_name),
                        strlen(strcat(format[1], dir->d_name)));
  ERROR_CHECK(wret1, -1, "write");
  // 将文件内容格式发送到3.pipe
  write(fdw, format[2], strlen(format[2]));
  // 读取file2的内容
  memset(buf, 0, sizeof(buf));
  while (1) {
    ssize_t rret = read(fdw_file, buf, sizeof(buf));
    if (0 == ret)
      break;
    write(fdw, buf, rret);
  }
}
