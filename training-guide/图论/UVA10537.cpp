#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

#define v_ptr(_T) vector<_T> :: iterator

int m;
long long p;
int S,T;
long long d[60];
vector<int> g[60];
int inq[60];
int flag[60];
queue<int> q;

inline int code(int node){
	return isupper(node) ? node-'A' : node-'a'+26;
}
inline int decode(int c_node){
	return c_node<26 ? c_node+'A' : c_node-26+'a';
}
inline int getv(){
	static char buf[10];
	scanf("%s",buf);
	return code(buf[0]);
}
void init(){
	for(int i=0;i<52;i++) g[i].clear();
	memset(flag,0,sizeof(flag));
}
long long getRemain(int v,long long d){
	if(v>=26) return d-1;
	return d-(d+19)/20;
}
long long getWeight(int u,long long d){
	if(u>=26) return d+1;
	long long res=d+d/20;
	while(getRemain(u,res)<d) res++;
	return res;
}
void spfa(int u,long long a){
	memset(d,0x7f,sizeof(d));
	d[u]=a;inq[u]=1;q.push(u);
	while(!q.empty()){
		int t=q.front();q.pop();inq[t]=0;
		for(v_ptr(int) p=g[t].begin();p!=g[t].end();p++){
			long long c=getWeight(t,d[t]);
			if(c<d[*p]){
				d[*p]=c;
				if(!inq[*p]){
					inq[*p]=1;q.push(*p);
				}
			}
		}
	}
}
int main()
{
	int __case=0;
	while(1){
		scanf("%d",&m);
		if(m<0) break;
		init();
		for(int i=1;i<=m;i++){
			int u,v;
			u=getv();v=getv();
			g[u].push_back(v);
			g[v].push_back(u);
		}
		for(int i=0;i<52;i++) sort(g[i].begin(),g[i].end());
		scanf("%lld",&p);S=getv();T=getv();
		spfa(T,p);
		printf("Case %d:\n%lld\n",++__case,d[S]);
		flag[S]=1;int u=S;putchar(decode(S));
		while(u!=T){
			for(v_ptr(int) p=g[u].begin();p!=g[u].end();p++)
				if(!flag[*p] && getRemain(*p,d[u])==d[*p]){
					printf("-%c",decode(u=*p));
					flag[u]=1;break;
				}
		}
		puts("");
	}
	return 0;
}
