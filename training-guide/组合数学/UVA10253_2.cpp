#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

unsigned long long f[35];
unsigned long long C(unsigned long long n,unsigned long long r){
	long double s=1;
	for(unsigned long long i=0;i<r;i++) s*=n-i;
	for(unsigned long long i=1;i<=r;i++) s/=i;
	return (unsigned long long)s;
}

unsigned long long dfs(int ,int );
unsigned long long F(int n){
	if(f[n]) return f[n];
	return f[n]=dfs(n,n-1);
}
unsigned long long dfs(int n,int upper){
	if(n<=1 || upper<=1) {
	//	printf("n=%d upper=%d result=1 (*)\n",n,upper);
		return 1;
	}
	unsigned long long sum=0,tmp1,tmp2;
	for(int i=min(n,upper);i>1;i--)
		for(int k=1;n-i*k>=0;k++){
			tmp1=dfs(n-i*k,i-1);
			tmp2=F(i);
			sum+=tmp1*C(tmp2+k-1,k);
		}
	//printf("n=%d upper=%d result=%d\n",n,upper,sum);
	return sum+1;
}
int main(){
	f[1]=1;
//	printf("%llu\n",F(30));
//	for(int i=1;i<=30;i++) printf("f[%d]=%llu\n",i,f[i]);
	F(30);
	int n;
	while(1){
		scanf("%d",&n);
		if(!n) break;
		printf("%llu\n",n==1 ? 1 : f[n]*2);
	}
	return 0;
}
