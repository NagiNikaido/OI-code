#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

unsigned long long n,m;

int main()
{
	while(1){
		scanf("%llu%llu",&n,&m);
		if(!n && !m) break;
		if(n<m) swap(n,m);
		printf("%llu\n",2*m*(m-1)*(2*m-4)/3+2*m*(m-1)*(n-m+1)+m*n*(n+m-2));
	}
	return 0;
}
