#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MaxN = 100010;
const int MaxM = 17;

int n,q,m;
int a[MaxN];
int left[MaxN],right[MaxN];
int pos[MaxN],num[MaxN];
int cnt[MaxN];
int log2[MaxN];
int maxt[MaxN][MaxM];

void init(){
	memset(left,0,sizeof(left));
	memset(right,0,sizeof(right));
	memset(pos,0,sizeof(pos));
	memset(num,0,sizeof(num));
	memset(cnt,0,sizeof(cnt));
	memset(maxt,0,sizeof(maxt));
}
int query(int l,int r){
	return max(maxt[l][log2[r-l+1]],maxt[r-(1<<log2[r-l+1])+1][log2[r-l+1]]);
}
int main()
{
	log2[0]=-1;
	for(int i=1;i<=100000;i++){
		log2[i]=1+log2[i>>1];
	}
	log2[0]=0;
	while(1){
		init();
		scanf("%d",&n);
		if(!n) break;
		scanf("%d",&q);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		int i=1;
		while(i<=n){
			m++;
			left[m]=right[m]=i;
			while(a[right[m]]==a[left[m]] && right[m]<=n) {
				pos[right[m]]=right[m]-left[m]+1;
				num[right[m]]=m;
				right[m]++;cnt[m]++;
			}
			i=right[m]--;
			maxt[m][0]=cnt[m];
		}
		for(int i=1;i<=log2[m];i++)
			for(int j=1;j+(1<<i)-1<=m;j++)
				maxt[j][i]=max(maxt[j][i-1],maxt[j+(1<<i-1)][i-1]);
		for(int i=1;i<=q;i++){
			int u,v;
			scanf("%d%d",&u,&v);
		//	printf("%d:%d %d\n%d:%d %d\n",u,num[u],pos[u],v,num[v],pos[v]);
			if(num[u]==num[v]) printf("%d\n",pos[v]-pos[u]+1);
			else{
				int t=max(right[num[u]]-u+1,v-left[num[v]]+1);
				if(num[u]<num[v]-1) t=max(t,query(num[u]+1,num[v]-1));
				printf("%d\n",t);
			}
		}
	}
	return 0;
}
