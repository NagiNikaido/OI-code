#include <cstdio>
#include <cstring>

using namespace std;

unsigned long long C(unsigned long long n,unsigned long long r){
	long double s=1;
	for(unsigned long long i=0;i<r;i++) s*=n-i;
	for(unsigned long long i=1;i<=r;i++) s/=i;
	return (unsigned long long)s;
}
unsigned long long f[35][35];
int n;

int main()
{
	while(1){
		scanf("%d",&n);
		if(!n) break;
		memset(f,0,sizeof(f));
		for(int i=1;i<=n;i++) f[0][i]=1;
		f[1][0]=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<i;j++){
				f[i][j]=0;
				for(int k=0;i-k*j>=0;k++)
					f[i][j]+=f[i-k*j][j-1]*C(f[j][j-1]+k-1,k);
			}
			for(int j=i;j<=n;j++) f[i][j]=f[i][j-1];
		}
		for(int i=0;i<=n;i++){
			for(int j=0;j<=n;j++) printf("%4llu",f[i][j]);
			printf("\n");
		}
		printf("%llu\n",f[n][n-1]);
	}
	return 0;
}
