#include <stdio.h>
#include <stdlib.h>

#define W 640
     // 幅
#define H 480
     // 高
#define Wb (3*W)
     // 幅バイト

int main(void)
{
  FILE* fp;
  char header[54] = {};         // 管理情報を格納する
  char image[Wb*H] = {};         // 画像データを格納する(3×W8×H8)

  // 管理情報を作成
  header[0] = 66;
  header[1] = 77;

  int* di;
  di = (int*)(header + 2);       // ファイルサイズ
  *di = Wb*H+54;
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
  // https://en.wikipedia.org/wiki/SMPTE_color_bars
  // https://www.arib.or.jp/english/html/overview/doc/6-STD-B28v1_0-E1.pdf#page=8
  for (int i = 0; i < Wb*H; i += 3) {
    int x = ((i/3)%W);
    int y = i/Wb;
    if(y < H*7/12) { // Pattern1
      if(x>=0 && x < 1*W/8) { // 40% Gray
        image[i]   = 104;          // 青
	      image[i+1] = 104;          // 緑
	      image[i+2] = 104;          // 赤
      } else if( x < 13*W/56) { // 75% Whilte
	      image[i]   = 180;          // 青
	      image[i+1] = 180;          // 緑
	      image[i+2] = 180;          // 赤
      } else if( x < 19*W/56) {  // 75% Yellow
      	image[i]   = 16;            // 青
      	image[i+1] = 180;          // 緑
	      image[i+2] = 180;          // 赤
      } else if( x < 25*W/56) {  // 75% Cyan
	      image[i]   = 180;          // 青
	      image[i+1] = 180;          // 緑
	      image[i+2] = 16;          // 赤
      } else if( x < 31*W/56) {  // 75% Green
      	image[i]   = 16;          // 青
	      image[i+1] = 180;          // 緑
	      image[i+2] = 16;          // 赤
      } else if( x < 37*W/56) {  // 75% Magenda
	      image[i]   = 180;          // 青
	      image[i+1] = 16;          // 緑
	      image[i+2] = 180;          // 赤
      } else if( x < 43*W/56) {  // 75% Red
      	image[i]   = 16;          // 青
	      image[i+1] = 16;          // 緑
	      image[i+2] = 180;          // 赤
      } else if( x < 49*W/56) {  // 75% Blue
	      image[i]   = 180;          // 青
	      image[i+1] = 16;          // 緑
	      image[i+2] = 16;          // 赤
      } else { // 40% Gray
	      image[i]   = 104;          // 青
	      image[i+1] = 104;          // 緑
	      image[i+2] = 104;          // 赤
      }
    } else if(y < H*8/12) { // Pattern2
      if(x>=0 && x < 1*W/8) { // 100% Cyan
	      image[i]   = 235;          // 青
	      image[i+1] = 235;          // 緑
	      image[i+2] = 16;          // 赤
      } else if( x < 13*W/56) { // 100% Whilte
	      image[i]   = 235;          // 青
	      image[i+1] = 235;          // 緑
	      image[i+2] = 235;          // 赤
      } else if( x < 49*W/56) {  // 75% Whilte
      	image[i]   = 180;            // 青
      	image[i+1] = 180;          // 緑
	      image[i+2] = 180;          // 赤
      } else { // 100% Blue
	      image[i]   = 235;          // 青
	      image[i+1] = 16;          // 緑
	      image[i+2] = 16;          // 赤
      }
    } else if(y < H*9/12) { // Pattern3
      if(x>=0 && x < 1*W/8) { // 100% Yellow
	      image[i]   = 16;          // 青
	      image[i+1] = 235;          // 緑
	      image[i+2] = 235;          // 赤
      } else if( x < 49*W/56) { // Y-Ramp
        int x1 = x-W/8 > 0 ? x-W/8 : 0;
        // x1/(3*W/4)*(235+1)
        image[i]   = 4*x1*(235+1)/(3*W);
        image[i+1] = 4*x1*(235+1)/(3*W);
        image[i+2] = 4*x1*(235+1)/(3*W);
      } else { // 100% Red
	      image[i]   = 16;          // 青
	      image[i+1] = 16;          // 緑
	      image[i+2] = 235;          // 赤
      }
    } else { // Pattern 4
      // 220 * 15/100 + 15 + 1=
      if(x>=0 && x < 1*W/8) { // 15% Gray
	      image[i]   = 49;          // 青
	      image[i+1] = 49;          // 緑
	      image[i+2] = 49;          // 赤
      } else if( x < 2*W/7) { // 0% Black
	      image[i]   = 16;          // 青
	      image[i+1] = 16;          // 緑
	      image[i+2] = 16;          // 赤
      } else if( x < W/2) { // 100% White
	      image[i]   = 235;          // 青
	      image[i+1] = 235;          // 緑
	      image[i+2] = 235;          // 赤
      } else if( x < 33*W/56) { // 0% Black
	      image[i]   = 16;          // 青
	      image[i+1] = 16;          // 緑
	      image[i+2] = 16;          // 赤
        //220 * (-2)/100 + 15 + 1
      } else if( x < 5*W/8) { // -2% Black
	      image[i]   = 12;          // 青
	      image[i+1] = 12;          // 緑
	      image[i+2] = 12;          // 赤
      } else if( x < 37*W/56) { // 0% Black
	      image[i]   = 16;          // 青
	      image[i+1] = 16;          // 緑
	      image[i+2] = 16;          // 赤
        //220 * (+2)/100 + 15 + 1
      } else if( x < 39*W/56) { // +2% Black
	      image[i]   = 20;          // 青
	      image[i+1] = 20;          // 緑
	      image[i+2] = 20;          // 赤
      } else if( x < 41*W/56) { // 0% Black
	      image[i]   = 16;          // 青
	      image[i+1] = 16;          // 緑
	      image[i+2] = 16;          // 赤
        //220 * (+4)/100 + 15 + 1
      } else if( x < 43*W/56) { // +4% Black
	      image[i]   = 25;          // 青
	      image[i+1] = 25;          // 緑
	      image[i+2] = 25;          // 赤
      } else if( x < 7*W/8) { // 0% Black
	      image[i]   = 16;          // 青
	      image[i+1] = 16;          // 緑
	      image[i+2] = 16;          // 赤
      } else { // 15% Gray
 	      image[i]   = 49;          // 青
	      image[i+1] = 49;          // 緑
	      image[i+2] = 49;          // 赤
      }
    }
  }
  char f[] = "04bmp.bmp";

  // https://www.jpcert.or.jp/sc-rules/c-fio03-c.html
  if ((fp = fopen(f, "wbx")) == NULL) {
    exit(1);
  }

  // データ書き込み
  fwrite(header, 54, 1, fp);  // 管理情報
  fwrite(image, 3*W*H, 1, fp);  // 画像データ

  fclose(fp);

  return 0;
}

