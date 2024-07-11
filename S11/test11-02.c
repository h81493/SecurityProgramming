//test11-2.c
//strcmp
#include <stdio.h>
#include <string.h>

int main(void) {
  char str1[1024] = "C language";
  char str2[]     = "C language";
  char str3[]     = "C ​​​​​​​​​​language"; //0幅スペース
  char str4[]     = "C　language"; //全角スペース
  char str5[]     = "Ｃ　ｌａｎｇｕａｇｅ"; //全角英字
  char stra[]     = "01234567";
  char strb[]     = "01234568";

  printf("strcmp str1 str1 =%d\n", strcmp(str1,str1));//0
  printf("strcmp str1 str2 =%d\n", strcmp(str1,str2));//0
  printf("strcmp str1 str3 =%d\n", strcmp(str1,str3));//-118
  printf("strcmp str1 str4 =%d\n", strcmp(str1,str4));//-195
  printf("strcmp str1 str5 =%d\n", strcmp(str1,str5));//-172
  printf("strcmp stra strb =%d\n", strcmp(stra,strb));//-1
  printf("strcmp strb stra =%d\n", strcmp(strb,stra));//+1



  return 0;
}