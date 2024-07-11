//test11-3.c
//strcpy
#include <stdio.h>
#include <string.h>

int main(void) {
  char str1[1024] = "C language";
  char str2[]     = "C language";
  char str3[]     = "C ​​​​​​​​​​language"; //0幅スペース
  char str4[]     = "C　language"; //全角スペース
  char str5[]     = "Ｃ　ｌａｎｇｕａｇｅ"; //全角英字

  char buff[512];

  strcpy(buff,str1);
  printf("strcpy str1 len = %ld %ld\n%s\n%s\n",
    strlen(str1),strlen(buff),str1,buff);

  strcpy(buff,str2);
  printf("strcpy str2 len = %ld %ld\n%s\n%s\n",
    strlen(str2),strlen(buff),str2,buff);

  strcpy(buff,str3);
  printf("strcpy str3 len = %ld %ld\n%s\n%s\n",
    strlen(str3),strlen(buff),str3,buff);

  strcpy(buff,str4);
  printf("strcpy str4 len = %ld %ld\n%s\n%s\n",
    strlen(str4),strlen(buff),str4,buff);

  strcpy(buff,str5);
  printf("strcpy str5 len = %ld %ld\n%s\n%s\n",
    strlen(str5),strlen(buff),str5,buff);

  return 0;
}