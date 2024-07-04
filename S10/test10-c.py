#!/usr/bin/python3
import subprocess
size = 100_000_000

print("プログラム実行前")
subprocess.run("free")
array = [0]*size
print("メモリ確保後")
subprocess.run("free")
