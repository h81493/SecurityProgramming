//test11-4.c
//strcat
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
  strcat(buff," ");
  strcat(buff,str2);
  printf("strcat len=%ld\n%s\n",strlen(buff),buff);

  buff[0]=0x00;
  strcpy(buff,str3);
  strcat(buff," ");
  strcat(buff,str4);
  strcat(buff," ");
  strcat(buff,str5);
  printf("strcat len=%ld\n%s\n",strlen(buff),buff);


  return 0;
}