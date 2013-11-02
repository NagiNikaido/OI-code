#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MaxN = 20010;
const int MaxA = 100010;

int T;
int n;
int a[MaxN];
int d[MaxA];
int l[MaxN],r[MaxN];

inline int lowbit(int t){
	return t & (-t);
}
int query(int u){
	int res=0;
	while(u){
		res+=d[u];u-=lowbit(u);
	}
	return res;
}
int modify(int u,int t){
	while(u<=100000){
		d[u]+=t;u+=lowbit(u);
	}
}
int main()
{
	scanf("%d",&T);
	while(T--){
		memset(d,0,sizeof(d));
		memset(l,0,sizeof(l));
		memset(r,0,sizeof(r));
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<=n;i++){
			l[i]=query(a[i]);
			modify(a[i],1);
		}
		memset(d,0,sizeof(d));
		for(int i=n;i>=1;i--){
			r[i]=query(a[i]);
			modify(a[i],1);
		}
		long long ans=0;
		for(int i=1;i<=n;i++) ans+=(long long)l[i]*(n-i-r[i])+(long long)r[i]*(i-1-l[i]);
		printf("%lld\n",ans);
	}
}
