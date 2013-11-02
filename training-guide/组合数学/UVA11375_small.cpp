#include <cstdio>
#include <cstring>

using namespace std;

unsigned long long f[2010],sum[2010];
//int MOVE[2][10]={
//	{0,0,1,1,1,3,2,1,0,0},
//	{0,0,1,1,1,3,3,1,0,0}
//};
int MOVE[10]={6,2,5,5,4,5,6,3,7,6};
int n;
int main()
{
	f[0]=1;
	for(int i=0;i<=40;i++){
		for(int j=0;j<10;j++) if(!(i==0 && j==0)){
			f[i+MOVE[j]]+=f[i];
		}
	}
	for(int i=1;i<=40;i++) sum[i]=f[i]+sum[i-1];
	while(scanf("%d",&n)!=EOF){
		if(n>=6) printf("%llu\n",sum[n]+1);
		else printf("%llu\n",sum[n]);
	}
	return 0;
}
