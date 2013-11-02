#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

const int MaxN	=	55;
const double eps=	1e-6;

typedef pair<int,double> PID;

#define V first
#define C second
#define v_ptr(_T) vector<_T> :: iterator

int n,m;
vector<PID> g[MaxN];
double dist[MaxN];
int flag[MaxN],inq[MaxN];
int cnt[MaxN];

void init(){
	for(int i=0;i<MaxN;i++) g[i].clear();
}
int spfa(int s,double dt){
	queue<int> q;
	memset(inq,0,sizeof(inq));
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=n;i++) dist[i]=1e16;
	dist[s]=0;inq[s]=1;q.push(s);cnt[s]=1;
	while(!q.empty()){
		int u=q.front();q.pop();inq[u]=0;
		for(v_ptr(PID) p=g[u].begin();p!=g[u].end();p++)
			if(p->C-dt+dist[u]<dist[p->V]){
				dist[p->V]=p->C-dt+dist[u];
				if(!inq[p->V]){
					inq[p->V]=1;q.push(p->V);
					if(++cnt[p->V]>n) return 0;
				}
			}
	}
	return 1;
}
int check(double dt){
	memset(flag,0,sizeof(flag));
	for(int i=1;i<=n;i++) if(!flag[i])
		if(!spfa(i,dt)) return 0;
	return 1;
}
int main()
{
	int T,P=0;
	scanf("%d",&T);
	while(T--){
		double l,r;
		l=r=1e8;
		scanf("%d%d",&n,&m);
		init();
		for(int i=1;i<=m;i++){
			int u,v;
			double c;
			scanf("%d%d%lf",&u,&v,&c);
			g[u].push_back(make_pair(v,c));
			l=min(l,c);
		}
		while(l<r-eps){
			double mid=(l+r)/2;
			if(check(mid)) l=mid;
			else r=mid;
		}
		printf("Case #%d: ",++P);
		if(abs(l-1e8)<=eps) puts("No cycle found."); else printf("%.2lf\n",l);
	}
	return 0;
}
