#include <stdio.h>
int main(void ) {
  int in[20+1];
  //Input
  for ( int j=0;j<20+1;j++) {
    int c;
    c = getchar();
    switch(c) {
      case '0':
        in[j] = 0;
        break;
      case '1':
        in[j] = 1;
        break;
      case ' ':
        continue;
      default:
        in[j] = 0xff;
    }
    if (in[j] == 0xff) break;
  }
/*
  for ( int j=0;j<10;j++) {
    printf("%d", in[j]);
    if(j%3==0) printf(" ");
  }
  printf("\n");
*/
  //State Machine
  int i=0;
  s1:
  if ( in[i] == 0xff) goto end;
  if (in[i++] == 0) {
    printf("0");
    goto s1;
  } else {
    printf("0");
    goto s2;
  }
  s2:
  if ( in[i] == 0xff) goto end;
  if (in[i++] == 0) {
    printf("0");
    goto s1;
  } else {
    printf("1");
    goto s3;
  }
  s3:
  if ( in[i] == 0xff) goto end;
  if (in[i++] == 0) {
    printf("0");
    goto s1;
  } else {
    printf("1");
    goto s3;
  }
  end:
  printf("\n");
  return 0;
}    
