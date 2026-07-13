# `getBestMove(game, forMark)` 詳細解説

> GitHub: [tictactoe.c#L351-L369](https://github.com/h81493/SecurityProgramming/blob/main/TICTACTOE/tictactoe.c#L351-L369)
> （行番号は本セッション作成時点のもの。リポジトリ側とズレていないか確認してください）

## 1. 概要

`getBestMove(game, forMark)` は、ミニマックス法（Minimax Algorithm）を使って、
「`forMark`（`'X'` または `'O'`）にとっての最善手」を1つ計算して返す関数である。
CPU対戦モード（モード2）・CPU同士対戦モード（モード3）の両方で、CPUの着手を
決定するために呼び出される。

## 2. シグネチャ

```c
int getBestMove(GameState *game, char forMark)
```

| 項目 | 型 | 説明 |
|---|---|---|
| 引数 `game` | `GameState *` | 盤面など現在のゲーム状態へのポインタ。読み取りだけでなく、探索中に一時的に書き換える（後述）ため`const`は付いていない。 |
| 引数 `forMark` | `char` | 「誰にとっての最善手を探すか」を指定する記号。`'X'`または`'O'`。 |
| 戻り値 | `int` | 最善手のマス番号（`board`配列上のインデックス、`0`〜`8`）。 |

## 3. ソースコード全文

```c
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
```

## 4. 内部で使用している変数の解説

| 変数 | 型 | 初期値 | 役割 |
|---|---|---|---|
| `bestScore` | `int` | `-1000` | それまでに見つかった最も良い評価値を記録する。ミニマックスの評価値は理論上どんなに大きくても`10`程度、小さくても`-10`程度にしかならないため、`-1000`は「まだ何も見つかっていない」ことを表す十分に小さいダミー値として使っている。 |
| `bestMove` | `int` | `-1` | それまでに見つかった最も良い手（マス番号）を記録する。`-1`は「まだ有効な手が見つかっていない」ことを表すダミー値（盤面のインデックスは`0`〜`8`なので、`-1`は絶対に本物の手と衝突しない）。 |
| `i` | `int` | （ループ変数） | `0`から`8`まで、盤面9マスすべてを順番に走査するためのループカウンタ。 |
| `backup` | `char` | `game->board[i]` の現在値 | 仮に`forMark`を置く前の、そのマスの元の値（多くは空きマスを表す番号文字）を退避しておく変数。評価が終わったら必ずこの値に戻す（バックトラック）。 |
| `score` | `int` | `minimax(...)` の戻り値 | そのマスに`forMark`を置いたと仮定した場合の、以降の展開を先読みした評価値。 |

### 処理の流れとの対応

```
for (i = 0; i < 9; i++) {              // ← 変数 i でマスを1つずつ走査
    if (isEmptyCell(game, i)) {        // 空きマスだけを候補にする
        backup = game->board[i];       // ① 元の値を backup に退避
        game->board[i] = forMark;      // ② forMark を仮に置く
        score = minimax(...);          // ③ 置いた後の展開を評価し、score に格納
        game->board[i] = backup;       // ④ backup で元に戻す（バックトラック）
        if (score > bestScore) {       // score が今までの bestScore より良ければ
            bestScore = score;         //   bestScore を更新
            bestMove = i;              //   bestMove も更新（このマスを暫定の最善手にする）
        }
    }
}
return bestMove;                       // 最終的に一番良かった手を返す
```

## 5. 内部で呼び出している関数の解説

`getBestMove`自身は「9マスを1つずつ試して`minimax`に評価させる」というループ
だけで、実際の思考ロジックの大部分は呼び出し先の関数群にある。それぞれを解説する。

### 5.1 `isEmptyCell(game, index)`

```c
int isEmptyCell(const GameState *game, int index) {
    return game->board[index] == (char)('1' + index);
}
```

- **役割**：指定したマス（`index`）がまだ空いているかどうかを判定する。
- **仕組み**：`initBoard()`で盤面は`board[0]='1'`, `board[1]='2'`, …, `board[8]='9'`と
  初期化される。つまり「そのマスの値が、まだ初期値（マス番号の文字）のままかどうか」を
  チェックすれば「空きマスかどうか」が分かる、という設計になっている。
  誰かが着手していれば値は`'X'`か`'O'`に書き換わっているので、この式は偽になる。
- `getBestMove`ではこの関数を使って、既に埋まっているマスを候補から除外している。

### 5.2 `minimax(game, forMark, depth, isMaximizing)`

```c
int minimax(GameState *game, char forMark, int depth, int isMaximizing) {
    char opponent = getOpponentMark(forMark);
    char winner = checkWin(game);
    if (winner == forMark)  return 10 - depth;
    if (winner == opponent) return depth - 10;
    if (checkDraw(game))    return 0;

    if (isMaximizing) {
        /* forMark側の手番：最大値を探す */
        ...
    } else {
        /* 相手側の手番：最小値を探す */
        ...
    }
}
```

- **役割**：「今の盤面から先、両者が最善を尽くしたら最終的にどうなるか」を再帰的に
  先読みし、数値スコアとして返す、ミニマックス法の中核。
- **`getBestMove`からの呼び出し方**：`minimax(game, forMark, 0, 0)` という形で呼ばれる。
  - `depth = 0`：これから始まる先読みの深さの起点。
  - `isMaximizing = 0`：`getBestMove`側で既に`forMark`の手を1つ仮置きした直後なので、
    次の手番は「相手」になる。相手は`forMark`にとって都合の悪い手を選ぶはずなので、
    次のターンは「評価値を最小化する側」として評価を始める。
- **引数**

  | 引数 | 型 | 意味 |
  |---|---|---|
  | `game` | `GameState *` | 盤面。再帰の中でも同じ盤面を仮置き・復元しながら使い回す。 |
  | `forMark` | `char` | 誰にとっての評価かは再帰全体を通じて固定。 |
  | `depth` | `int` | 再帰の深さ（あと何手読んだか）。勝敗の評価値を「早い決着ほど極端な値にする」ために使う。 |
  | `isMaximizing` | `int`（真偽値） | 今読んでいる手番が`forMark`側なら真、相手側なら偽。 |

- **戻り値の意味**：`forMark`が勝つなら`10 - depth`（早く勝つほど高得点）、
  相手が勝つなら`depth - 10`（遅く負けるほどマシ）、引き分けなら`0`。

### 5.3 `getOpponentMark(mark)`

```c
char getOpponentMark(char mark) {
    return (mark == 'X') ? 'O' : 'X';
}
```

- **役割**：指定した記号の「相手側」の記号を返す、状態を持たない単純な関数。
- `minimax`の中で、`forMark`から見た相手の記号（`opponent`）を求めるために使われる。

### 5.4 `checkWin(game)`

```c
char checkWin(const GameState *game) {
    static const int lines[8][3] = { {0,1,2}, {3,4,5}, {6,7,8},
                                      {0,3,6}, {1,4,7}, {2,5,8},
                                      {0,4,8}, {2,4,6} };
    ...
    for (i = 0; i < 8; i++) {
        // 3マスとも同じ記号（'X'か'O'）なら、その記号を返す
    }
    return 0; // 誰も勝っていない
}
```

- **役割**：現在の盤面に勝者がいるかどうかを判定する。
- **仕組み**：縦・横・斜め、全8パターンの「3マスの組み合わせ」を`lines`配列に
  持っておき、それぞれについて3マスが同じ記号で揃っているかを順にチェックする。
  揃っていればその記号（`'X'`か`'O'`）を返し、どれも揃っていなければ`0`を返す。
- `minimax`は、この戻り値を使って「決着がついたかどうか」を再帰の終了条件として
  利用している。

### 5.5 `checkDraw(game)`

```c
int checkDraw(const GameState *game) {
    if (isBoardFull(game)) {
        return 1;
    }
    return isNoWinPossible(game);
}
```

- **役割**：現在の盤面が引き分けかどうかを判定する。以下の2つの関数に処理を委譲する。

#### `isBoardFull(game)`
```c
int isBoardFull(const GameState *game) {
    // 9マス全部が isEmptyCell() でなければ真
}
```
全マスが埋まっているかどうかだけを見る、単純な判定。

#### `isNoWinPossible(game)`
```c
int isNoWinPossible(const GameState *game) {
    // 8つの勝ち筋すべてに X と O の両方が含まれていれば真
}
```
全マスが埋まっていなくても、「どの勝ち筋にも既に`X`と`O`の両方が入ってしまい、
これ以上誰も3つ揃えられない」状態になっていれば真を返す（早期引き分け判定）。
`checkDraw`はこの2つの「どちらか一方でも真なら引き分け」という形で判定している。

- `minimax`は、勝者もおらず`checkDraw`も偽の場合だけ、まだ手を続けられると
  判断して再帰を続ける。

## 6. まとめ：呼び出し関係

```
getBestMove(game, forMark)
 ├─ isEmptyCell(game, i)          … 候補マスの絞り込み
 └─ minimax(game, forMark, 0, 0)  … 各候補手の評価
     ├─ getOpponentMark(forMark)  … 相手の記号を求める
     ├─ checkWin(game)            … 勝者がいるか（再帰の終了条件）
     ├─ checkDraw(game)           … 引き分けか（再帰の終了条件）
     │   ├─ isBoardFull(game)
     │   └─ isNoWinPossible(game)
     ├─ isEmptyCell(game, i)      … 再帰内での候補マスの絞り込み
     └─ minimax(...)              … さらに先を再帰的に評価
```

`getBestMove`自体は「1段目」の分岐（＝実際にCPUが打つマス）を決めるためのループに
過ぎず、思考の本体（何手も先まで読む部分）はすべて`minimax`の再帰呼び出しが担っている。
