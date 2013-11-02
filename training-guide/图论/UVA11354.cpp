#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n,m;
struct Edge{
	int u,v,c;
}e[100010];
struct Node{
	int v,c;
	Node *next;
}*g[50010],pool[100010],*tail;
int fa[50010],h[50010];
int d[50010][20],maxc[50010][20];

bool operator <(const Edge &a,const Edge &b){
	return a.c<b.c;
}
void init(){
	memset(g,0,sizeof(g));
	tail=pool;
}
void make_edge(int u,int v,int c){
	tail->v=v;tail->c=c;tail->next=g[u];g[u]=tail++;
	tail->v=u;tail->c=c;tail->next=g[v];g[v]=tail++;
}
int getfather(int u){
	if(fa[u]==u) return u;
	return fa[u]=getfather(fa[u]);
}
void kruskal(){
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++){
		int p=getfather(e[i].u),q=getfather(e[i].v);
		if(p==q) continue;
		fa[p]=q;make_edge(e[i].u,e[i].v,e[i].c);
	}
}
void dfs(int u,int fa){
	h[u]=h[fa]+1;
	for(Node *p=g[u];p;p=p->next) if(p->v!=fa){
		d[p->v][0]=u;maxc[p->v][0]=p->c;
		dfs(p->v,u);
	}
}
void prepare(){
	memset(d,0,sizeof(d));
	memset(maxc,0,sizeof(maxc));
	memset(h,0,sizeof(h));
	dfs(1,0);
	for(int i=1;i<20;i++)
		for(int j=1;j<=n;j++)
			d[j][i]=d[d[j][i-1]][i-1],maxc[j][i]=max(maxc[j][i-1],maxc[d[j][i-1]][i-1]);
}
int query(int u,int v){
	if(h[u]<h[v]) swap(u,v);
	int p=u,q=v,maxt=0;
	int j=0;
	while(j>=0){
		if(h[d[p][j]]<h[q]) j--;
		else{
			maxt=max(maxt,maxc[p][j]);
			p=d[p][j++];
		}
	}
	if(p==q) return maxt;
	j=0;
	while(j>=0){
		if(d[p][j]==d[q][j]) j--;
		else{
			maxt=max(maxt,max(maxc[p][j],maxc[q][j]));
			p=d[p][j],q=d[q][j];j++;
		}
	}
	return max(maxt,max(maxc[p][0],maxc[q][0]));
}
int main()
{
	int first=1;
	while(scanf("%d%d",&n,&m)!=EOF){
		init();
		for(int i=1;i<=m;i++) scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].c);
		sort(e+1,e+m+1);
		kruskal();
		prepare();
		int q;scanf("%d",&q);
		if(first) first=0; else puts("");
		for(int i=1;i<=q;i++){
			int u,v;scanf("%d%d",&u,&v);
			printf("%d\n",query(u,v));
		} /**/
	} 
	return 0;
}
