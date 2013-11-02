#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

const int MaxN = 1010;

typedef pair<int,int> PII;

#define U first
#define V second
#define C first
#define v_ptr(_T) vector<_T> :: iterator

queue<int> q;
int inq[1010];
int dist[1010];
vector<PII> g[1010],edge;
vector<int> g2[1010];
int f[1010],ind[1010];
int n,m;

void spfa(){
	memset(dist,0x7f,sizeof(dist));
	q.push(2);inq[2]=1;dist[2]=0;
	while(!q.empty()){
		int u=q.front();q.pop();inq[u]=0;
		for(v_ptr(PII) p=g[u].begin();p!=g[u].end();p++)
			if(dist[u]+p->C<dist[p->V]){
				dist[p->V]=dist[u]+p->C;
				if(!inq[p->V]){
					inq[p->V]=1;
					q.push(p->V);
				}
			}
	}
}
void init(){
	memset(f,0,sizeof(f));
	memset(ind,0,sizeof(ind));
	for(int i=1;i<=1000;i++) g[i].clear(),g2[i].clear();
	edge.clear();
}
int main()
{
	while(scanf("%d%d",&n,&m)==2){
		init();
		for(int i=1;i<=m;i++){
			int u,v,c;
			scanf("%d%d%d",&u,&v,&c);
			g[u].push_back(make_pair(c,v));
			g[v].push_back(make_pair(c,u));
			edge.push_back(make_pair(u,v));
			edge.push_back(make_pair(v,u));
		}
		spfa();
		for(v_ptr(PII) p=edge.begin();p!=edge.end();p++)
			if(dist[p->V]<dist[p->U]) g2[p->U].push_back(p->V),ind[p->V]++;
		for(int i=1;i<=n;i++) if(!ind[i]) q.push(i);
		f[1]=1;
		while(!q.empty()){
			int t=q.front();q.pop();
			for(v_ptr(int) p=g2[t].begin();p!=g2[t].end();p++){
				f[*p]+=f[t];ind[*p]--;
				if(!ind[*p]) q.push(*p);
			}
		}
		printf("%d\n",f[2]);
	}
	return 0;
}
