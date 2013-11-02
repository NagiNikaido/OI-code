#include <cstdio>
#include <cctype>
#include <cstring>
#include <utility>
#include <vector>

using namespace std;

#define EXPNT first
#define COEFF second
#define v_ptr(_T) vector< _T > :: iterator

typedef pair<long long,long long> PLL;

char buf[1000];
long long D;
vector<PLL> P;

long long power(long long x,long long y,long long mod){
	if(y==0) return 1;
	if(y==1) return x%mod;
	long long tmp=power(x,y>>1,mod);
	tmp=tmp * tmp % mod;
	if(y&1) return tmp * x % mod;
	else return tmp;
}
long long getint(char *(&p)){
	long long res=0;
	while(isdigit(*p)) res=res*10+*(p++)-'0';
	return res ? res : 1;
}
void solute(char expr[],vector<PLL> &list,long long &mod){
	list.clear();mod=0;
	int posr=0;
	for(posr=0;expr[posr]!=')';posr++);
	char *p=expr+posr+2; 
	mod=getint(p);
	p=expr+1;
	while(p<expr+posr){
		int flag=0;
		long long c=0,e=0;
		if(*p=='-') flag=-1;
		else flag=1;
		if(*p=='n') c=1;
		else{
			if(!isdigit(*p)) ++p;
			c=flag*getint(p);
		}
		if(*p=='n'){
			++p;
			if(*p=='^') {++p;e=getint(p);}
			else e=1;
		}
		list.push_back(make_pair(e,c));
	}
}
long long calc(long long n,vector<PLL> &list,long long mod){
	long long res=0;
	for(v_ptr(PLL) p=P.begin();p!=P.end();p++)
		res=(res+(power(n,p->EXPNT,mod)*p->COEFF)%mod)%mod;
	return res;
}
int main()
{
	int cntc=0;
	while(1){
		scanf("%s",buf);
		if(buf[0]=='.') break;
		solute(buf,P,D);
	//	for(v_ptr(PLL) p=P.begin();p!=P.end();p++)
	//		printf("%lld*n^%lld\n",p->COEFF,p->EXPNT);
	//	printf("mod=%d\n",D);
		int flag=1;
		for(long long t=0;t<=P.begin()->EXPNT;t++)
			if(calc(t,P,D)){
				flag=0;
				break;
			}
		printf("Case %d: ",++cntc);
		if(flag) puts("Always an integer");
		else puts("Not always an integer");
	}
	return 0;
}
