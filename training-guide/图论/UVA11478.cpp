#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int MaxN = 510;
const int MaxM = 3000;

int n,m;
struct Node{
	int v,c;
	Node *next;
}*g[MaxN],pool[MaxM<<1],*tail;
int inq[MaxN],dist[MaxN],cnt[MaxN];

void init(){
	memset(g,0,sizeof(g));
	tail=pool;
}
int spfa(int offset){
	queue<int> q;
	memset(inq,0,sizeof(inq));
	memset(cnt,0,sizeof(cnt));
	memset(dist,0x7f,sizeof(dist));
	inq[0]=1;cnt[0]=1;dist[0]=0;q.push(0);
	while(!q.empty()){
		int u=q.front();q.pop();inq[u]=0;
		for(Node *p=g[u];p;p=p->next){
			int tmp=dist[u]-(u==0 ? 0 : offset)+p->c;
			if(tmp<dist[p->v]){
				dist[p->v]=tmp;
				if(!inq[p->v]){
					inq[p->v]=1;q.push(p->v);
					if(++cnt[p->v]>(n+1)) return 0;
				}
			}
		}
	}
	return 1;
}
int main()
{
	while(scanf("%d%d",&n,&m)!=EOF){
		int l,r,ans=0;
		init();
		r=0x80000000;
		for(int i=1;i<=m;i++){
			int u,v,c;
			scanf("%d%d%d",&u,&v,&c);
			tail->v=u;tail->c=c;tail->next=g[v];g[v]=tail++;
			r=max(r,c);
		}
		n++;
		for(int i=1;i<n;i++){
			tail->v=i;tail->c=0;tail->next=g[0];g[0]=tail++;
		}
		if(spfa(r+1)) {puts("Infinite");continue;}
		if(!spfa(1)) {puts("No Solution");continue;}
		l=1;r++;
		while(l<r-1){
			int mid=l+r >> 1;
			if(spfa(mid)) l=mid;
			else r=mid;
		}
		printf("%d\n",l);
	}
	return 0;
}
