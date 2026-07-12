/*
 * 三目並べ（Tic-Tac-Toe）
 * 仕様書: tictactoe_spec.md に基づく実装
 *
 * 1: 2人対戦モード
 * 2: CPU対戦モード（ミニマックス法による最善手）
 * 3: CPU同士対戦モード（観戦モード）
 *
 * 入力方式:
 *   scanf ではなく read() + termios を用いた1文字入力とし、
 *   Enterキーを押さなくても有効な1文字を入力した瞬間に処理が進むようにしている。
 *   ※ termios は POSIX 端末（Linux / macOS）向けの機能のため、
 *     Windows のコンソールでは動作しない（別途 conio.h の _getch() 等が必要）。
 *
 * コンパイル: gcc -o tictactoe tictactoe.c main.c
 * 実行     : ./tictactoe
 */

#include "tictactoe.h"

int main(void) {
    GameState game;

    printf("=== 三目並べを開始します ===\n");

    do {
        game.game_mode = getGameMode();

        if (game.game_mode == 2) {
            game.human_mark = getHumanMark();
            game.cpu_mark = getOpponentMark(game.human_mark);
        }

        playOneGame(&game);

    } while (askPlayAgain());

    printf("ゲームを終了します。お疲れ様でした。\n");
    return 0;
}
