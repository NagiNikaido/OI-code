#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

#define v_ptr(_T) vector< _T > :: iterator

const int MaxN = 40010;
const unsigned long long MOD = 1000000007;

int n,m,t;
vector<int> g[MaxN];
unsigned long long f[MaxN];
int sum[MaxN];
int flag[MaxN];
unsigned long long fact[MaxN],re_fact[MaxN];

void dfs(int u){
	f[u]=sum[u]=1;
	for(v_ptr(int) p=g[u].begin();p!=g[u].end();p++){
		dfs(*p);sum[u]+=sum[*p];
		f[u]=f[u]*f[*p]%MOD*re_fact[sum[*p]]%MOD;
	}
	f[u]=f[u]*fact[sum[u]-1]%MOD;
}
unsigned long long power(unsigned long long a,unsigned long long b){
	if(b==0) return 1;
	if(b==1) return a%MOD;
	unsigned long long tmp=power(a,b>>1);
	if(b&1) return tmp*tmp%MOD*a%MOD;
	else return tmp*tmp%MOD;
}

int main()
{
	fact[0]=1;
	for(int i=1;i<=40000;i++) fact[i]=(fact[i-1]*i)%MOD;
	re_fact[40000]=power(fact[40000],MOD-2);
	for(int i=40000;i>=1;i--)
		re_fact[i-1]=re_fact[i]*i%MOD;
	scanf("%d",&t);
	while(t--){
		memset(flag,0,sizeof(flag));
		for(int i=0;i<=n;i++) g[i].clear();
		memset(f,0,sizeof(f));
		
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++){
			int u,v;
			scanf("%d%d",&u,&v);
			flag[u]=1;
			g[v].push_back(u);
		}
		for(int i=1;i<=n;i++) if(!flag[i]) g[0].push_back(i);
		dfs(0);
		printf("%llu\n",f[0]);
	}
	return 0;
}
