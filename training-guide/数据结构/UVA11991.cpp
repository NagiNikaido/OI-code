#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int HASHSIZE = 1000010;

struct HashNode{
	int key;
	HashNode *next;
}pool[HASHSIZE],*tail=pool;
struct Hash{
	HashNode *hsh[HASHSIZE];
	void init(){
		memset(hsh,0,sizeof(hsh));
		tail=pool;
	}
	void insert(int t,int key){
		HashNode *p=tail++;
		p->key=key;
		p->next=hsh[t];
		hsh[t]=p;
	}
	int query(int t,int cnt){
		for(HashNode *p=hsh[t];p;p=p->next){
			if(!(--cnt)) return p->key;
		}
		if(cnt) return 0;
	}
}hash;
int a[HASHSIZE];
int n,m;

int main()
{
	while(scanf("%d%d",&n,&m)!=EOF){
		hash.init();
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=n;i>=1;i--) hash.insert(a[i],i);
		for(int i=1;i<=m;i++){
			int u,v;scanf("%d%d",&u,&v);
			printf("%d\n",hash.query(v,u));
		}
	}
	return 0;
}
