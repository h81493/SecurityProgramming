# 三目並べ（Tic-Tac-Toe）UML仕様書

本書は `tictactoe_spec.md`（機能仕様書）および `tictactoe.c`（実装）に対応するUML図をまとめたものである。
C言語による手続き型実装のため、状態を保持する `GameState` 構造体と、それを操作する関数群を、
論理的なクラスとして概念モデル化している。

Mermaid記法で記述しているため、GitHubやVSCode（Mermaid拡張）などで図として表示できる。

---

<a id="uml-sec-1"></a>
## 1. クラス図（Class Diagram）

`GameState`（旧: 複数のグローバル変数）にゲーム全体の状態を集約し、
`Board` 操作関数・`Game` 進行管理関数・`ComputerPlayer`（CPU思考）・`InputDevice`（1文字入力）に
責務を分割している。実装上はいずれも `GameState` へのポインタを引数に取る関数群だが、
UML上は関連するクラスとして表現する。

```mermaid
classDiagram
    class GameState {
        <<struct>>
        +char board[9]
        +char current_player
        +int  game_mode
        +char human_mark
        +char cpu_mark
    }

    class Board {
        +initBoard(game GameState*) void
        +printBoard(game GameState*) void
        +isEmptyCell(game GameState*, index int) bool
        +updateBoard(game GameState*, index int) void
        +checkWin(game GameState*) char
        +isBoardFull(game GameState*) bool
        +isNoWinPossible(game GameState*) bool
        +checkDraw(game GameState*) bool
    }

    class Game {
        +getGameMode() int
        +getHumanMark() char
        +getMove(game GameState*) int
        +switchPlayer(game GameState*) void
        +isComputerTurn(game GameState*) bool
        +announceWinner(game GameState*, winner char) void
        +announceDraw(game GameState*) void
        +playOneTurn(game GameState*) void
        +playOneGame(game GameState*) void
        +askPlayAgain() bool
    }

    class ComputerPlayer {
        +getBestMove(game GameState*, forMark char) int
        -minimax(game GameState*, forMark char, depth int, isMaximizing bool) int
    }

    class InputDevice {
        +readRawByte() char
        +readMenuChar() char
        +waitForEnter() void
        +clearScreen() void
    }

    class Main {
        +main() int
    }

    Main --> GameState : 1つだけ実体を保持
    Main --> Game : 起動・制御
    Game --> GameState : ポインタで操作
    Board --> GameState : ポインタで操作
    ComputerPlayer --> GameState : ポインタで操作
    Game --> Board : 盤面操作を委譲
    Game --> ComputerPlayer : CPUの手番で利用
    Game --> InputDevice : 入力受付・画面制御
    ComputerPlayer --> Board : 盤面を評価（checkWin/checkDraw）
```

**対応関係（実装関数 ⇔ クラスメソッド）**

| クラス | メソッド | 対応するC関数 |
|---|---|---|
| Board | initBoard() | `initBoard()` |
| Board | printBoard() | `printBoard()`（内部で`clearScreen()`を呼ぶ） |
| Board | isEmptyCell() | `isEmptyCell()` |
| Board | updateBoard() | `updateBoard()` |
| Board | checkWin() | `checkWin()` |
| Board | isBoardFull() | `isBoardFull()` |
| Board | isNoWinPossible() | `isNoWinPossible()` |
| Board | checkDraw() | `checkDraw()` |
| Game | getGameMode() | `getGameMode()` |
| Game | getHumanMark() | `getHumanMark()` |
| Game | getMove() | `getMove()` |
| Game | switchPlayer() | `switchPlayer()` |
| Game | isComputerTurn() | `isComputerTurn()` |
| Game | announceWinner() | `announceWinner()` |
| Game | announceDraw() | `announceDraw()` |
| Game | playOneTurn() | `playOneTurn()` |
| Game | playOneGame() | `playOneGame()` |
| Game | askPlayAgain() | `askPlayAgain()` |
| ComputerPlayer | getBestMove() | `getBestMove()` |
| ComputerPlayer | minimax() | `minimax()` |
| InputDevice | readRawByte() | `readRawByte()` |
| InputDevice | readMenuChar() | `readMenuChar()` |
| InputDevice | waitForEnter() | `waitForEnter()` |
| InputDevice | clearScreen() | `clearScreen()` |
| Main | main() | `main()` |

