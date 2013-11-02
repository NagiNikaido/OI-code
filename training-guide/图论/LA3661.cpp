#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>

using namespace std;

const int MaxN = 1010;
const int MaxM = 2000010;
const int MaxE = 6000010;

typedef pair<int,int> PII;

struct Node{
	int v,c;
	Node *next;
}*g[MaxM],pool[MaxE],*tail;
int n,m;
int cost[MaxN][MaxN][3];

int mapping(int x,int y,int flag){
	return ((x-1)*(m-1)+(y-1))*2+flag;
}
void make_edge(int u,int v,int c){
	tail->v=v;tail->c=c;tail->next=g[u];g[u]=tail++;
}
void init(){
	memset(g,0,sizeof(g));
	tail=pool;
}
/*
int spfa(int S,int T){
	static int inq[MaxM]={0},dist[MaxM];
	queue<int> q;
	memset(dist,0x7f,sizeof(dist));
	dist[S]=0;inq[S]=1;q.push(S);
	while(!q.empty()){
		int u=q.front();q.pop();inq[u]=0;
		for(Node *p=g[u];p;p=p->next) if(dist[u]+p->c<dist[p->v]){
			dist[p->v]=dist[u]+p->c;
			if(!inq[p->v]) inq[p->v]=1,q.push(p->v);
		}
	}
	return dist[T];
}
*/
int dijkstra(int S,int T){
	static int flag[MaxM],dist[MaxM];
	priority_queue< PII ,vector<PII>,greater<PII> > q;
	memset(flag,0,sizeof(flag));
	memset(dist,0x7f,sizeof(dist));
	dist[S]=0;q.push(make_pair(0,S));
	while(!q.empty()){
		PII t=q.top();q.pop();
		if(flag[t.second]) continue;
		flag[t.second]=1;
		for(Node *p=g[t.second];p;p=p->next) if(dist[t.second]+p->c<dist[p->v]){
			dist[p->v]=dist[t.second]+p->c;
			q.push(make_pair(dist[p->v],p->v));
		}
	}
	return dist[T];
}
int main()
{
	int t=0;
	while(1){
		int S,T;
		scanf("%d%d",&n,&m);
		if(!n && !m) break;
		S=0;T=2*(m)*(n)+1;
		init();
		for(int i=1;i<=n;i++)
			for(int j=1;j<m;j++)
				scanf("%d",&cost[i][j][0]);
		for(int i=1;i<n;i++)
			for(int j=1;j<=m;j++)
				scanf("%d",&cost[i][j][1]);
		for(int i=1;i<n;i++)
			for(int j=1;j<m;j++)
				scanf("%d",&cost[i][j][2]);
		for(int i=1;i<n;i++)
			for(int j=1;j<m;j++){
				int id1=mapping(i,j,1),id2=mapping(i,j,2);
				if(j<m-1) make_edge(id1,mapping(i,j+1,2),cost[i][j+1][1]);
				if(i>1)   make_edge(id1,mapping(i-1,j,2),cost[i][j][0]);
				make_edge(id1,id2,cost[i][j][2]);
				if(j>1)   make_edge(id2,mapping(i,j-1,1),cost[i][j][1]);
				if(i<n-1) make_edge(id2,mapping(i+1,j,1),cost[i+1][j][0]);
				make_edge(id2,id1,cost[i][j][2]);
			}
		for(int i=1;i<n;i++){
			make_edge(S,mapping(i,1,2),cost[i][1][1]);
			make_edge(mapping(i,m-1,1),T,cost[i][m][1]);
		}
		for(int i=1;i<m;i++){
			make_edge(S,mapping(n-1,i,2),cost[n][i][0]);
			make_edge(mapping(1,i,1),T,cost[1][i][0]);
		}
	//	for(int i=S;i<=T;i++){
	//		printf("%d:\n",i);
	//		for(Node *p=g[i];p;p=p->next)
	//			printf("  <%d,%d>=%d\n",i,p->v,p->c);
	//	}
		printf("Case %d: Minimum = %d\n",++t,dijkstra(S,T));
	}
	return 0;
}
