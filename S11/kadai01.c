#include <stdio.h>
#include <string.h>
#include "reverse.h"

// gcc kadai01.c reverse.c
int main(void) {
  char *msg[] = {
    "Was it a cat I saw?",
    "Rats live on no evil star",
    "Never odd or even",
    "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG",
    "The rain in Spain stays mainly in the plain"
  };
  char message[]=
    "1234567890123456789012345678901234567890123";
  char* s;
  strcpy(message,msg[1]);
  printf("%s\n",message);
  s=reverse(message);
  printf("%s\n",message);
  printf("%s\n",s);

  return 0;
}
