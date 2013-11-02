#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int MaxN = 110;
int rev[5]={0,3,4,1,2};
int dx[5]={0,-1,0,1 ,0};
int dy[5]={0,0 ,1,0,-1};
		/* 0 1  2 3  4*/
int r,c,r1,c1,r2,c2;
int cost[MaxN][MaxN][5];
int dist[MaxN*MaxN*5];
int inq[MaxN*MaxN*5];

struct Node{
	int v,c;
	Node *next;
}*g[MaxN*MaxN*5],pool[MaxN*MaxN*100],*tail=pool;

void init(){
	memset(g,0,sizeof(g));
	memset(cost,0,sizeof(cost));
	tail=pool;
}
inline void new_edge(int u,int v,int c){
	tail->v=v;tail->c=c;tail->next=g[u];g[u]=tail++;
}
inline int mapping(int x,int y,int d){
	return r*c*d+(x-1)*c+y;
}
int spfa(int S,int T){
	queue<int> q;
	memset(dist,0x7f,sizeof(dist));
	dist[S]=0;inq[S]=1;q.push(S);
	while(!q.empty()){
		int u=q.front();q.pop();
		inq[u]=0;
		for(Node *p=g[u];p;p=p->next) if(p->c+dist[u]<dist[p->v]){
			dist[p->v]=p->c+dist[u];
			if(!inq[p->v]) q.push(p->v),inq[p->v]=1;
		}
	}
	return dist[T];
}
int main()
{
	int t=0,ans;
	while(1){
		scanf("%d%d%d%d%d%d",&r,&c,&r1,&c1,&r2,&c2);
		if(!r && !c && !r1 && !c1 && !r2 && !c2) break;
		init();
		for(int i=1;i<=r;i++){
			int t;
			for(int j=1;j<c;j++){
				scanf("%d",&t);
				cost[i][j][2]=cost[i][j+1][4]=t;
			}
			if(i==r) break;
			for(int j=1;j<=c;j++){
				scanf("%d",&t);
				cost[i][j][3]=cost[i+1][j][1]=t;
			}
		}
		for(int i=1;i<=r;i++)
			for(int j=1;j<=c;j++)
				for(int d=1;d<=4;d++){
					if(cost[i][j][d]){
						new_edge(mapping(i,j,d),mapping(i+dx[d],j+dy[d],d),cost[i][j][d]);
						new_edge(mapping(i,j,0),mapping(i+dx[d],j+dy[d],d),cost[i][j][d]*2);
						new_edge(mapping(i,j,0),mapping(i+dx[d],j+dy[d],0),cost[i][j][d]*2);
					}
					if(cost[i][j][rev[d]]){
						new_edge(mapping(i,j,d),mapping(i,j,0),cost[i][j][rev[d]]);
					}
				}
		ans=spfa(mapping(r1,c1,0),mapping(r2,c2,0));
		printf("Case %d: ",++t);
		if(ans==0x7f7f7f7f) puts("Impossible"); else printf("%d\n",ans);
	}
	return 0;
}
