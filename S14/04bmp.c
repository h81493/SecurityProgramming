#include <stdio.h>
#include <stdlib.h>

#define W 640
#define H 480

int main(void)
{
  FILE* fp;
  char header[54] = {};         // 管理情報を格納する
  char image[W*H*3] = {};         // 画像データを格納する(3×W8×H8)

  // 管理情報を作成
  header[0] = 66;
  header[1] = 77;

  int* di;
  di = (int*)(header + 2);       // ファイルサイズ
  *di = 3*W*H+54;
  di = (int*)(header + 10);
  *di = 54;
  di = (int*)(header + 14);
  *di = 40;
  di = (int*)(header + 18);      // 横幅ピクセル数W
  *di = W;
  di = (int*)(header + 22);      // 縦幅ピクセル数H
  *di = -1*H;

  short* ds;
  ds = (short*)(header + 26);
  *ds = 1;
  ds = (short*)(header + 28);
  *ds = 24;

  // 画像データを作成
  for (int i = 0; i < 3*W*H; i += 3) {
    if(i/(3*W)>=H*3/4) {
      image[i] = (i%(3*W)) % 256;
      image[i+1] = (i%(3*W)) % 256;
      image[i+2] = (i%(3*W)) % 256;
    } else {
      if(i%(3*W)>=0 && i%(3*W) < 3*W/7) {
	image[i]   = 191;          // 青
	image[i+1] = 191;          // 緑
	image[i+2] = 191;          // 赤
      } else if( i%(3*W) < 2*3*W/7) {
	image[i]   = 0;            // 青
	image[i+1] = 191;          // 緑
	image[i+2] = 191;          // 赤
      } else if( i%(3*W) < 3*3*W/7) {
	image[i]   = 191;          // 青
	image[i+1] = 191;          // 緑
	image[i+2] = 0;          // 赤
      } else if( i%(3*W) < 4*3*W/7) {
	image[i]   = 0;          // 青
	image[i+1] = 191;          // 緑
	image[i+2] = 0;          // 赤
      } else if( i%(3*W) < 5*3*W/7) {
	image[i]   = 191;          // 青
	image[i+1] = 0;          // 緑
	image[i+2] = 191;          // 赤
      } else if( i%(3*W) < 6*3*W/7) {
	image[i]   = 0;          // 青
	image[i+1] = 0;          // 緑
	image[i+2] = 191;          // 赤
      } else if( i%(3*W) < 7*3*W/7) {
	image[i]   = 191;          // 青
	image[i+1] = 0;          // 緑
	image[i+2] = 0;          // 赤
      } else {
	image[i]   = 0;          // 青
	image[i+1] = 0;          // 緑
	image[i+2] = 0;          // 赤
      }
    }
  }
  char f[] = "04bmp.bmp";

  if ((fp = fopen(f, "wbx")) == NULL) {
    exit(1);
  }

  // データ書き込み
  fwrite(header, 54, 1, fp);  // 管理情報
  fwrite(image, 3*W*H, 1, fp);  // 画像データ

  fclose(fp);

  return 0;
}

