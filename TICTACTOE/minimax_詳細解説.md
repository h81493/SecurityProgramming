# `minimax(game, forMark, depth, isMaximizing)` 詳細解説

> GitHub: [tictactoe.c#L311-L345](https://github.com/h81493/SecurityProgramming/blob/main/TICTACTOE/tictactoe.c#L311-L345)
> （行番号は本セッション作成時点のもの。リポジトリ側とズレていないか確認してください）

## 1. 概要

`minimax(game, forMark, depth, isMaximizing)` は、現在の盤面から先、
「両者が常に最善手を打ち続けたら最終的にどうなるか」を再帰的に読み切り、
その結果を1つの数値（評価値）として返す関数である。ミニマックス法
（Minimax Algorithm）の中核であり、`getBestMove()`がCPUの1手を決める際に、
候補となる各手について「この手を選んだ後、この先どうなるか」を評価するために
繰り返し呼び出す。

`getBestMove`との役割分担は以下の通り：
- `getBestMove`：**今すぐ打てる9マス**を1つずつ試す（探索木の一番上の1段だけ）。
- `minimax`：それぞれの手を打った**後**、決着がつくまで何手も先を読み切る（探索木の
  残り全部）。

## 2. シグネチャ

```c
int minimax(GameState *game, char forMark, int depth, int isMaximizing)
```

| 項目 | 型 | 説明 |
|---|---|---|
| 引数 `game` | `GameState *` | 盤面へのポインタ。再帰の中で一時的に書き換え、評価後は必ず元に戻す（後述）。 |
| 引数 `forMark` | `char` | 「誰にとっての評価か」を表す記号（`'X'`または`'O'`）。再帰全体を通して変化しない固定値。 |
| 引数 `depth` | `int` | 現在の再帰の深さ（＝これまでに何手先まで仮に進めたか）。最初の呼び出しでは`0`。 |
| 引数 `isMaximizing` | `int`（真偽値として使用） | 今読んでいる手番が`forMark`側なら`1`（真）、相手側なら`0`（偽）。 |
| 戻り値 | `int` | この局面から両者が最善を尽くした場合の評価値。`forMark`にとって良いほど大きく、悪いほど小さい。 |

## 3. ソースコード全文

```c
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
```

## 4. 内部で使用している変数の解説

| 変数 | 型 | 初期値 | 役割 |
|---|---|---|---|
| `opponent` | `char` | `getOpponentMark(forMark)` の戻り値 | `forMark`の逆の記号。以降の勝敗判定・仮置きで使う。 |
| `winner` | `char` | `checkWin(game)` の戻り値 | 現在の盤面の勝者。`'X'`・`'O'`・勝者なしを表す`0`のいずれか。 |
| `bestScore`（`isMaximizing`側） | `int` | `-1000` | forMark側の手番として探している最良（最大）の評価値。理論上の評価値の範囲（-10〜10程度）よりも十分小さいダミー値で初期化し、必ず1回目の比較で更新されるようにしている。 |
| `bestScore`（相手側） | `int` | `1000` | 相手側の手番として探している最良（最小）の評価値。同様の理由で十分大きいダミー値。 |
| `i` | `int` | （ループ変数） | `0`から`8`まで、盤面9マスを順に走査するためのカウンタ。 |
| `backup` | `char` | `game->board[i]` の現在値 | 仮に記号を置く前の、そのマスの元の値を退避しておく変数。評価後は必ずこの値に復元する（バックトラック）。 |
| `score` | `int` | 再帰呼び出し `minimax(...)` の戻り値 | 1つの候補手を仮に置いた場合の、そこから先を読み切った評価値。 |

**`isMaximizing`によって`bestScore`の初期値と更新条件が逆になっている点に注意：**

| | `isMaximizing = 1`（forMark側） | `isMaximizing = 0`（相手側） |
|---|---|---|
| 置く記号 | `forMark` | `opponent` |
| `bestScore`の初期値 | `-1000`（十分小さい） | `1000`（十分大きい） |
| 採用条件 | `score > bestScore`（大きい方を採用） | `score < bestScore`（小さい方を採用） |
| 次の再帰の`isMaximizing` | `0`を渡す（次は相手の番） | `1`を渡す（次はforMarkの番） |

forMark側は「自分にとって一番良い（評価値が大きい）手」を選ぶはずなので最大値を、
相手側は「forMarkにとって一番都合が悪い（評価値が小さい）手」を選ぶはずなので
最小値を、それぞれ探している。

## 5. 内部で呼び出している関数の解説

### 5.1 `getOpponentMark(mark)`

```c
char getOpponentMark(char mark) {
    return (mark == 'X') ? 'O' : 'X';
}
```

- **役割**：指定した記号の相手側の記号を返す、状態を持たない単純な関数。
- `minimax`内では、再帰呼び出しのたびに`opponent`を求め直す（`forMark`は固定なので
  毎回同じ結果になるが、関数の先頭で都度計算している）。

### 5.2 `checkWin(game)`

```c
char checkWin(const GameState *game) {
    static const int lines[8][3] = { {0,1,2}, {3,4,5}, {6,7,8},
                                      {0,3,6}, {1,4,7}, {2,5,8},
                                      {0,4,8}, {2,4,6} };
    // 8パターンそれぞれについて3マスが同じ記号か判定し、勝者の記号 or 0 を返す
}
```

- **役割**：現在の盤面（`minimax`が仮置きした状態を含む）に勝者がいるかどうかを判定する。
- **`minimax`での使い方**：`winner == forMark`なら「forMarkが勝った局面」、
  `winner == opponent`なら「相手が勝った局面」として、それぞれ異なるスコアで
  即座に`return`する（再帰の終了条件の1つ）。

### 5.3 `checkDraw(game)`

```c
int checkDraw(const GameState *game) {
    if (isBoardFull(game)) {
        return 1;
    }
    return isNoWinPossible(game);
}
```

- **役割**：現在の盤面が引き分け（全マス消化、または早期に「もう誰も勝てない」と
  確定した状態）かどうかを判定する。
- **`minimax`での使い方**：`winner`がどちらでもなく（勝者なし）、かつ`checkDraw`が
  真であれば`0`を返して再帰を打ち切る。これにより、全マスが埋まるより前でも
  無駄な深追いをせずに探索を打ち切れる（探索の効率化にもなっている）。
- 内部で`isBoardFull(game)`（全マスが埋まっているか）と`isNoWinPossible(game)`
  （8つの勝ち筋すべてに`X`と`O`の両方が含まれ、もう誰も揃えられないか）の
  どちらかが真であれば引き分けと判定する。

### 5.4 `isEmptyCell(game, index)`

```c
int isEmptyCell(const GameState *game, int index) {
    return game->board[index] == (char)('1' + index);
}
```

- **役割**：指定したマスがまだ空いているかどうかを判定する。
- **`minimax`での使い方**：`for`ループで9マスを走査する際、既に埋まっているマスは
  候補から除外するために使う。

## 6. 再帰の全体像

### 6.1 終了条件（再帰の底）

再帰は無条件に9手続くわけではなく、以下のいずれかが成立した時点で即座に打ち切られる。

```c
if (winner == forMark)  return 10 - depth;  // forMarkの勝ち
if (winner == opponent) return depth - 10;  // 相手の勝ち
if (checkDraw(game))    return 0;           // 引き分け
```

| 状況 | 戻り値 | 意味 |
|---|---|---|
| `forMark`の勝ち | `10 - depth` | `depth`が小さいほど（＝早く勝つほど）大きい値になる（最大`10`）。 |
| 相手の勝ち | `depth - 10` | `depth`が小さいほど（＝早く負けるほど）小さい値になる（最小`-10`）。裏を返せば、深く進んでから負ける方が「まだマシ」と評価される。 |
| 引き分け | `0` | 勝ちでも負けでもない中立の値。 |

`depth`を評価値に組み込んでいる理由は、「同じ“勝ち”でも早く勝てる手を優先し、
同じ“負け”なら少しでも長く粘れる手を選ぶ」ようにするため。これがないと、
1手先で勝てる場合も5手先で勝てる場合も同じ評価値になってしまい、
CPUが遠回りな勝ち方を選んでしまうことがある。

### 6.2 再帰ステップ（決着がついていない場合）

決着がついていなければ、空いているマス全部に「今の手番側の記号」を仮置きし、
`depth + 1`・手番を反転させた`isMaximizing`で自分自身を再帰呼び出しする。

```c
game->board[i] = (isMaximizing ? forMark : opponent);
int score = minimax(game, forMark, depth + 1, !isMaximizing);
game->board[i] = backup; // 必ず元に戻す
```

（実際のコードでは`if (isMaximizing) {...} else {...}`で2つのブロックに分けて
書かれているが、本質的にはこの1つのパターンの繰り返しである。）

- **`depth + 1`**：1手進めたので、深さを1つ増やす。
- **`isMaximizing`の反転**（`0`→`1`または`1`→`0`）：三目並べは1人が1手ずつ交互に
  打つゲームなので、次の手番は必ず今と逆の側になる。

## 7. 具体的な動作イメージ（簡略化した例）

たとえば、`forMark = 'O'`で呼び出され、あと1マスだけ空いている局面を考える。

1. `minimax`が呼ばれる。`checkWin`・`checkDraw`ではまだ決着がついていないとする。
2. 空いている最後の1マスに、今の手番側の記号を仮置きして再帰呼び出し。
3. その再帰呼び出しの中で、盤面は「全マス埋まった」状態になっている。
   - もしこれで`O`（`forMark`）が勝っていれば`10 - depth`を返す。
   - もし`X`（相手）が勝っていれば`depth - 10`を返す。
   - どちらでもなければ`checkDraw`が真になり`0`を返す。
4. この戻り値が1階層上に伝わり、`bestScore`と比較されて（`isMaximizing`に応じて
   最大値または最小値として）採用される。
5. 最終的に一番外側の`minimax`呼び出し（＝`getBestMove`から呼ばれた初回の呼び出し）
   まで評価値が伝播し、`getBestMove`が「どのマスが一番良かったか」を決定する材料になる。

盤面が9マスしかないため、この再帰は深くても9段程度で必ず終了し、
全ての可能な展開を漏れなく評価できる。

## 8. まとめ：呼び出し関係

```
minimax(game, forMark, depth, isMaximizing)
 ├─ getOpponentMark(forMark)   … 相手の記号を求める
 ├─ checkWin(game)             … 勝者がいるか（終了条件）
 ├─ checkDraw(game)            … 引き分けか（終了条件）
 │   ├─ isBoardFull(game)
 │   └─ isNoWinPossible(game)
 ├─ isEmptyCell(game, i)       … 候補マスの絞り込み（ループ内）
 └─ minimax(game, forMark, depth+1, !isMaximizing)  … 自分自身を再帰呼び出し
```

`minimax`は自分自身を再帰的に呼び出す関数であり、`getBestMove`・`minimax`・
`checkWin`・`checkDraw`・`isEmptyCell`・`getOpponentMark`が一体となって
「三目並べの全探索によるCPU思考ルーチン」を構成している。
