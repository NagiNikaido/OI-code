#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>

using namespace std;

const int MaxN = 25;
const int MaxC = 10100;

int n,m;
struct Node{
	int v,c,num;
	Node *next;
}*g[MaxC],pool[MaxC<<5],*tail=pool;
int cost[MaxN];
int seq[MaxN];
int len[MaxN];
int cities[MaxN][MaxN];
map<int,int> id;
int last;

void init(){
	memset(g,0,sizeof(g));tail=pool;
}
void make_edge(int u,int v,int c,int num){
	tail->v=v;tail->c=c;tail->num=num;tail->next=g[u];g[u]=tail++;
//	tail->v=u;tail->c=c;tail->num=num;tail->next=g[v];g[v]=tail++;
}
int mapping(int u,int cnt){
	return 400*cnt+id[u];
}
void spfa(int S,int T){
	queue<int> q;
	stack<int> st;
	static int inq[MaxC],dist[MaxC],fa[MaxC],from[MaxC];
	memset(inq,0,sizeof(inq));
	memset(fa,0,sizeof(fa));
	memset(from,0,sizeof(from));
	memset(dist,0x7f,sizeof(dist));
	dist[S]=0;inq[S]=1;q.push(S);
	while(!q.empty()){
		int u=q.front();q.pop();
		inq[u]=0;
		for(Node *p=g[u];p;p=p->next) if(dist[u]+p->c<dist[p->v]){
			dist[p->v]=dist[u]+p->c;
			from[p->v]=p->num;fa[p->v]=u;
			if(!inq[p->v]){
				inq[p->v]=1;q.push(p->v);
			}
		}
	}
	printf("%d\n",dist[T]);
	int u=T;
	while(u!=S){
		st.push(from[u]);
		u=fa[u];
	}
	printf("  Tickets used:");
	while(!st.empty()){
		printf(" %d",st.top());st.pop();
	}
	puts("");
}
int main()
{
	int t=0;
	while(1){
		scanf("%d",&n);if(!n) break;
		t++;memset(len,0,sizeof(len));
		id.clear();last=0;
		for(int i=1;i<=n;i++){
			int l;
			scanf("%d%d",&cost[i],&l);
			while(l--){
				int a;scanf("%d",&a);
				cities[i][++len[i]]=a;
				if(id.find(a)==id.end()) id[a]=++last;
			}
		}
		scanf("%d",&m);
		for(int P=1;P<=m;P++){
			init();int s;scanf("%d",&s);
			for(int i=1;i<=s;i++) scanf("%d",&seq[i]);
			for(int i=1;i<=n;i++){
				for(int j=2;j<=s;j++){
					int nxt=j;
					for(int k=2;k<=len[i];k++){
						if(cities[i][k]==seq[nxt]) nxt++;
						make_edge(mapping(cities[i][1],j-1),mapping(cities[i][k],nxt-1),cost[i],i);
						if(nxt>s) break;
					}
				}
			}
			printf("Case %d, Trip %d: Cost = ",t,P);
			spfa(mapping(seq[1],1),mapping(seq[s],s));
		}
	}
	return 0;
}
