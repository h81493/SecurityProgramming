// 人間同士の対戦で、各盤面の最善手を表示する。

#include "tictactoe.h"

int test1(GameState *game) {
    int move,chkdraw;
    char winner;
    char mover;

    initBoard(game);

    while(1) {
        printBoard(game);  // 画面クリア＋盤面の表示
        mover =                          // 構造体gameのメンバcurrent_playerをmoverに代入
        move = getBestMove(game, mover); // ミニマックス法により指定記号にとっての最善手を算出
        printf("best move = %d mover = %c\n", move+1, mover);

        winner  = checkWin(game);  // 勝敗判定（勝者の記号 or 0 を返す）
        chkdraw = checkDraw(game); // 引き分け判定
        printf("Win = %c Draw = %d\n",winner,chkdraw);
        if(      )       ; // 引き分けまたは勝ちが決まったらループを抜ける

        move = getMove(game); // 人間プレイヤーからの入力受付とバリデーション
        updateBoard(game, move); // 盤面の更新
        switchPlayer(game); // 手番の交代
    }

}
int main(void) {
    GameState game;

    printf("=== Test1 ===\n");
    test1(&game);
    return 0;
}
