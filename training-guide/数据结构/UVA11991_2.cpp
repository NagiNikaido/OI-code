#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

map< int,vector<int> > hsh;
int n,m;

int main()
{
	while(scanf("%d%d",&n,&m)!=EOF){
		hsh.clear();
		for(int i=1;i<=n;i++){
			int x;scanf("%d",&x);
			hsh[x].push_back(i);
		}
		for(int i=1;i<=m;i++){
			int u,v;scanf("%d%d",&u,&v);
			if(hsh[v].size()>=u) printf("%d\n",hsh[v][u-1]);
			else puts("0");
		}
	}
	return 0;
}
