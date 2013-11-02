#include <cstdio>
#include <cstring>

using namespace std;

const int MaxN = 4000000;

long long f[4000010];
long long phi[4000010];

void calc(){
	for(int i=2;i<=MaxN;i++) phi[i]=i;
	for(int i=2;i<=MaxN;i++) if(phi[i]==i){
		phi[i]--;
		for(int j=i+i;j<=MaxN;j+=i)
			phi[j]=phi[j] / i * (i-1);
	}
	for(int i=1;i<=MaxN;i++)
		for(int j=i+i;j<=MaxN;j+=i)
			f[j]+=i*phi[j/i];
	for(int i=1;i<=MaxN;i++) f[i]+=f[i-1];
}
int main()
{
	calc();
	int n;
	while(1){
		scanf("%d",&n);
		if(!n) break;
		printf("%lld\n",f[n]);
	}
	return 0;
}
