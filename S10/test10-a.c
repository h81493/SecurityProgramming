//test10-7
//整数を10万個一気にmallocする。
#include <stdio.h>
#include <malloc.h>
#include <x86intrin.h>

char c;

int *funca(int i) {
  static int *ptr;
  if(i==0) {
    ptr = (int *)malloc(100000*sizeof(int));
    printf("1:malloc後停止");
    c=getchar();//malloc後停止
  }
  return(ptr);
}

int main(void) {
  int *ptr;
  int *ptmp[100000];
  unsigned long long ts0;
  unsigned long long ts1;
  unsigned long long cycle;

  printf("【学籍番号】\n");
  // RDTSC クロックサイクル数で時間を計測する。
  cycle = 0;
  ts0 = __rdtsc(); // ts1とts0の間の処理時間を計測する。

  for(int i=0;i<100000;i++) {
    ptr = funca(i);
    ptr[i]=i;

    ptmp[i] = (int *)malloc(1*sizeof(int));
    ptmp[i][0]=i+1;
  }
  printf("2:ptmp malloc後停止");
  c=getchar();//ptmp malloc後停止

  ts1 = __rdtsc();
  cycle = (ts1 - ts0);
  printf("  cycle = %14llu\n", cycle);

  int sum1=0;
  for(int i=0;i<100000;i++) {
    sum1=sum1+ptr[i];
  }
  if(sum1 != 704982704) {
    printf("NG ptr  sum1 = %d\n", sum1);
  }
  int sum2=0;
  for(int i=0;i<100000;i++) {
    sum2=sum2+ptmp[i][0];
  }
  if(sum2 != 705082704) {
    printf("NG ptmp sum2 = %d\n", sum2);
  }
  free(ptr);
  printf("3:ptr free後停止");
  c=getchar();//ptr free後停止
  for(int i=0;i<100000;i++) {
    free(ptmp[i]);
  }
  printf("4:ptmp free後停止");
  c=getchar();//ptmp free後停止
  return 0;
}