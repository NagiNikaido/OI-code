#include <cstdio>
#include <cstring>

using namespace std;

const int MaxN = 100010;
struct Union_set{
	int n;
	int _[MaxN];
	void init(int _n){
		n=_n;
		memset(_,0,sizeof(_));
		for(int i=1;i<=n;i++) _[i]=i;
	}
	int getfather(int u){
		if(_[u]==u) return u;
		return _[u]=getfather(_[u]);
	}
	int query(int u,int v){
		return getfather(u)==getfather(v);
	}
	void unionsets(int u,int v){
		_[getfather(u)]=getfather(v);
	}
}s;

int main()
{
	int a,b;
	while(scanf("%d",&a)!=EOF){
		if(a==-1) {puts("0");continue;}
		scanf("%d",&b);
		s.init(100000);
		s.unionsets(a,b);
		int ans=0;
		while(1){
			scanf("%d",&a);if(a==-1) break;
			scanf("%d",&b);
			if(s.query(a,b)) ans++;
			else s.unionsets(a,b);
		}
		printf("%d\n",ans);
	}
	return 0;
}
