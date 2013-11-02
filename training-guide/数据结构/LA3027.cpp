#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace std;

const int MaxN = 20010;

struct Union_set{
	int n;
	int d[MaxN],_[MaxN];
	void init(int _n){
		n=_n;
		for(int i=1;i<=n;i++) d[i]=0,_[i]=i;
	}
	int getfather(int u,int *D=0){
		if(u==_[u]) return u;
		_[u]=getfather(_[u],d+u);
		if(D) *D+=d[u];
		return _[u];
	}
	int queryDist(int u){
		getfather(u);
		return d[u];
	}
	void join(int u,int v){ // v -> root
		d[u]=abs(u-v)%1000;
		_[u]=v;
		getfather(u);
	}
}s;

int main()
{
	int t,n;
	char buf[5];
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		s.init(n);
		while(1){
			scanf("%s",buf);
			if(buf[0]=='O') break;
			else if(buf[0]=='I'){
				int u,v;
				scanf("%d%d",&u,&v);
				s.join(u,v);
			}
			else if(buf[0]=='E'){
				int u;
				scanf("%d",&u);
				printf("%d\n",s.queryDist(u));
			}
		}
	}
	return 0;
}
