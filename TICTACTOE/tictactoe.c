#include "tictactoe.h"

/* ---------- 1文字入力（rawモード） ---------- */

/*
 * 端末の行バッファリング(ICANON)とエコー(ECHO)を一時的に無効化し、
 * 1バイトだけ読み取ってすぐに終端設定を元に戻す。
 * Enterキーを押さなくても、1文字入力した瞬間に read() が返る。
 * 標準入力がTTYでない場合（パイプ・リダイレクト等）は、通常通り1バイトずつ読み取る。
 */
char readRawByte(void) {
    struct termios oldt, newt;
    int isTTY = isatty(STDIN_FILENO);
    char c;
    ssize_t n;

    /*
     * scanf/getchar 等の stdio 関数を使わず read() を直接呼ぶようにしたため、
     * 「同じ端末につながった出力を、入力待ちの前に自動でフラッシュする」という
     * stdio の暗黙の仕組みが働かなくなっている。
     * そのため、改行を含まないプロンプト文字列（例:「(何かキーを押すと次へ進みます) 」）が
     * 出力バッファに残ったまま画面に表示されず、入力待ちなのに何も表示されていないように
     * 見えてしまう。read() の直前で明示的にフラッシュすることでこれを防ぐ。
     */
    fflush(stdout);

    if (isTTY) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        /*
         * c_cc[VMIN]/c_cc[VTIME] は、カノニカルモードでは VEOF/VEOL として
         * 使われている配列を共有しているため、ICANON を外しただけでは
         * 古い値（多くの環境で VEOF=4 等）がそのまま引き継がれてしまう。
         * それを VMIN として解釈すると「4バイト届くまで read() がブロックする」
         * 挙動になり、1文字入力しても反応しないように見える原因になる。
         * そのため明示的に「1バイト届き次第すぐ返す」設定にする。
         */
        newt.c_cc[VMIN] = 1;
        newt.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    }

    n = read(STDIN_FILENO, &c, 1);

    if (isTTY) {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }

    if (n <= 0) {
        printf("\n入力が終了しました。ゲームを終了します。\n");
        exit(0);
    }

    return c;
}

/*
 * メニュー選択・着手用の1文字入力。
 * 改行文字(\n, \r)は読み飛ばし、実際に入力された文字だけを返す。
 * エコーを無効化しているため、受理した文字は手動で画面に表示する。
 */
char readMenuChar(void) {
    char c;
    while (1) {
        c = readRawByte();
        if (c == '\n' || c == '\r') {
            continue; /* 改行は無視して次の入力を待つ */
        }
        break;
    }
    printf("%c\n", c); /* 手動エコー */
    return c;
}

/* モード3（観戦モード）で、何かキーが押されるまで待つ（Enterでもよい） */
void waitForEnter(void) {
    printf("(何かキーを押すと次へ進みます) ");
    readRawByte();
    printf("\n");
}

/* ---------- 状態に依存しない純粋関数 ---------- */

/* 指定した記号の相手側の記号を返す */
char getOpponentMark(char mark) {
    return (mark == 'X') ? 'O' : 'X';
}

/* ---------- モード・先手後手の選択 ---------- */

/* 対戦モードの選択 */
int getGameMode(void) {
    char c;
    while (1) {
        printf("対戦モードを選んでください。\n");
        printf("1: 2人対戦\n");
        printf("2: コンピュータと対戦\n");
        printf("3: コンピュータ同士の対戦（観戦モード）\n");
        printf("選択(1-3): ");
        c = readMenuChar();

        if (c < '1' || c > '3') {
            printf("1〜3のいずれかを入力してください。\n");
            continue;
        }
        return c - '0';
    }
}

/* CPU対戦モード時、人間の先手・後手を選択 */
char getHumanMark(void) {
    char c;
    while (1) {
        printf("先手(X)・後手(O)どちらで対戦しますか？\n");
        printf("1: 先手 (X)\n");
        printf("2: 後手 (O)\n");
        printf("選択(1-2): ");
        c = readMenuChar();

        if (c != '1' && c != '2') {
            printf("1か2を入力してください。\n");
            continue;
        }
        return (c == '1') ? 'X' : 'O';
    }
}

/* ---------- 盤面操作（GameState を引数に取る） ---------- */

/* 盤面の初期化：各マスに1〜9の番号を設定し、先手をXにする */
void initBoard(GameState *game) {
    int i;
    for (i = 0; i < 9; i++) {
        game->board[i] = (char)('1' + i);
    }
    game->current_player = 'X'; /* 先手は常にX */
}

