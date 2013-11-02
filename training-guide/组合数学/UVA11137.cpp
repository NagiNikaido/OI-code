#include <cstdio>
#include <cstring>

using namespace std;

int n;
unsigned long long f[10010][25];

int main()
{
	f[0][1]=1;
	for(int i=0;i<=10000;i++)
		for(int j=1;j<=21;j++) if(f[i][j])
			for(int k=j;k<=21 && i+k*k*k<=10000;k++)
				f[i+k*k*k][k]+=f[i][j];
	for(int i=0;i<=10000;i++)
		for(int j=1;j<=21;j++) f[i][j]+=f[i][j-1];
	while(scanf("%d",&n)!=EOF){
		printf("%llu\n",f[n][21]);
	}
	return 0;
}
