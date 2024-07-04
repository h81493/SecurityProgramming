//test10-4.c
#include <stdio.h>
#include <x86intrin.h>

#define N 1000

void pa(int array[][N]) {
  unsigned long long ts0;
  unsigned long long ts1;
  unsigned long long cycle;

  printf("パターンA\n");
  // RDTSC クロックサイクル数で時間を計測する。
  cycle = 0;
  ts0 = __rdtsc(); // ts1とts0の間の処理時間を計測する。
  for(int i=0;i<10;i++) {
    for(int y=0;y<N;y++) {
      for(int x=0;x<N;x++) {
        array[x][y]=x*N+y;
      } 
    }
  }
  ts1 = __rdtsc();
  cycle = (ts1 - ts0);
  printf("A cycle = %10llu\n", cycle);
  printf("&array[0][0] =%p\n",&(array[0][0]));
  printf("&array[1][0] =%p\n",&(array[1][0]));
  printf("&array[2][0] =%p\n",&(array[2][0]));
}
void pb(int array[][N]) {
  unsigned long long ts0;
  unsigned long long ts1;
  unsigned long long cycle;

  printf("パターンB\n");
  // RDTSC クロックサイクル数で時間を計測する。
  cycle = 0;
  ts0 = __rdtsc(); // ts1とts0の間の処理時間を計測する。
  for(int i=0;i<10;i++) {
    for(int x=0;x<N;x++) {
      for(int y=0;y<N;y++) {
        array[x][y]=y*N+x;
      } 
    }
  }
  ts1 = __rdtsc();
  cycle = (ts1 - ts0);
  printf("B cycle = %10llu\n", cycle);
  printf("&array[0][0] =%p\n",&(array[0][0]));
  printf("&array[0][1] =%p\n",&(array[0][1]));
  printf("&array[0][2] =%p\n",&(array[0][2]));
}

int main(void) {
  int array[N][N]={0};

  for(int i=0;i<2;i++) {
    pa(array);
    pb(array);
  }
  return 0;
}