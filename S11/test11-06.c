//test11-6.c
//引数の表示
#include <stdio.h>
#include <string.h>

int main(int argc,char **argv) {
  char **s = argv;
  char s1[20];
  char mes[]="testmes";
  for(int i = 0;i < argc;i++) {
    printf("%02d: %s\n", i, *s++);
  }
  printf("argv %p\n",argv);
  printf("argv[0] %p\n",argv[0]);
  printf("argv[1] %p\n",argv[1]);
  printf("%s\n",mes);
  scanf("%s",s1);
  return 0;
}