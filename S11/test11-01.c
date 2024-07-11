//test11-1.c
//strlen
#include <stdio.h>
#include <string.h>

int main(void) {
  char str1[1024] = "C language";
  char str2[]     = "C language";
  char str3[]     = "C ​​​​​​​​​​language"; //0幅スペース
  char str4[]     = "C言語";       //UTF-8漢字
  char str5[]     = "C　language"; //全角スペース
  char str6[]     = "Ｃ　ｌａｎｇｕａｇｅ"; //全角英字
  char str7[]     = "𩸽";
  char str8[]     = "邉󠄂";
  char str9[]     = "☔";
  char stra[]     = "👨‍👩‍👧‍👦";

  

  printf("str1 len = %2ld %s\n", strlen(str1),str1);
  printf("str2 len = %2ld %s\n", strlen(str2),str2);
  printf("str3 len = %2ld %s\n", strlen(str3),str3);
  printf("str4 len = %2ld %s\n", strlen(str4),str4);
  printf("str5 len = %2ld %s\n", strlen(str5),str5);
  printf("str6 len = %2ld %s\n", strlen(str6),str6);
  printf("str7 len = %2ld %s\n", strlen(str7),str7);
  printf("str8 len = %2ld %s\n", strlen(str8),str8);
  printf("str9 len = %2ld %s\n", strlen(str9),str9);
  printf("stra len = %2ld %s\n", strlen(stra),stra);

  return 0;
}