/* 画面をクリアしてカーソルを左上に戻す（ANSIエスケープシーケンス） */
void clearScreen(void) {
    printf("\033[2J\033[H");
    fflush(stdout);
}

/* 盤面の表示 */
void printBoard(const GameState *game) {
    const char *b = game->board;
    clearScreen();
    printf("\n");
    printf(" %c | %c | %c\n", b[0], b[1], b[2]);
    printf("-----------\n");
    printf(" %c | %c | %c\n", b[3], b[4], b[5]);
    printf("-----------\n");
    printf(" %c | %c | %c\n", b[6], b[7], b[8]);
    printf("\n");
}

/* 指定マスが空きかどうか（番号のままなら空き） */
int isEmptyCell(const GameState *game, int index) {
    return game->board[index] == (char)('1' + index);
}

/* 盤面の更新：現在の手番の記号を指定マスに置く */
void updateBoard(GameState *game, int index) {
    game->board[index] = game->current_player;
}

/* 勝敗判定：勝者の記号('X' or 'O')を返す。勝者なしは0を返す */
char checkWin(const GameState *game) {
    static const int lines[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, /* 横 */
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, /* 縦 */
        {0, 4, 8}, {2, 4, 6}            /* 斜め */
    };
    const char *b = game->board;
    int i;

    for (i = 0; i < 8; i++) {
        int a = lines[i][0];
        int c = lines[i][1];
        int d = lines[i][2];

        if (b[a] == b[c] && b[c] == b[d] && (b[a] == 'X' || b[a] == 'O')) {
            return b[a];
        }
    }
    return 0;
}

/* 全マスが埋まっているかどうか */
int isBoardFull(const GameState *game) {
    int i;
    for (i = 0; i < 9; i++) {
        if (isEmptyCell(game, i)) {
            return 0;
        }
    }
    return 1;
}

/*
 * 8つの勝ち筋(縦・横・斜め)すべてに X と O の両方が既に含まれているか＝
 * 空きマスが残っていても、これ以上どちらのプレイヤーも
 * 3つ揃えられる見込みがない状態かどうかを判定する。
 */
int isNoWinPossible(const GameState *game) {
    static const int lines[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, /* 横 */
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, /* 縦 */
        {0, 4, 8}, {2, 4, 6}            /* 斜め */
    };
    const char *b = game->board;
    int i;

    for (i = 0; i < 8; i++) {
        int a = lines[i][0];
        int c = lines[i][1];
        int d = lines[i][2];
        int hasX = (b[a] == 'X' || b[c] == 'X' || b[d] == 'X');
        int hasO = (b[a] == 'O' || b[c] == 'O' || b[d] == 'O');

        if (!(hasX && hasO)) {
            return 0; /* この勝ち筋はまだどちらかが完成させられる可能性が残る */
        }
    }
    return 1; /* すべての勝ち筋がふさがれている＝これ以上勝者は出ない */
}

/*
 * 引き分け判定。
 * 全マスが埋まった場合に加え、空きマスが残っていても
 * これ以上誰も勝てないことが確定していれば、その時点で引き分けとする。
 */
int checkDraw(const GameState *game) {
    if (isBoardFull(game)) {
        return 1;
    }
    return isNoWinPossible(game);
}

/* 手番の交代 */
void switchPlayer(GameState *game) {
    game->current_player = getOpponentMark(game->current_player);
}

/* 人間プレイヤーからの入力受付とバリデーション。0-8のインデックスを返す */
int getMove(const GameState *game) {
    char c;
    int index;

    while (1) {
        printf("プレイヤー %c の番です。マス番号(1-9)を入力してください: ", game->current_player);
        c = readMenuChar();

        if (c < '1' || c > '9') {
            printf("1〜9の範囲で入力してください。\n");
            continue;
        }

        index = c - '1';
        if (!isEmptyCell(game, index)) {
            printf("そのマスは既に埋まっています。別のマスを選んでください。\n");
            continue;
        }

        return index;
    }
}

/* ---------- CPU思考ルーチン ---------- */

/*
 * ミニマックス法による盤面評価。
 * forMark: 「誰にとっての最善手か」を表す記号。
 * isMaximizing=1 のときは forMark 側の手番（評価値を最大化したい）、
 * isMaximizing=0 のときは相手側の手番（評価値を最小化したい）とみなして再帰評価する。
 * 評価値は「forMarkの勝ち: 10-depth」「相手の勝ち: depth-10」「引き分け: 0」。
 * game->board を一時的に書き換えて評価し、終わったら元に戻す（バックトラック）。
 */
