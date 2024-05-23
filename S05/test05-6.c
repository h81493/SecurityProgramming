#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  int u_hand;
  printf("あなたの手　ぐう=0　ちょき=1　ぱあ=2　？　");
  (void)scanf("%d", &u_hand);
  srand((unsigned)time(NULL));
  int c_hand = rand() % 3;

  printf("コンピュータ　");
  switch (c_hand) {
    case 0: printf("ぐう"); break;
    case 1: printf("ちょき"); break;
    case 2: printf("ぱあ"); break;
  }
  printf("、　あなた　");
  switch (u_hand) {
    case 0: printf("ぐう"); break;
    case 1: printf("ちょき"); break;
    case 2: printf("ぱあ"); break;
  }
  printf("\n");
  if ( u_hand == c_hand)
    printf("あいこです。\n");
  else if ((u_hand + 1) % 3 == c_hand)
    printf("あなたの勝ちです！\n");
  else
    printf("あなたの負けです・・・\n");
  return 0;
}
