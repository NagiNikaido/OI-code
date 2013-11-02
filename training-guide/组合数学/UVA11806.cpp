#include <cstdio>
#include <cstring>

using namespace std;

const int MOD = 1000007;

int c[600][600];
int t,n,m,k;

inline int C(int i,int j){
	return i>=0 ? c[i][j] : 0;
}
int main()
{
	for(int i=0;i<=500;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++)
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%MOD;
	}
//	for(int i=0;i<=10;i++){
//		for(int j=0;j<=i;j++) printf("%d ",c[i][j]);
//		puts("");
//	}
	scanf("%d",&t);
	for(int i=1;i<=t;i++){
		scanf("%d%d%d",&n,&m,&k);
		printf("Case %d: %d\n",i,((C(m*n,k)
								-2*C(m*n-n,k)
								-2*C(m*n-m,k)
								+C(m*n-2*m,k)
								+C(m*n-2*n,k)
								+4*C(m*n-m-n+1,k)
								-2*C(m*n-m-2*n+2,k)
								-2*C(m*n-n-2*m+2,k)
								+C(n*m-2*n-2*m+4,k))
								%MOD+MOD)%MOD);
	}
	return 0;
}