int minimax(GameState *game, char forMark, int depth, int isMaximizing) {
    char opponent = getOpponentMark(forMark);
    char winner = checkWin(game);
    if (winner == forMark)  return 10 - depth;
    if (winner == opponent) return depth - 10;
    if (checkDraw(game))    return 0;

    if (isMaximizing) {
        int bestScore = -1000;
        int i;
        for (i = 0; i < 9; i++) {
            if (isEmptyCell(game, i)) {
                char backup = game->board[i];
                game->board[i] = forMark;
                int score = minimax(game, forMark, depth + 1, 0);
                game->board[i] = backup;
                if (score > bestScore) bestScore = score;
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        int i;
        for (i = 0; i < 9; i++) {
            if (isEmptyCell(game, i)) {
                char backup = game->board[i];
                game->board[i] = opponent;
                int score = minimax(game, forMark, depth + 1, 1);
                game->board[i] = backup;
                if (score < bestScore) bestScore = score;
            }
        }
        return bestScore;
    }
}

/*
 * ミニマックス法により、指定した記号(forMark)にとっての最善手（0-8のインデックス）を決定する。
 * モード2（CPU対戦）・モード3（CPU同士対戦）の両方で共用する。
 */
int getBestMove(GameState *game, char forMark) {
    int bestScore = -1000;
    int bestMove = -1;
    int i;

    for (i = 0; i < 9; i++) {
        if (isEmptyCell(game, i)) {
            char backup = game->board[i];
            game->board[i] = forMark;
            int score = minimax(game, forMark, 0, 0); /* 次は相手の手番なので最小化 */
            game->board[i] = backup;
            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }
    return bestMove;
}

/* 現在の手番がCPUかどうかを、ゲームモードに応じて判定する */
int isComputerTurn(const GameState *game) {
    switch (game->game_mode) {
        case 1: return 0;                                        /* 2人対戦: 常に人間 */
        case 2: return (game->current_player == game->cpu_mark);  /* CPU対戦: CPU側の手番のみ */
        case 3: return 1;                                         /* CPU同士: 常にCPU */
        default: return 0;
    }
}

/* 引き分けメッセージを表示する（全マス消化前に確定した場合は理由も添える） */
void announceDraw(const GameState *game) {
    if (isBoardFull(game)) {
        printf("引き分けです。\n");
    } else {
        printf("空きマスは残っていますが、これ以上誰も勝てないため引き分けです。\n");
    }
}

/* 勝者の記号からモードに応じた表示用メッセージを出す */
void announceWinner(const GameState *game, char winner) {
    if (game->game_mode == 1) {
        printf("プレイヤー %c の勝ちです！\n", winner);
    } else if (game->game_mode == 2) {
        if (winner == game->human_mark) {
            printf("あなた（%c）の勝ちです！\n", winner);
        } else {
            printf("コンピュータ（%c）の勝ちです！\n", winner);
        }
    } else {
        printf("CPU（%c）の勝ちです！\n", winner);
    }
}

/* ---------- 1手番分の処理 ---------- */

/* 現在の手番を1回分処理する（着手 → 表示 → 観戦モードの一時停止） */
void playOneTurn(GameState *game) {
    int move;
    char mover = game->current_player;
    int cpuTurn = isComputerTurn(game);

    /*
     * printBoard() は表示直前に画面をクリアするため、
     * 「CPU（O）が思考中です...」のようなメッセージを着手より前に出しても
     * この後の printBoard() で即座に消えてしまう。
     * そのため、CPUの着手メッセージは printBoard() の後（消されない位置）に表示する。
     */
    if (cpuTurn) {
        move = getBestMove(game, mover);
    } else {
        move = getMove(game);
    }

    updateBoard(game, move);
    printBoard(game);

    if (cpuTurn) {
        printf("CPU（%c）はマス %d を選びました。\n", mover, move + 1);
    }

    if (game->game_mode == 3) {
        waitForEnter();
    }
}

/* 1ゲームを最初から最後まで（決着がつくまで）実行する */
void playOneGame(GameState *game) {
    char winner;

    initBoard(game);
    printBoard(game);

    while (1) {
        playOneTurn(game);

        winner = checkWin(game);
        if (winner != 0) {
            announceWinner(game, winner);
            return;
        }

        if (checkDraw(game)) {
            announceDraw(game);
            return;
        }

        switchPlayer(game);
    }
}

/* 「もう一度遊びますか？」の確認。続ける場合は1、終了する場合は0を返す */
int askPlayAgain(void) {
    char c;
    printf("もう一度遊びますか？ (y/n): ");
    c = readMenuChar();
    return (c == 'y' || c == 'Y');
}