---

<a id="uml-sec-2"></a>
## 2. 状態遷移図（State Diagram）

ゲーム全体が取りうる状態と遷移条件（モード選択を含む）。

```mermaid
stateDiagram-v2
    [*] --> ModeSelect : ゲーム起動

    ModeSelect --> MarkSelect : 「CPU対戦」(モード2)を選択
    ModeSelect --> Playing : 「2人対戦」(モード1)を選択
    ModeSelect --> Playing : 「CPU同士対戦」(モード3)を選択

    MarkSelect --> Playing : 先手/後手を選択

    Playing --> Playing : 手番（人間 or CPU）\n勝敗・引き分けが確定せず、交代
    Playing --> XWin : Xの記号が3つ揃う
    Playing --> OWin : Oの記号が3つ揃う
    Playing --> Draw : 全マス埋まる、または\nこれ以上誰も勝てないと確定(早期引き分け)

    XWin --> Replay : 結果表示
    OWin --> Replay : 結果表示
    Draw --> Replay : 結果表示

    Replay --> ModeSelect : 有効な1文字(y/Y)を入力
    Replay --> [*] : y/Y以外を入力、またはEOF
```

---

<a id="uml-sec-3"></a>
## 3. アクティビティ図（Activity Diagram）

1手番あたりの処理フロー。画面クリアと、CPU着手メッセージの表示順序
（機能仕様書 [4.2節](tictactoe_spec.md#sec-4-2) の制約）を反映している。

```mermaid
flowchart TD
    Start([開始]) --> SelMode[対戦モードを選択\n1:2人 2:CPU対戦 3:CPU同士]
    SelMode --> IsMode2{モード2\nCPU対戦?}
    IsMode2 -- Yes --> SelMark[先手/後手を選択]
    IsMode2 -- No --> Init
    SelMark --> Init[盤面初期化]
    Init --> Print1[画面クリア＋盤面表示]
    Print1 --> DetermineTurn{手番の主体は?}

    DetermineTurn -- モード3:常にCPU --> CpuThink3[getBestMove\n現在の手番側の記号]
    DetermineTurn -- モード2:CPU側の手番 --> CpuThink2[getBestMove\ncpuMark]
    DetermineTurn -- モード1 or モード2:人間側 --> Input[1文字入力\nEnter不要]

    CpuThink3 --> Update
    CpuThink2 --> Update

    Input --> ValidNum{1〜9の範囲内?}
    ValidNum -- No --> ErrMsg1[エラー表示]
    ErrMsg1 --> Input
    ValidNum -- Yes --> ValidEmpty{そのマスは\n空いている?}
    ValidEmpty -- No --> ErrMsg2[エラー表示]
    ErrMsg2 --> Input
    ValidEmpty -- Yes --> Update[盤面を更新]

    Update --> Print2[画面クリア＋盤面を再表示]
    Print2 --> WasCpu{直前の手番は\nCPUだった?}
    WasCpu -- Yes --> ShowCpuMove[「CPUはマスNを\n選びました」を表示]
    WasCpu -- No --> IsMode3
    ShowCpuMove --> IsMode3{モード3?}
    IsMode3 -- Yes --> Wait[何かキー入力を待つ]
    Wait --> CheckWin
    IsMode3 -- No --> CheckWin{勝者がいる?}

    CheckWin -- Yes --> ShowWin[勝者を表示]
    ShowWin --> AskReplay
    CheckWin -- No --> CheckDraw{引き分け?\n(全埋まり or 早期確定)}
    CheckDraw -- Yes --> ShowDraw[引き分けを表示\n(理由に応じ文言変更)]
    ShowDraw --> AskReplay
    CheckDraw -- No --> Switch[手番を交代]
    Switch --> DetermineTurn

    AskReplay{もう一度遊ぶ?\n1文字入力}
    AskReplay -- y/Y --> SelMode
    AskReplay -- それ以外/EOF --> End([終了])
```

---

<a id="uml-sec-4"></a>
## 4. シーケンス図（Sequence Diagram）

<a id="uml-sec-4-1"></a>
### 4.1 モード2（人間 対 CPU）

CPUの着手メッセージが、画面クリアを伴う `printBoard()` の**後**に表示される点に注意。

```mermaid
sequenceDiagram
    participant User as ユーザー（人間）
    participant Main as main()
    participant Game as Game(playOneTurn)
    participant Board as Board
    participant CPU as ComputerPlayer
    participant Input as InputDevice

    Main->>Game: モード・先手後手を選択させる
    User->>Game: モード2、先手(X)を選択
    Game->>Board: initBoard() / printBoard()
    Note over Input: printBoard()内でclearScreen()実行

    loop 決着がつくまで
        alt 現在の手番が人間
            Game->>Input: readMenuChar()（1文字、Enter不要）
            User->>Input: マス番号を1文字入力
        else 現在の手番がCPU
            Game->>CPU: getBestMove(cpuMark)
            CPU->>Board: 全空きマスを仮に試す
            CPU->>CPU: minimax() で再帰評価
            CPU-->>Game: 最善手のマス番号
        end
        Game->>Board: updateBoard() / printBoard()
        Note over Input: printBoard()内でclearScreen()実行
        opt 直前がCPUの手番だった場合
            Game->>User: 「CPUはマスNを選びました」
        end
        Game->>Board: checkWin() / checkDraw()
        Board-->>Game: 勝者 or 引き分け or 継続
        Game->>Game: switchPlayer()（決着していなければ）
    end
    Game->>User: 結果表示 → 「もう一度遊びますか？」
```

<a id="uml-sec-4-2"></a>
### 4.2 モード3（CPU 対 CPU、観戦モード）

```mermaid
sequenceDiagram
    participant User as ユーザー（観戦者）
    participant Main as main()
    participant Game as Game(playOneTurn)
    participant Board as Board
    participant CPU as ComputerPlayer
    participant Input as InputDevice

    Main->>Game: 「3:CPU同士の対戦」を選択させる
    User->>Game: モード3を選択
    Game->>Board: initBoard() / printBoard()

    loop 決着がつくまで
        Game->>CPU: getBestMove(currentPlayer)
        CPU->>Board: 全空きマスを仮に試す
        CPU->>CPU: minimax() で再帰評価
        CPU-->>Game: 最善手のマス番号
        Game->>Board: updateBoard() / printBoard()
        Note over Input: clearScreen() → 盤面表示
        Game->>User: 「CPUはマスNを選びました」（盤面表示の後）
        Game->>Input: waitForEnter()
        Game->>User: 「(何かキーを押すと次へ進みます)」
        User->>Input: 何か1文字入力
        Game->>Board: checkWin() / checkDraw()
        Board-->>Game: 勝者 or 引き分け(早期含む) or 継続
        Game->>Game: switchPlayer()（決着していなければ）
    end
    Game->>User: 結果表示（通常は引き分け）→「もう一度遊びますか？」
```

---

<a id="uml-sec-5"></a>
## 5. 図と機能仕様書の対応

| UML図 | 対応する機能仕様書の章 |
|---|---|
| クラス図 | [6. 内部データ仕様](tictactoe_spec.md#sec-6) / [10. 使用関数（想定）](tictactoe_spec.md#sec-10) |
| 状態遷移図 | [3. 対戦モード仕様](tictactoe_spec.md#sec-3) / [7.1 引き分け判定の早期化](tictactoe_spec.md#sec-7-1) / [9. 処理フロー](tictactoe_spec.md#sec-9) |
| アクティビティ図 | [4. 画面表示仕様](tictactoe_spec.md#sec-4) / [5. 入力仕様](tictactoe_spec.md#sec-5) / [8. 画面クリア仕様](tictactoe_spec.md#sec-8) / [9. 処理フロー](tictactoe_spec.md#sec-9) |
| シーケンス図 | [9. 処理フロー](tictactoe_spec.md#sec-9) 全体（モード2・モード3、メッセージ表示順序を含む） |
