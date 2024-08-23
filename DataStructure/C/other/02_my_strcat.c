// 自定义strcat函数
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *dynamic_strcat(const char *prefix, const char *suffix) {
  // 检测prefix和suffix是否为空
  if (prefix == NULL || suffix == NULL)
    return NULL;
  // 2.计算prefix和suffix中的有效字符个数
  size_t prefix_len = strlen(prefix);
  size_t suffix_len = strlen(suffix);
  // 3.申请堆内存
  char *str = (char *)malloc(sizeof(char) * (prefix_len + suffix_len + 1));
  // 4.判断是否申请失败
  if (NULL == str)
    return NULL;
  // 5.创建临时指针拷贝数据
  char *tmp = str;
  // 5.1拷贝prefix中的字符
  for (int i = 0; i < prefix_len; i++)
    *tmp++ = prefix[i];
  // 5.2拷贝suffix中的字符
  for (int i = 0; i < suffix_len; i++)
    *tmp++ = suffix[i];
  // 5.3将str指向的堆内存中的最后内存单元的值设为'\0'
  *tmp = '\0';
  // 6.返回str
  return str;
}

int main() {
  const char *str1 = "wangshuai ";
  const char *str2 = "love huamengjun";
  char *str = dynamic_strcat(str1, str2);
  printf("%s\n", str);
  free(str);
  str = NULL;
}
