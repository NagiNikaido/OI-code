#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MaxLen = 100000000;

int n;
struct BigInt{
	int a[110];
	int len;
	BigInt () {len=0;memset(a,0,sizeof(a));}
	BigInt (int p){
		len=0;memset(a,0,sizeof(a));
		while(p){
			a[len++]=p%MaxLen;
			p/=MaxLen;
		}
	}
	BigInt operator =(int p){
		memset(a,0,sizeof(a));len=0;
		while(p){
			a[len++]=p%MaxLen;
			p/=MaxLen;
		}
		return *this;
	}
	BigInt operator +=(int p){
		BigInt b(p);
		int k=0;
		len=max(len,b.len);
		for(int i=0;i<len;i++){
			k+=a[i]+b.a[i];
			a[i]=k%MaxLen;
			k/=MaxLen;
		}
		if(k) a[len++]=k;
		return *this;
	}
	BigInt operator +=(const BigInt &b){
		int k=0;
		len=max(len,b.len);
		for(int i=0;i<len;i++){
			k+=a[i]+b.a[i];
			a[i]=k%MaxLen;
			k/=MaxLen;
		}
		if(k) a[len++]=k;
		return *this;
	}
	BigInt operator +(const BigInt &b){
		BigInt c;
		int k=0;
		c.len=max(len,b.len);
		for(int i=0;i<c.len;i++){
			k+=a[i]+b.a[i];
			c.a[i]=k%MaxLen;
			k/=MaxLen;
		}
		if(k) c.a[c.len++]=k;
		return c;
	}
	void print(){
		if(len){
			printf("%d",a[len-1]);
			for(int i=len-2;i>=0;i--) printf("%08d",a[i]);
			puts("");
		}
		else puts("0");
	}
}f[2010],sum[2010];
int MOVE[10]={6,2,5,5,4,5,6,3,7,6};
int main()
{
	f[0]=1;
	for(int i=0;i<=2000;i++){
		for(int j=0;j<10;j++)if(!(i==0 && j==0)){
			f[i+MOVE[j]]+=f[i];
		}
	}
	for(int i=1;i<=2000;i++) sum[i]=f[i]+sum[i-1];
	while(scanf("%d",&n)!=EOF){
		if(n>=6) (sum[n]+1).print();
		else sum[n].print();
	}
	return 0;
}
