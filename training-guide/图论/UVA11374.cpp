#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

struct Edge{
	int u,v,c;
}g2[2010];
struct Node{
	int v,c;
	Node *next;
}*g[510],pool[2010],*tail=pool;

int n,op,ed,m,k;
int pre[510][510];
int inq[510];
int dist[510][510];

void spfa(int op){
	queue<int> q;
	memset(pre[op],0,sizeof(int)*510);
	memset(dist[op],0x7f,sizeof(int)*510);
	memset(inq,0,sizeof(inq));
	q.push(op);inq[op]=1;dist[op][op]=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		inq[u]=0;
		for(Node *p=g[u];p;p=p->next) if(dist[op][u]+p->c<dist[op][p->v]){
			dist[op][p->v]=dist[op][u]+p->c;
			pre[op][p->v]=u;
			if(!inq[p->v]){
				inq[p->v]=1;q.push(p->v);
			}
		}
	}
}
void printPath(int u,int v){
	if(u==v) printf("%d",u);
	else{printPath(u,pre[u][v]);printf(" %d",v);}
}
void printReversedPath(int u,int v){
	if(u==v) printf("%d",u);
	else{printf("%d ",v);printReversedPath(u,pre[u][v]);}
}
int main()
{
	int cnt=0;
	while(scanf("%d%d%d",&n,&op,&ed)!=EOF){
		int ans=0x7f7f7f7f,ansu=0,ansv=0;
		memset(g,0,sizeof(g));tail=pool;
		scanf("%d",&m);
		for(int i=1;i<=m;i++){
			int u,v,c;
			scanf("%d%d%d",&u,&v,&c);
			tail->v=v;tail->c=c;tail->next=g[u];g[u]=tail++;
			tail->v=u;tail->c=c;tail->next=g[v];g[v]=tail++;
		}
		scanf("%d",&k);
		for(int i=1;i<=k;i++){
			scanf("%d%d%d",&g2[i].u,&g2[i].v,&g2[i].c);
			g2[i+k]=g2[i];swap(g2[i+k].u,g2[i+k].v);
		}
		spfa(op);spfa(ed);
		ansu=0,ans=dist[op][ed];
		for(int i=1;i<=k*2;i++)
			if(dist[op][g2[i].u]!=0x7f7f7f7f && dist[ed][g2[i].v]!=0x7f7f7f7f
				&& dist[op][g2[i].u]+dist[ed][g2[i].v]+g2[i].c<ans){
					ans=dist[op][g2[i].u]+dist[ed][g2[i].v]+g2[i].c;
					ansu=g2[i].u,ansv=g2[i].v;
			}
		if(cnt) puts(""); else cnt++;
		if(!ansu){
			printPath(op,ed);puts("");
			puts("Ticket Not Used");
			printf("%d\n",ans);
		}
		else{
			printPath(op,ansu);printf(" ");
			printReversedPath(ed,ansv);puts("");
			printf("%d\n%d\n",ansu,ans);
		}
	}
	return 0;
}
