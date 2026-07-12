#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/* ゲーム全体の状態をまとめた構造体 */
typedef struct {
    char board[9];        /* 盤面。空きマスは '1'〜'9'、埋まっていれば 'X' か 'O' */
    char current_player;  /* 現在の手番の記号 */
    int  game_mode;       /* 1: 2人対戦, 2: CPU対戦, 3: CPU同士対戦 */
    char human_mark;      /* モード2時の人間側の記号 */
    char cpu_mark;        /* モード2時のCPU側の記号 */
} GameState;

/* ---------- 関数プロトタイプ宣言 ---------- */

/* 1文字入力（rawモード） */
char readRawByte(void);
char readMenuChar(void);
void waitForEnter(void);

/* 状態に依存しない純粋関数 */
char getOpponentMark(char mark);

/* モード・先手後手の選択 */
int  getGameMode(void);
char getHumanMark(void);

/* 盤面操作（GameState を引数に取る） */
void initBoard(GameState *game);
void clearScreen(void);
void printBoard(const GameState *game);
int  isEmptyCell(const GameState *game, int index);
void updateBoard(GameState *game, int index);
char checkWin(const GameState *game);
int  isBoardFull(const GameState *game);
int  isNoWinPossible(const GameState *game);
int  checkDraw(const GameState *game);
void switchPlayer(GameState *game);
int  getMove(const GameState *game);

/* CPU思考ルーチン */
int minimax(GameState *game, char forMark, int depth, int isMaximizing);
int getBestMove(GameState *game, char forMark);

/* 手番・結果表示の制御 */
int  isComputerTurn(const GameState *game);
void announceDraw(const GameState *game);
void announceWinner(const GameState *game, char winner);

/* 1手番分の処理・1ゲーム全体の進行 */
void playOneTurn(GameState *game);
void playOneGame(GameState *game);
int  askPlayAgain(void);
