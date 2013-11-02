#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n,m,maxcost;
struct Edge{
	int u,v,c,f;
}e[10010];

int check(int lower){
	static int g[65][65];
	static int pre[65],flag[65],inq[65];
	int sum=0;
	
	memset(g,0x7f,sizeof(g));
	memset(flag,0,sizeof(flag));
	
	for(int i=1;i<=m;i++) if(e[i].f>=lower) g[e[i].u][e[i].v]=min(e[i].c,g[e[i].u][e[i].v]);
	while(1){
		for(int i=1;i<n;i++) if(!flag[i]){
			pre[i]=i;
			for(int j=0;j<n;j++) if(!flag[j] && g[j][i]<g[pre[i]][i]) pre[i]=j;
			if(pre[i]==i) return 0;
		}
		int XXXXX=0;
		for(int i=1;i<n;i++) if(!flag[i]){
			int j;
			memset(inq,0,sizeof(inq));
			inq[0]=1;
			for(j=i;!inq[j];j=pre[j]) inq[j]=1;
			if(j==0) continue;
			for(j=i;;){
				sum+=g[pre[j]][j];
				for(int k=0;k<n;k++) if(!flag[k] && g[k][j]<0x7f7f7f7f && k!=pre[j])
					g[k][j]-=g[pre[j]][j];
				j=pre[j];
				if(j==i) break;
			}
			for(j=0;j<n;j++) if(j!=i){
				for(int k=pre[i];k!=i;k=pre[k]){
					g[i][j]=min(g[i][j],g[k][j]);
					g[j][i]=min(g[j][i],g[j][k]);
				}
			}
			for(j=pre[i];j!=i;j=pre[j]) flag[j]=1;
			XXXXX=1;break;
		}
		if(!XXXXX){
			for(int i=1;i<n;i++) if(!flag[i]) sum+=g[pre[i]][i];
			break;
		}
	} 
	return sum<=maxcost;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&n,&m,&maxcost);
		for(int i=1;i<=m;i++) scanf("%d%d%d%d",&e[i].u,&e[i].v,&e[i].f,&e[i].c);
		int l=0,r=maxcost+1;
		while(l<r-1){
		//	printf("%d %d\n",l,r);
			int mid=l+r >> 1;
			if(check(mid)) l=mid;
			else r=mid;
		}
		if(!l) puts("streaming not possible."); else printf("%d kbps\n",l);
	}
	return 0;
}
