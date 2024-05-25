#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <features.h>
int main() {
  extern char** environ;
  pid_t pid = fork();
  if (0 == pid) {//执行子进程
    printf("我是子进程,我的进程id是%d\n",getpid());
    // execl("./mycmd", "mycmd",NULL);
    char* const argv[] = {
      (char*)"nvim",
      (char*)"-v",
      NULL
    };
    char* const envp[] = {
      (char*)"wangshuai=iamtofu",
      NULL
    };
    execve("/home/tinytofu/tofu_executable/nvim", argv, environ);
    // execle("./mycmd", "mycmd",NULL,environ);
    // execv("/usr/bin/ls", argv);
    // execlp("ls", "ls","-l",NULL);
    // execvp("ls", argv);
    //如果程序替换失败,则子进程退出,不然的话要执行和父进程一样的代码了
    exit(-1);
  }
  //必须是父进程
  int status = 0;
  pid_t ret = waitpid(pid, &status, 0);
  if (ret == pid) {
    sleep(2);
    printf("父进程等待成功!退出码为%d\n",WEXITSTATUS(status));
  }

  // printf("我是一个进程的,我的进程id是%d\n",getppid());
  // //执行ls可执行程序,带上参数
  // int ret = execl("/usr/bin/lssss", "ls","-l",NULL);
  //
  // printf("我执行完成了!,ret = %d\n",ret);
  // return 0;
}
