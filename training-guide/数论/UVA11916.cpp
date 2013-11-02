#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <map>
#include <utility>

using namespace std;

const int MaxN = 510;
const int MOD = 100000007ll;

typedef pair<int,int> PII;

set<PII> B;
long long t,n,m,k,b,r;
int x[MaxN],y[MaxN];

long long multi(long long x,long long y,long long mod){
	if(y==0) return 0;
	if(y==1) return x%mod;
	long long t=multi(x,y>>1,mod);
	t=(t+t)%mod;
	if(y&1) return (t+x)%mod;
	else return t;
}
long long power(long long x,long long y,long long mod){
	if(y==0) return 1;
	if(y==1) return x%mod;
	long long t=power(x,y>>1,mod);
	t=multi(t,t,mod);
	if(y&1) return multi(t,x,mod);
	else return t;
}
long long log_z(long long a,long long b,long long mod){
	long long m,v,e=1;
	m=sqrt(mod);
	v=power(power(a,m,mod),mod-2,mod);
	map<long long,long long> x;
	x[1]=0;
	for(long long i=1;i<m;i++){
		e=multi(e,a,mod);
		if(x.find(e)==x.end()) x[e]=i;
	}
	for(long long i=0;i<m;i++){
		if(x.find(b)!=x.end()) return i*m+x[b];
		b=multi(b,v,mod);
	}
	return -1;
}
long long cnt(){
	long long s=0;
	for(int i=1;i<=b;i++) if(x[i]<m && B.find(make_pair(x[i]+1,y[i]))==B.end()) s++;
	for(int i=1;i<=b;i++) if(x[i]==1) s--;s+=n;
	return multi(power(k,s,MOD),power(k-1,n*m-s-b,MOD),MOD);
}
long long calc(){
	long long res=cnt();
	if(res==r) return m;
	int c=0;
	for(int i=1;i<=b;i++) if(x[i]==m) c++;
	res=multi(res,multi(power(k,c,MOD),power(k-1,n-c,MOD),MOD),MOD); m++;
	if(res==r) return m;
	return m+log_z(power(k-1,n,MOD),multi(r,power(res,MOD-2,MOD),MOD),MOD);
}
int main()
{
	scanf("%lld",&t);
	int j=0;
	while(t--){
		scanf("%lld%lld%lld%lld",&n,&k,&b,&r);
		m=1;B.clear();
		for(int i=1;i<=b;i++){
			scanf("%d%d",&x[i],&y[i]);
			B.insert(make_pair(x[i],y[i]));
			m=max(m,(long long)x[i]);
		}
		printf("Case %d: %lld\n",++j,calc());
	}
	return 0;
}
