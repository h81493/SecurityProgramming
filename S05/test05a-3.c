/*
  状態機械の実装:
複雑な状態遷移を持つ状態機械（ステートマシン）の実装では、
goto文を使用することで状態遷移を明示的に記述しやすくなります。
 */
state1:
    // 状態1の処理
    if (condition1) goto state2;
    goto end;

state2:
    // 状態2の処理
    if (condition2) goto state3;
    goto end;

state3:
    // 状態3の処理
    if (condition3) goto state1;
    goto end;

end:
    // 終了処理

