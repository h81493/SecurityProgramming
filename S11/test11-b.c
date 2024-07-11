#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int main(void) {
  int 🎲1,🎲2;
  char 丁半[6];
  int 丁=0;
  char 🍵1[]={0xe2,0x9a,0x80,0x00};//⚀
  char 🍵2[]={0xe2,0x9a,0x80,0x00};//⚀
  time_t 🕰️;//⏲️
  🕰️ = time(NULL);
  srand((unsigned) 🕰️ ); // 23.3.4.5 modiﬁers:
  🎲1=rand()%6+1;
  🎲2=rand()%6+1;
  🍵1[2]=🍵1[2]+(🎲1-1);
  🍵2[2]=🍵2[2]+(🎲2-1);
  if((🎲1+🎲2)%2 == 丁) {
    strcpy(丁半,"丁");
  } else {
    strcpy(丁半,"半");
  }
  printf("🎲サイコロを振ります。 %s%s %d,%d %s\n",🍵1,🍵2,🎲1,🎲2,丁半);
}
