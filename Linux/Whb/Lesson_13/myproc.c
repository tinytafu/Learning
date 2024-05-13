#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*创建一个未初始化的全局变量*/
int un_global_value;
/*创建一个初始化的全局变量*/
int global_value = 100;
int main (int argc,char** argv,char** env) {
  
  /*感知进程地址空间*/
  pid_t pid = fork();
  if (pid == 0 ) {
    //child
    int flag = 0;
    while(1) {
      printf("我是子进程:%d,ppid = %d,global_value: %d,&global_value = %p\n\n",getpid(),getppid(),global_value,&global_value);
      sleep(1);
      if (5 == flag) {
        global_value = 200;
        printf("我是子进程,我已经修改了global_value的值为200,父进程注意!\n");
      }
      flag++;
    }
  }else {
    //parent
    while(1) {
      printf("我是父进程:%d,ppid = %d,global_value: %d,&global_value = %p\n\n",getpid(),getppid(),global_value,&global_value);
      sleep(2);
    }
  }
  
  /*验证进程地址空间*/
  // printf("main address in .text                       : %p\n",main);
  // printf("global_value address in .data               : %p\n",&global_value);
  // printf("un_global_value address in .bss             : %p\n",&un_global_value);
  // char* heap_memory_one = (char*) malloc(sizeof(char));
  // char* heap_memory_two = (char*) malloc(sizeof(char));
  // char* heap_memory_three = (char*) malloc(sizeof(char));
  // char* heap_memory_four = (char*) malloc(sizeof(char));
  // static int static_variable = 200;
  // static int un_static_variable;
  // printf("heap_memory_one address in heap             : %p\n",heap_memory_one);
  // printf("heap_memory_two address in heap             : %p\n",heap_memory_two);
  // printf("heap_memory_three address in heap           : %p\n",heap_memory_three);
  // printf("heap_memory_four address in heap            : %p\n",heap_memory_four);
  // printf("&heap_memory_one address in stack           : %p\n",&heap_memory_one);
  // printf("&heap_memory_two address in stack           : %p\n",&heap_memory_two);
  // printf("&heap_memory_three address in stack         : %p\n",&heap_memory_three);
  // printf("&heap_memory_four address in stack          : %p\n",&heap_memory_four);
  // printf("static_variable address in stack            : %p\n",&static_variable);
  // printf("un_static_variable address in stack         : %p\n",&un_static_variable);
  // free(heap_memory_one);
  // free(heap_memory_two);
  // free(heap_memory_three);
  // free(heap_memory_four);
  //
  // printf("argv[0] address in command-line argument    : %p\n",argv[0]);
  //
  // printf("env[0] address in env                       : %p\n",env[0]);
  // while(1) {
  //   printf("hello world! -> pid = %d,ppid = %d,myenv = %s\n",getpid(),getppid(),getenv("wangshuai"));
  //   sleep(1);
  // }
}
