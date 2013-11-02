#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int MaxN	=	110;
const int MaxM	=	1010;
const int INF	=	100000000;

struct Node{
	int v,c,num;
	Node *next;
}*g[MaxN],pool[MaxM << 1],*tail=pool;
int n,m,L;
int dist[MaxN],invalid[MaxM],used[MaxM];
int totalDistAfterAttack[MaxM];
int totalDistBeforeAttack[MaxN];
queue<int> q;

int spfa(int s,int *dist,int *used){
	static int inq[MaxN],num[MaxN];	
	int ret=0;
	
	memset(inq,0,sizeof(inq));
	memset(num,0,sizeof(num));
	for(int i=1;i<=n;i++) dist[i]=INF;
	if(used) for(int i=1;i<=m;i++) used[i]=0;
	inq[s]=1;q.push(s);dist[s]=0;
	while(!q.empty()){
		int u=q.front();q.pop();inq[u]=0;
		for(Node *p=g[u];p;p=p->next)
			if(!invalid[p->num] && p->c+dist[u]<dist[p->v]){
				num[p->v]=p->num;
				dist[p->v]=dist[u]+p->c;
				if(!inq[p->v]){
					inq[p->v]=1;q.push(p->v);
				}
			}
	}
	for(int i=1;i<=n;i++){
		ret+=(dist[i]==INF ? L : dist[i]);
		if(used) used[num[i]]=1;
	}
	return ret;
}
void init(){
	tail=pool;
	memset(g,0,sizeof(g));
	memset(invalid,0,sizeof(invalid));
	memset(totalDistAfterAttack,0,sizeof(totalDistAfterAttack));
	memset(totalDistBeforeAttack,0,sizeof(totalDistBeforeAttack));
}
int main()
{
	while(scanf("%d%d%d",&n,&m,&L)!=EOF){
		init();
		for(int i=1;i<=m;i++){
			int u,v,c;
			scanf("%d%d%d",&u,&v,&c);
			tail->v=v;tail->c=c;tail->num=i;tail->next=g[u];g[u]=tail++;
			tail->v=u;tail->c=c;tail->num=i;tail->next=g[v];g[v]=tail++;
		}
		int ans1=0,ans2=0;
		for(int i=1;i<=n;i++){
			totalDistBeforeAttack[i]=spfa(i,dist,used);
			for(int j=1;j<=m;j++)
				if(used[j]){
					invalid[j]=1;
					totalDistAfterAttack[j]+=spfa(i,dist,0);
					invalid[j]=0;
				}
				else totalDistAfterAttack[j]+=totalDistBeforeAttack[i];
		}
		for(int i=1;i<=n;i++) ans1+=totalDistBeforeAttack[i];
		for(int i=1;i<=m;i++) ans2=max(ans2,totalDistAfterAttack[i]);
		printf("%d %d\n",ans1,ans2);
	}
	return 0;
}
