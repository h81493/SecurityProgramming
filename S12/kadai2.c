#include <stdio.h>
#include <stdbool.h>

#define N 5      /* ノードの個数*/
#define INF __INT_MAX__ >>1   /* 十分大きい定数*/
#define GOAL 5-1 /* 終点のノード番号*/

int distance(int edge[N][N]) {
  int dist[N] = {INF,INF,INF,INF,INF};
  //始点ノード距離。初期値はINF。要素番号がノード番号を表す。 */
  int done[N] = {0};//初期値は0。最短距離が確定したら1を入れる。
  int curNode; //更新起点ノードのノード番号
  int minDist; //更新起点ノードを求める際に使用する一時変数 */
  int k;//要素番号
  dist[1-1]=0;//始点の始点ノード距離を0とする。
  while(true) {
    minDist=INF;
    for(k=1-1;k<N;k++) {
      if(done[k]==0 && dist[k]<minDist) {
        minDist = dist[k];
        curNode = k;
      }
    }
    done[curNode]=1;
    if(curNode==GOAL)
      return dist[curNode];
    for(k=1-1;k<N;k++) {
      if(dist[curNode]+edge[curNode][k]<dist[k] && done[k]==0)
        dist[k]=dist[curNode]+edge[curNode][k];
                    //C言語ではedge[m][n] 疑似言語はedge[m,n]
    }
  }
}
int main(void) {
  int edge[N][N] ={ // edge[m,n]にはノードmからノードnへの距離を格納
                    // 2つのノードが隣接していない場合にはINFを格納
    {   ,   ,   ,   ,   },
    {   ,   ,   ,   ,   },
    {   ,   ,   ,   ,   },
    {   ,   ,   ,   ,   },
    {   ,   ,   ,   ,   }
  };
  printf("distance = %d\n",distance(edge));
  return 0;
}