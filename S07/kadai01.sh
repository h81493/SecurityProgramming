#!/bin/bash
set -ex          # エラーが起きたら即終了
gcc kadai01.c sort01.c
set +e          # -e を一時無効化
./a.out > ./kadai01.txt
RET=$?          # リターンコードを保存
set -e          # -e を再有効化
ls -l ./kadai01.txt
md5sum ./kadai01.txt
if [ $RET -eq 0 ]; then
  tail -1 ./kadai01.txt
else
  tail -8 ./kadai01.txt
fi
