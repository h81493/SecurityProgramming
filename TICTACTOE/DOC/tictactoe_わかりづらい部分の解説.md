# `tictactoe.c` 分かりづらい部分の解説

`tictactoe.c` の中で、特に初見では意図が読み取りにくい箇所を抜き出し、
使われている変数も含めて解説する。

> GitHubリンクは [h81493/SecurityProgramming/TICTACTOE/tictactoe.c](https://github.com/h81493/SecurityProgramming/blob/main/TICTACTOE/tictactoe.c) を基準にしている
> （行番号は本セッション時点のもの。ズレていたら実際の行を確認してください）。

---

## 1. `GameState` 構造体（[L24-L31](https://github.com/h81493/SecurityProgramming/blob/main/TICTACTOE/tictactoe.c#L24-L31)）

```c
typedef struct {
    char board[9];        /* 盤面。空きマスは '1'〜'9'、埋まっていれば 'X' か 'O' */
    char current_player;  /* 現在の手番の記号 */
    int  game_mode;       /* 1: 2人対戦, 2: CPU対戦, 3: CPU同士対戦 */
    char human_mark;      /* モード2時の人間側の記号 */
    char cpu_mark;        /* モード2時のCPU側の記号 */
} GameState;
```

全関数がこの1つの構造体を介して状態をやり取りする、いわば「ゲームの全部入り」の変数。

| フィールド | 型 | 意味 |
|---|---|---|
| `board[9]` | `char[9]` | 3×3の盤面を長さ9の1次元配列で表現。インデックス0〜8が、画面上の左上から右下へ`1〜9`のマス番号に対応する（`board[0]`=左上、`board[8]`=右下）。値は空きマスなら`'1'`〜`'9'`（マス番号の文字）、埋まっていれば`'X'`か`'O'`。 |
| `current_player` | `char` | 「今どちらの手番か」を表す。`'X'`か`'O'`のどちらか。 |
| `game_mode` | `int` | 対戦モード。`1`=2人対戦、`2`=CPU対戦、`3`=CPU同士対戦。 |
| `human_mark` | `char` | モード2（CPU対戦）の時だけ使う。人間側が`'X'`か`'O'`か。モード1・3では未設定（値は不定）。 |
| `cpu_mark` | `char` | モード2の時だけ使う。`human_mark`の逆の記号。 |

**分かりづらい点：** `human_mark`/`cpu_mark`はモード1・3では一度も代入されないため「未初期化のまま」になる。
モード1・3のコードパスではこの2つのフィールドを一切参照しないよう設計されている
（`isComputerTurn()`や`announceWinner()`の`switch`/`if`文を参照）ので実害はないが、
デバッガでこの構造体を覗くと一見「初期化忘れ」に見えるので注意。

---

## 2. `readRawByte()` — 一番分かりづらい関数（[L41-L86](https://github.com/h81493/SecurityProgramming/blob/main/TICTACTOE/tictactoe.c#L41-L86)）

```c
char readRawByte(void) {
    struct termios oldt, newt;
    int isTTY = isatty(STDIN_FILENO);
    char c;
    ssize_t n;

    fflush(stdout);

    if (isTTY) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
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
```

### 変数の意味

| 変数 | 型 | 意味 |
|---|---|---|
| `oldt` | `struct termios` | 呼び出し時点の「元の」端末設定を退避しておくための変数。関数の最後に必ずこれへ戻す。 |
| `newt` | `struct termios` | `oldt`をコピーした上で、rawモード用に一部フラグだけ書き換えた「新しい」設定。 |
| `isTTY` | `int` | 標準入力が対話的な端末（TTY）かどうか。パイプやリダイレクトの場合は`0`。 |
| `c` | `char` | 読み取った1バイトを受け取る変数。戻り値そのもの。 |
| `n` | `ssize_t` | `read()`の戻り値。実際に読み取れたバイト数（正常なら`1`、EOFなら`0`、エラーなら負数）。 |

### 分かりづらいポイント

1. **なぜ`oldt`と`newt`の2つが要るのか**
   `tcsetattr()`で設定を変更する前に、必ず元の設定（`oldt`）を保存しておき、
   1文字読み終えたら`tcsetattr(..., &oldt)`で元に戻している。これを忘れると、
   プログラム終了後もターミナルがrawモードのままになり、通常のシェル操作
   （バックスペースが効かない等）が壊れてしまう。

2. **`c_lflag &= ~(ICANON | ECHO)` の意味**
   `c_lflag`はビットフラグの集合。`ICANON`（行バッファリング＝Enterを押すまで
   入力が確定しない）と`ECHO`（入力した文字を勝手に画面表示する）を、
   ビット演算の`&= ~(...)`で「オフにする」。`~`はビット反転、`&=`は元の値との
   AND代入なので、「指定した2つのビットだけを0にし、他のビットはそのまま残す」
   という定型的な書き方。

3. **`c_cc[VMIN] = 1; c_cc[VTIME] = 0;` が必須な理由**
   `c_cc`は「制御文字」を格納する配列だが、カノニカルモード（`ICANON`あり）の
   ときと非カノニカルモード（rawモード）のときとで、**同じ配列の同じ添字が
   別の意味に使われる**、というPOSIX termiosの落とし穴がある。
   カノニカルモードでは`c_cc[VEOF]`（多くの環境で値4=Ctrl-D）として
   使われている領域が、rawモードでは`c_cc[VMIN]`として再解釈される。
   `ICANON`フラグを外すだけでこの値を明示的に設定し直さないと、
   「4バイト届くまで`read()`がブロックする」という不可解な挙動になる
   （実際にこのバグで動作しないという報告があり、`VMIN=1, VTIME=0`を
   明示的に指定することで解決した）。

4. **`fflush(stdout)`をなぜ`read()`の直前でやるのか**
   `scanf`/`getchar`など標準の`stdio`関数を使っていれば、「同じ端末につながった
   出力を、入力待ちの前に自動でフラッシュする」という仕組みがCライブラリ側に
   備わっている。しかしこの関数は`read()`システムコールを直接呼んでその仕組みを
   バイパスしているため、自分で明示的に`fflush`しないと、改行を含まない
   プロンプト文字列（例:「選択(1-3): 」）が画面に表示されないまま入力待ちに
   なってしまう（実際にこの問題が起きて修正した経緯がある）。

5. **`isTTY`による分岐がある理由**
   このプログラムを`./tictactoe < input.txt`のようにファイルやパイプから
   実行してテストする場合、標準入力は「端末」ではないため`termios`の設定変更は
   意味を持たない（`tcgetattr`はエラーになる）。`isatty()`でTTYかどうかを判定し、
   TTYでなければ`termios`の操作を丸ごとスキップして、単に`read()`で1バイトずつ
   読むだけにフォールバックしている。

---

## 3. 文字と数値の変換トリック

このプログラムのあちこちに、「文字コードの足し算・引き算でマス番号を扱う」
というC言語特有のイディオムが登場する。

```c
game->board[i] = (char)('1' + i);          // initBoard: i=0なら'1', i=8なら'9'
return game->board[index] == (char)('1' + index); // isEmptyCell
return c - '0';                            // getGameMode: 文字'1'〜'3' → 整数1〜3
index = c - '1';                           // getMove: 文字'1'〜'9' → 配列インデックス0〜8
```

C言語では文字（`char`）は内部的に単なる整数（文字コード）として扱われるため、
`'1' + i`は「文字'1'の文字コード + i」の計算になり、結果として`i=0`のとき`'1'`、
`i=1`のとき`'2'`…という具合に、**マス番号の文字**を生成できる。
同様に`c - '0'`や`c - '1'`は「入力された文字から、対応する整数値・配列
インデックスを逆算する」処理。ASCIIコードでは`'0'`〜`'9'`が連続した値を持つ
ことを前提にした、C言語でよく使われる書き方である。

---

## 4. `minimax()` と `getBestMove()` の「仮に置いて→評価して→元に戻す」パターン
（[minimax: L311-L345](https://github.com/h81493/SecurityProgramming/blob/main/TICTACTOE/tictactoe.c#L311-L345) /
[getBestMove: L351-L369](https://github.com/h81493/SecurityProgramming/blob/main/TICTACTOE/tictactoe.c#L351-L369)）

（`getBestMove`の詳細な解説は別ファイル `getBestMove_解説.md` を参照。ここでは
特に分かりづらい変数・パターンだけを補足する。）

```c
char backup = game->board[i];
game->board[i] = forMark;
int score = minimax(game, forMark, depth + 1, 0);
game->board[i] = backup;
```

| 変数 | 型 | 意味 |
|---|---|---|
| `backup` | `char` | 仮に上書きする前の、そのマスの元の値（多くの場合、空きマスの番号文字）を退避しておく変数。 |
| `forMark` | `char` | 「誰にとっての最善手を探しているか」を表す記号。再帰全体を通して変わらない。 |
| `opponent` | `char` | `forMark`の逆の記号。`getOpponentMark(forMark)`で求める。 |
| `depth` | `int` | 再帰の深さ＝これから何手先を読んでいるか。勝敗の評価値を「何手で決着したか」で調整するために使う。 |
| `isMaximizing` | `int`（真偽値として使用） | 今読んでいる手番が`forMark`側なら`1`（真）、相手側なら`0`（偽）。 |
| `bestScore` | `int` | その時点で見つかっている最も良い評価値。`isMaximizing`が真なら大きいほど良い、偽なら小さいほど良いので、初期値をそれぞれ`-1000`（十分小さい値）・`1000`（十分大きい値）にしておき、必ず1回目の比較で更新されるようにしている。 |
| `score` | `int` | 1つの候補手を仮に置いた結果、再帰的に評価して返ってきた評価値。 |
| `winner` | `char` | `checkWin()`の戻り値。勝者の記号、または勝者なしを表す`0`。 |

**分かりづらい点：** `game->board[i]`を実際に書き換えてから再帰呼び出しし、
戻ってきたら**必ず**`backup`で元に戻している。盤面のコピーを作らずに
1つの配列だけで全パターンを試せる代わりに、「戻し忘れ」があると
即座にバグる（他の候補手を試す時点で盤面が壊れている）ため、
`game->board[i] = forMark;` と `game->board[i] = backup;` は必ずセットで
読む必要がある。

---

## 5. `isNoWinPossible()` の判定ロジック（[L237-L258](https://github.com/h81493/SecurityProgramming/blob/main/TICTACTOE/tictactoe.c#L237-L258)）

```c
int hasX = (b[a] == 'X' || b[c] == 'X' || b[d] == 'X');
int hasO = (b[a] == 'O' || b[c] == 'O' || b[d] == 'O');

if (!(hasX && hasO)) {
    return 0;
}
```

| 変数 | 型 | 意味 |
|---|---|---|
| `a`, `c`, `d` | `int` | 1つの勝ち筋（縦・横・斜めのいずれか）を構成する3マスの、`board`配列上のインデックス。 |
| `hasX` | `int`（真偽値） | その勝ち筋の3マスの中に、`'X'`が1つでもあれば真。 |
| `hasO` | `int`（真偽値） | 同様に`'O'`が1つでもあれば真。 |

**分かりづらい点：** 一見「勝てるかどうか」を判定していそうだが、実際にやっているのは
逆で「**もう勝てないこと**」の判定。ある勝ち筋に`X`と`O`が両方とも
（1つずつでも）含まれていれば、残りが何であってもその3マスを同じ記号で
埋めることは不可能＝その勝ち筋は「死んでいる（詰んでいる）」と判定できる。
これを8つの勝ち筋**全部**についてチェックし、1つでも「まだ生きている
（`X`か`O`のどちらか一方しか入っていない、または空）」勝ち筋があれば
`return 0`（まだ勝負の可能性が残っている）で即座に打ち切る。全部が
「死んでいた」場合だけ、最後まで到達して`return 1`（もう誰も勝てない）となる。

---

## 6. `playOneTurn()` 内のメッセージ表示順序（[L408-L435](https://github.com/h81493/SecurityProgramming/blob/main/TICTACTOE/tictactoe.c#L408-L435)）

```c
char mover = game->current_player;
int cpuTurn = isComputerTurn(game);

if (cpuTurn) {
    move = getBestMove(game, mover);
} else {
    move = getMove(game);
}

updateBoard(game, move);
printBoard(game);            // ← ここで画面クリアが走る

if (cpuTurn) {
    printf("CPU（%c）はマス %d を選びました。\n", mover, move + 1); // 表示の後で出す
}
```

| 変数 | 型 | 意味 |
|---|---|---|
| `mover` | `char` | この手番の**開始時点**での`current_player`を保存しておく変数。 |
| `cpuTurn` | `int`（真偽値） | この手番がCPUによるものかどうか。 |
| `move` | `int` | 決定された着手位置（`board`配列のインデックス、0〜8）。 |

**分かりづらい点：**

- `mover`をわざわざローカル変数に保存しているのは、`game->current_player`が
  この関数の中では変わらないとはいえ、後から読んだときに「今の手番は誰か」を
  明示するため（`printf`で`mover`を使うことで、`game->current_player`を
  直接参照するより意図が読み取りやすくなる）。
- `printBoard(game)`は内部で毎回`clearScreen()`を呼ぶ（画面をクリアしてから
  盤面を描画する）ため、**もし**CPUの着手メッセージを`printBoard()`より
  **前**に表示していたら、直後の画面クリアで一瞬で消えてしまう。
  そのため、着手メッセージは`printBoard()`の**後**（次にクリアされるまでの間）
  に表示するよう、意図的に順序が入れ替えられている。

---

## 7. `isComputerTurn()` のモード別分岐（[L372-L379](https://github.com/h81493/SecurityProgramming/blob/main/TICTACTOE/tictactoe.c#L372-L379)）

```c
switch (game->game_mode) {
    case 1: return 0;
    case 2: return (game->current_player == game->cpu_mark);
    case 3: return 1;
    default: return 0;
}
```

モードごとに「CPUの手番かどうか」の判定基準が異なる：
- モード1（2人対戦）：常に人間 → 常に`0`（偽）。
- モード2（CPU対戦）：`current_player`が`cpu_mark`と一致する時だけCPUの番。
- モード3（CPU同士対戦）：常にCPU → 常に`1`（真）。

**分かりづらい点：** モード2だけが「盤面の状態（`current_player`）を見て判定する」
動的な条件になっており、モード1・3は最初から結果が決まっている静的な条件になっている。
この非対称性を知らずに読むと、なぜモード2だけ比較式なのか一瞬迷うかもしれない。

---

## まとめ：登場する変数の型と役割一覧

| 変数名 | 主な登場箇所 | 型 | 役割 |
|---|---|---|---|
| `board` | `GameState` | `char[9]` | 盤面本体 |
| `current_player` | `GameState` | `char` | 現在の手番の記号 |
| `game_mode` | `GameState` | `int` | 対戦モード(1〜3) |
| `human_mark` / `cpu_mark` | `GameState` | `char` | モード2専用の役割分担 |
| `oldt` / `newt` | `readRawByte` | `struct termios` | 端末設定の退避・変更用 |
| `isTTY` | `readRawByte` | `int` | 標準入力が端末かどうか |
| `n` | `readRawByte` | `ssize_t` | `read()`の戻り値（読めたバイト数） |
| `forMark` | `minimax`, `getBestMove` | `char` | 誰にとっての最善手かを表す固定パラメータ |
| `opponent` | `minimax` | `char` | `forMark`の逆の記号 |
| `depth` | `minimax` | `int` | 再帰の深さ（手数） |
| `isMaximizing` | `minimax` | `int`(真偽値) | 今の手番が最大化側か最小化側か |
| `bestScore` / `bestMove` | `minimax`, `getBestMove` | `int` | 探索中に見つかった最良の評価値・手 |
| `backup` | `minimax`, `getBestMove` | `char` | 仮置きする前のマスの値の退避用 |
| `hasX` / `hasO` | `isNoWinPossible` | `int`(真偽値) | ある勝ち筋にX/Oが含まれるか |
| `mover` | `playOneTurn` | `char` | その手番の主体の記号 |
| `cpuTurn` | `playOneTurn` | `int`(真偽値) | その手番がCPUによるものか |
