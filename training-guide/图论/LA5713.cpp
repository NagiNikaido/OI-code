#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int n;
struct Edge{
	int u,v;
	double c;
}g[1000010];
bool operator <(const Edge &a,const Edge &b){
	return a.c<b.c;
}
inline double sqr(double t){
	return t*t;
}
inline double dist(int x1,int y1,int x2,int y2){
	return sqrt(sqr(x1-x2)+sqr(y1-y2));
}

int fa[1010];
vector<int> a[1010];
double cost[1010][1010];
int p[1010];
int x[1010],y[1010];

int tail;

int getfather(int t){
	if(fa[t]==t) return t;
	return fa[t]=getfather(fa[t]);
}
double kruskal(){
	double sum=0;
	for(int i=1;i<=n;i++) {fa[i]=i;a[i].clear();a[i].push_back(i);}
	for(int i=1;i<tail;i++){
		int p=getfather(g[i].u),q=getfather(g[i].v);
		if(p==q) continue;
		sum+=g[i].c;fa[q]=p;
		for(vector<int> :: iterator p1=a[p].begin();p1!=a[p].end();p1++)
			for(vector<int> :: iterator p2=a[q].begin();p2!=a[q].end();p2++)
				cost[*p1][*p2]=cost[*p2][*p1]=g[i].c;
		for(vector<int> :: iterator p2=a[q].begin();p2!=a[q].end();p2++)
			a[p].push_back(*p2);
	}
	return sum;
}
int main()
{
	int cnt;
	scanf("%d",&cnt);
	while(cnt--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d%d%d",&x[i],&y[i],&p[i]);
		tail=1;
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++){
				g[tail].u=g[tail+1].v=i;
				g[tail].v=g[tail+1].u=j;
				g[tail].c=g[tail+1].c=dist(x[i],y[i],x[j],y[j]);
				tail+=2;
			}
		sort(g+1,g+tail);
		double sum=kruskal();
		double ans=0;
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				ans=max(ans,(p[i]+p[j])/(sum-cost[i][j]));
		printf("%.2lf\n",ans);
	}
	return 0;
}
