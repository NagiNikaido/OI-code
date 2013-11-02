#include <cstdio>
#include <cstring>

using namespace std;

unsigned long long f[1000010];
int n;

int main()
{
	for(int i=4;i<=1000000;i++){
		unsigned long long k=i/2-1;
		f[i]=f[i-1]+k*(i-2-k);
	}
	while(1){
		scanf("%d",&n);
		if(n<3) break;
		printf("%llu\n",f[n]);
	}
	return 0;
}
