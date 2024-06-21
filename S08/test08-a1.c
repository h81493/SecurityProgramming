/*
*じゃんけん３
*５回勝負に変更
*
*じゃんけん２
*リターンを待たないでキー入力
*非カノニカル　ブロッキングI/O　エコーオフ
*/
//#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef S_SPLINT_S
// Splint用の簡略化されたtermios.h
struct termios {
    // 必要最低限のメンバだけを定義
  };
#else
#include <termios.h>
#endif

static void mode(int on) {//カノニカル モード
#ifdef S_SPLINT_S
  printf("%d\n",on);
#else
  static struct termios term1, term0;
  if( on) { //non canonical mode
    tcgetattr(0, &term1); //現在の画面環境の取得
    term0 = term1; //現在の画面環境の保存
    term1.c_lflag &= ~(ICANON | ECHO);
    //現在の画面環境をエコーオフおよび非カノニカル・モードに設定
    term1.c_cc[VMIN] = 1; //そのためのパラメータ
    term1.c_cc[VTIME] = 0; //そのためのパラメータ
    tcsetattr(0, TCSANOW, &term1); //現在の画面環境を更新
  } else {
    tcsetattr(0, TCSANOW, &term0);
    //保存しておいた環境で現在の画面環境を更新（元に戻す）
    //
  }
#endif
}
#define ON  1
#define OFF 0
int main(void) {
  int u_hand = 0;
  int u_win = 0; // 人間の勝った回数
  int c_win = 0; // コンピュータの勝った回数
  int cnt = 0;
  mode(ON);
  while(cnt++ < 5) {
    printf("%d回戦\n",cnt);
    start:
    printf("あなたの手　ぐう=0　ちょき=1　ぱあ=2　？　");
    while(true) {
      u_hand = getchar();
      if(u_hand>=(int)'0' && u_hand<=(int)'2') {
        u_hand = u_hand & 0x0f;
        break;
      }
    }
    printf("\n");
    srand((unsigned)time(NULL));
    int c_hand = 0;
    c_hand = rand() % 3;
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
    if ( u_hand == c_hand) {
      printf("あいこです。\n");
      goto start;
    } else if ((u_hand + 1) % 3 == c_hand) {
      printf("あなたの勝ちです！\n");
      u_win++;
    } else {
      printf("あなたの負けです・・・\n");
      c_win++;
    }
  }
  printf("５戦%d勝%d敗  ",u_win,c_win);
  if(u_win > c_win) {
    printf("あなたの勝ちです！\n");
  } else {
    printf("あなたの負けです！\n");
  }
  mode(OFF);
  return 0;
}
