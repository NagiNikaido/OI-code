#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int c,s;
int list[15][110],len[15],x[15];
set<int> hash[15];
long long sum,tot;
int maxt;

void solve(){
	for(int i=1;i<=c;i++){
		hash[i].clear();
		if(i!=maxt) for(int j=1;j<=len[i];j++) hash[i].insert(list[i][j]);
	}
	int t=0;
	while(s){
	//	printf("%d %d\n",t,s);
		for(int i=1;i<=len[maxt];i++){
			long long n=(long long)x[maxt]*t+list[maxt][i];
			int flag=0;
			if(!n) continue;
			for(int j=1;j<=c;j++) if(j!=maxt && hash[j].find(n%x[j])==hash[j].end()){
				flag=1;break;
			}
			if(!flag) {printf("%lld\n",n);s--;if(!s) break;}
		}
		t++;
	}
	puts("");
}

vector<long long> solutions;
int a[15];

long long gcd(long long a,long long b){
	if(!b) return a;
	else return gcd(b,a%b);
}
long long ex_gcd(long long a,long long b,long long &x,long long &y){
	if(!b){x=1,y=0;return a;}
	else{
		long long tmp=ex_gcd(b,a%b,y,x);
		y-=x*(a/b);
		return tmp;
	}
}
long long solute(){
	long long y=0;
	for(int i=1;i<=c;i++){
		long long p=0,q=0;
		long long w=sum/x[i];
		ex_gcd(w,x[i],p,q);
		y=(y+w*p*a[i])%sum;
	}
	return (y+sum)%sum;
}
void dfs(int dep){
	if(dep>c) solutions.push_back(solute());
	else
		for(int i=1;i<=len[dep];i++){
			a[dep]=list[dep][i];
			dfs(dep+1);
		}
}
void solve2(){
	solutions.clear();
	dfs(1);
	sort(solutions.begin(),solutions.end());
	int t=0;
	while(s){
		for(vector<long long> :: iterator p=solutions.begin();
				p!=solutions.end();p++){
					long long n=sum * t + *p;
					if(n>0){
						printf("%lld\n",n);
						s--;
						if(!s) break;
					}
				}
		t++;
	}
	puts("");
}
int main()
{
	while(scanf("%d%d",&c,&s)){
		if(!c && !s) break;
		tot=1,sum=1,maxt=1;
		for(int i=1;i<=c;i++){
			scanf("%d%d",&x[i],&len[i]);sum*=x[i],tot*=len[i];
			for(int j=1;j<=len[i];j++) scanf("%d",&list[i][j]);
			sort(list[i]+1,list[i]+len[i]+1);
			if(len[i]*x[maxt]<len[maxt]*x[i]) maxt=i;
		}
	//	printf("%d %d\n",sum,maxt);
		if(tot>=10000) solve();
		else solve2();
	}
	return 0;
}

