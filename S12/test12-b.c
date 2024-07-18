#include <stdio.h>
#define N 4 //サイコロを振った回数

int main(void) {
  int data[N] = { 3, 1, 1, 6};  //出た目
  double ave;  //平均
  int total; //合計

  total = 0;
  total += data[0];
  total += data[1];
  total += data[2];
  total += data[3];
  ave = (double) total / N;

  printf("平均:%4.1f\n", ave);
  return 0;
}