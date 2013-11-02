#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

inline int cmp(int x1,int x2,int y1,int y2){
	return x1<x2 || x1==x2 && y1<y2;
}
struct Node{
	long long key;
	int pos,size;
	long long sum,maxl,maxr,maxs;
	int maxs_x,maxs_y,maxl_y,maxr_x;
	Node *lchild,*rchild,*father;
	Node () :key(0),pos(0),size(0),sum(0),maxl(0),maxr(0),maxs(0),
		maxs_x(0),maxs_y(0),maxl_y(0),maxr_x(0),lchild(0),rchild(0),father(0) {}
	Node (long long _key,int _pos) :key(_key),pos(_pos),size(1),sum(_key),maxl(_key),
		maxr(_key),maxs(_key),maxs_x(_pos),maxs_y(_pos),maxl_y(_pos),maxr_x(_pos),
		lchild(0),rchild(0),father(0) {}
	void update(){
		size=1;sum=key;maxs_x=maxs_y=pos;
		maxs=key;
		long long lmaxr=0,rmaxl=0,suml=0,sumr=0;
		int lmaxr_x=pos,rmaxl_y=pos;
		if(lchild){
			size+=lchild->size,sum+=lchild->sum;
			maxl=lchild->maxl;maxl_y=lchild->maxl_y;
			if(lchild->sum+key>maxl) maxl=lchild->sum+key,maxl_y=pos;
			if(key+lchild->maxr>maxs || key+lchild->maxr==maxs
				&& cmp(lchild->maxr_x,maxs_x,pos,maxs_y))
					maxs=key+lchild->maxr,maxs_x=lchild->maxr_x,maxs_y=pos;
			if(lchild->maxs>maxs || lchild->maxs==maxs
				&& cmp(lchild->maxs_x,maxs_x,lchild->maxs_y,maxs_y))
					maxs=lchild->maxs,maxs_x=lchild->maxs_x,maxs_y=lchild->maxs_y;
			lmaxr=lchild->maxr,lmaxr_x=lchild->maxr_x;suml=lchild->sum;
		}
		else maxl=key,maxl_y=pos;
		if(rchild){
			size+=rchild->size,sum+=rchild->sum;
			maxr=rchild->sum+key;maxr_x=pos;
			if(rchild->maxr>maxr) maxr=rchild->maxr,maxr_x=rchild->maxr_x;
			if(key+rchild->maxl>maxs || key+rchild->maxl==maxs
				&& cmp(pos,maxs_x,rchild->maxl_y,maxs_y))
					maxs=key+rchild->maxl,maxs_x=pos,maxs_y=rchild->maxl_y;
			if(rchild->maxs>maxs || rchild->maxs==maxs
				&& cmp(rchild->maxs_x,maxs_x,rchild->maxs_y,maxs_y))
					maxs=rchild->maxs,maxs_x=rchild->maxs_x,maxs_y=rchild->maxs_y;
			rmaxl=rchild->maxl,rmaxl_y=rchild->maxl_y;sumr=rchild->sum;
		}
		else maxr=key,maxr_x=pos;
		if(suml+key+rmaxl>maxl || suml+key+rmaxl==maxl && rmaxl_y<maxl_y)
			maxl=suml+key+rmaxl,maxl_y=rmaxl_y;
		if(sumr+key+lmaxr>maxr || sumr+key+lmaxr==maxr && lmaxr_x<maxr_x)
			maxr=sumr+key+lmaxr,maxr_x=lmaxr_x;
		if(lmaxr+key+rmaxl>maxs || lmaxr+key+rmaxl==maxs
			&& cmp(lmaxr_x,maxs_x,rmaxl_y,maxs_y))
				maxs=lmaxr+rmaxl+key,maxs_x=lmaxr_x,maxs_y=rmaxl_y;
	}
	void zig(){
		Node *t=lchild;
		t->father=father;
		father=t;
		lchild=t->rchild;
		if(lchild) lchild->father=this;
		t->rchild=this;
		if(t->father){
			if(t->father->lchild==this) t->father->lchild=t;
			else t->father->rchild=t;
		}
		update();t->update();
	}
	void zag(){
		Node *t=rchild;
		t->father=father;
		father=t;
		rchild=t->lchild;
		if(rchild) rchild->father=this;
		t->lchild=this;
		if(t->father){
			if(t->father->lchild==this) t->father->lchild=t;
			else t->father->rchild=t;
		}
		update();t->update();
	}
};
struct SplayTree{
	Node *root;
	SplayTree () : root(0) {}
	void __build(Node *(&rt),Node *fa,int l,int r,long long *seq){
		int mid=l+r >> 1;
		rt=new Node(seq[mid],mid);
		rt->father=fa;
		if(l<mid) __build(rt->lchild,rt,l,mid-1,seq);
		if(mid<r) __build(rt->rchild,rt,mid+1,r,seq);
		rt->update();
	}
	void erase(Node *(&rt)){
		if(rt){
			erase(rt->lchild);
			erase(rt->rchild);
			delete rt;rt=0;
		}
	}
	void init(int size,long long *a){
		erase(root);
		if(size) __build(root,0,1,size,a);
	}
	void splay(Node *rt,Node *goal=0){
		if(!rt) return;
		while(rt->father!=goal){
			if(rt->father->father!=goal){
				if(rt->father==rt->father->father->lchild){
					if(rt==rt->father->lchild) rt->father->father->zig(),rt->father->zig();
					else rt->father->zag(),rt->father->zig();
				}
				else{
					if(rt==rt->father->lchild) rt->father->zig(),rt->father->zag();
					else rt->father->father->zag(),rt->father->zag();
				}
			}
			else{
				if(rt==rt->father->lchild) rt->father->zig();
				else rt->father->zag();
			}
		}
		if(!goal) root=rt;
	}
	Node *select(int rank){
		Node *rt=root;
		while(1){
			if(!rt) return 0;
			if(rt->lchild){
				if(rank<=rt->lchild->size) {rt=rt->lchild;continue;}
				rank-=rt->lchild->size;
			}
			if(!(--rank)) return rt;
			rt=rt->rchild;
		}
	}
	Node *getInterval(int l,int r){
		if(l<=1){
			if(r>=root->size) return root;
			else{
				splay(select(r+1));
				return root->lchild;
			}
		}
		else{
			splay(select(l-1));
			if(r>=root->size) return root->rchild;
			else{
				splay(select(r+1),root);
				return root->rchild->lchild;
			}
		}
	}
	void query(int l,int r){
		Node *t=getInterval(l,r);
		printf("%d %d\n",t->maxs_x,t->maxs_y);
	}
}T;
int n,m;
long long a[500010];

int main()
{
	int cnt=0;
	while(scanf("%d%d",&n,&m)!=EOF){
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		T.init(n,a);
		printf("Case %d:\n",++cnt);
		for(int i=1;i<=m;i++){
			int l,r;scanf("%d%d",&l,&r);
			T.query(l,r);
		}
	}
	return 0;
}
