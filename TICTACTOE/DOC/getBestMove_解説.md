# `getBestMove(game, forMark)` 関数解説

> **GitHub上のソースコード**
> - リポジトリ: [h81493/SecurityProgramming (TICTACTOE)](https://github.com/h81493/SecurityProgramming/tree/main/TICTACTOE)
> - ファイル全体: [`tictactoe.c`](https://github.com/h81493/SecurityProgramming/blob/main/TICTACTOE/tictactoe.c)
> - `minimax()` 本体: [tictactoe.c#L311-L345](https://github.com/h81493/SecurityProgramming/blob/main/TICTACTOE/tictactoe.c#L311-L345)
> - `getBestMove()` 本体: [tictactoe.c#L351-L369](https://github.com/h81493/SecurityProgramming/blob/main/TICTACTOE/tictactoe.c#L351-L369)
>
> ※ 行番号は、本ドキュメント作成時点の `tictactoe.c`（本セッションで作成した版）を基準にしています。
> リポジトリ側のファイルに差分がある場合はズレる可能性があるため、リンク先で実際の行がずれていないか一度ご確認ください。

`getBestMove(game, forMark)` は、ミニマックス法を使って「`forMark`（`'X'` か `'O'`）に
とっての最善手」を1つ計算して返す関数です。`tictactoe.c` の実装を対象に解説します。

## 1. シグネチャと役割（[GitHubで見る](https://github.com/h81493/SecurityProgramming/blob/main/TICTACTOE/tictactoe.c#L351-L369)）

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

- **引数**
  - `game`：盤面など現在のゲーム状態へのポインタ。
  - `forMark`：「誰にとっての最善手を探すか」を指定する記号（`'X'` または `'O'`）。CPU対戦モード
    （モード2）でもCPU同士対戦モード（モード3）でも、この記号を差し替えるだけで同じロジックを
    使い回せる。
- **戻り値**：最善手のマス番号（`0`〜`8`のインデックス）。

## 2. 処理の流れ

「今すぐ着手できる9マスのうち、まだ空いているマスそれぞれに実際に`forMark`を試しに置いてみて、
その後の展開を`minimax()`で評価し、一番評価が高かったマスを選ぶ」という**全探索**である。

1手ずつ、以下を繰り返す（`for (i = 0; i < 9; i++)`）。

```c
char backup = game->board[i];   /* ① 今のマスの中身を退避 */
game->board[i] = forMark;       /* ② forMarkを仮に置いてみる */
int score = minimax(game, forMark, 0, 0); /* ③ その後の展開を再帰的に評価 */
game->board[i] = backup;        /* ④ 仮に置いた手を元に戻す（バックトラック） */
```

①〜④の「仮に置く→評価する→元に戻す」という操作を**バックトラック**と呼ぶ。実際に盤面を
変更するのではなく、一時的に変更して評価した後、必ず元の状態に復元するのがポイントである。
これにより、`board`配列を余分にコピーすることなく、1つの配列だけで全パターンを試せる。

## 3. `minimax()`の呼び出し方の意味

```c
int score = minimax(game, forMark, 0, 0);
```

引数はそれぞれ：

- `forMark`：誰にとっての評価かは変わらず、探索全体を通して固定。
- `depth = 0`：これから始まる再帰探索の深さの起点（手数のカウント）。
- `isMaximizing = 0`：**ここが重要**。`getBestMove`側で既に`forMark`の手を1つ置いた直後
  なので、次の手番は「相手」になる。相手はできるだけ`forMark`にとって不利な（＝評価値が低い）
  手を選ぶはずなので、次のターンは「最小化する側」＝`isMaximizing = 0`として評価を始める。

## 4. `minimax()`本体の中身（再掲、[GitHubで見る](https://github.com/h81493/SecurityProgramming/blob/main/TICTACTOE/tictactoe.c#L311-L345)）

```c
int minimax(GameState *game, char forMark, int depth, int isMaximizing) {
    char opponent = getOpponentMark(forMark);
    char winner = checkWin(game);
    if (winner == forMark)  return 10 - depth;   /* forMarkの勝ち：早く勝つほど高評価 */
    if (winner == opponent) return depth - 10;   /* 相手の勝ち：遅く負けるほどマシ */
    if (checkDraw(game))    return 0;            /* 引き分け：中立 */

    if (isMaximizing) {
        /* forMark側の手番：全ての空きマスを試し、一番高い評価値を採用 */
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
        /* 相手側の手番：全ての空きマスを試し、一番低い評価値を採用 */
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

- **終了条件（再帰の底）**：勝敗がついたか、引き分けが確定した時点で数値を返して再帰を打ち切る。
  - `forMark`が勝つ盤面：`10 - depth`。深さ（手数）が浅いほど（＝早く勝つほど）大きい値
    （最大10）。
  - 相手が勝つ盤面：`depth - 10`。深さが浅いほど（＝早く負けるほど）小さい値（最小-10）。
    深く進んでから負ける方がまだマシという評価。
  - 引き分け：`0`。
- **再帰ステップ**：まだ決着していなければ、空いているマス全部に「今の手番側の記号」を仮置き
  し、`depth + 1`・手番を反転（`isMaximizing`を裏返す）して自分自身を再帰呼び出しする。
  - `isMaximizing = 1`（forMark側の番）なら、返ってきたスコアの**最大値**を採用（forMarkに
    とって一番良い選択をするはずだから）。
  - `isMaximizing = 0`（相手の番）なら、返ってきたスコアの**最小値**を採用（相手はforMarkに
    とって一番都合の悪い選択をするはずだから）。

この「自分の番なら最大化、相手の番なら最小化」を交互に繰り返しながら盤面が埋まるまで
（または決着がつくまで）再帰することで、**両者が最善を尽くした場合に最終的にどうなるか**を
先読みできる。

## 5. なぜこれで「CPUが絶対に負けない」のか

`minimax()`は9マスしかない三目並べの**全ての可能な展開**（最大でも高々9!通り程度、実際は
決着で打ち切られるのでもっと少ない）を漏れなく評価する。相手が常に最善手（自分にとって最悪の
手）を指してくると仮定した上で、それでも一番良い結果になる手を選ぶため、理論的に負けることが
ない（勝てる局面では確実に勝ち、勝てない局面では引き分けに持ち込む）。

## 6. `getBestMove`が実際に選ぶ手

`getBestMove`は、9マス全部について上記`minimax`の評価値を求め、その中で**最初に見つかった
最高評価のマス**（`score > bestScore`、同点なら先に見つかった方を優先＝番号の小さいマス）を
返す。同じ評価値の手が複数ある場合、常にマス番号の若い方が選ばれる、という決定的な（毎回同じ
入力なら同じ手を返す）挙動になる。

## 7. 計算量について

3×3の盤面なので最大深さは9、分岐数も最大9からどんどん減っていくため、全探索してもごく一瞬で
終わる（アルファベータ枝刈りなどの高速化は行っていないが、この規模では不要）。もし4×4以上に
拡張する場合は、探索空間が急激に大きくなるため、アルファベータ枝刈りや探索深さの制限が必要に
なる（`tictactoe_spec.md` の「拡張候補」の章も参照）。
