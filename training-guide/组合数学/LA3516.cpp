#include <cstdio>
#include <cstring>

using namespace std;

const long long MOD=1000000000LL;

char st[310];
long long f[310][310];

long long F(int l,int r){
	if(l==r) return 1;
	if(f[l][r]>=0) return f[l][r];
	f[l][r]=0;
	for(int i=l+2;i<=r;i++)
		if(st[i]==st[l])
			f[l][r]=(f[l][r]+F(l+1,i-1)*F(i,r))%MOD;
	return f[l][r];
}
int main()
{
	while(scanf("%s",st)!=EOF){
		memset(f,0xff,sizeof(f));
		printf("%lld\n",F(0,strlen(st)-1));
	}
	return 0;
}

