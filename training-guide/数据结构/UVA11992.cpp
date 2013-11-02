#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x7fffffff;

struct Node{
	int l,r;
	int sum,maxt,mint;
	Node *lchild,*rchild;
	int tag_inc,tag_same;
	Node (int _l=0,int _r=0) : l(_l),r(_r),sum(0),maxt(0),mint(0)
		,lchild(0),rchild(0),tag_inc(0),tag_same(-1) {}
	void modify(int type,int dt){
		if(type==1){tag_inc+=dt;sum+=(r-l+1)*dt;maxt+=dt;mint+=dt;}
		else {tag_inc=0;tag_same=dt;sum=(r-l+1)*dt;maxt=mint=dt;}
	}
	void sink(){
		if(tag_same>=0){
			if(lchild) lchild->modify(2,tag_same);
			if(rchild) rchild->modify(2,tag_same);
		}
		if(tag_inc){
			if(lchild) lchild->modify(1,tag_inc);
			if(rchild) rchild->modify(1,tag_inc);
		}
		tag_inc=0;tag_same=-1;
	}
	void update(){
		if(l==r) maxt=mint=sum;
		else{
			maxt=max(lchild->maxt,rchild->maxt);
			mint=min(lchild->mint,rchild->mint);
			sum=lchild->sum+rchild->sum;
		}
	}
};
struct IntervalTree{
	Node *root;
	IntervalTree() : root(0) {}
	void __build(Node *(&rt),int l,int r){
		rt=new Node(l,r);
		if(l<r){
			int mid=l+r >> 1;
			__build(rt->lchild,l,mid);
			__build(rt->rchild,mid+1,r);
		}
	}
	void erase(Node *(&rt)){
		if(rt){
			erase(rt->lchild);
			erase(rt->rchild);
			delete rt;rt=0;
		}
	}
	void init(int size) {erase(root);__build(root,1,size);}
	void __modify(Node *rt,int l,int r,int type,int dt){
		if(l<=rt->l && r>=rt->r) rt->modify(type,dt);
		else{
			int mid=rt->l+rt->r >> 1;
			rt->sink();
			if(l<=mid) __modify(rt->lchild,l,r,type,dt);
			if(r>mid)  __modify(rt->rchild,l,r,type,dt);
			rt->update();
		}
	}
	void modify(int l,int r,int type,int dt) {__modify(root,l,r,type,dt);}
	int __queryMint(Node *rt,int l,int r){
		if(l<=rt->l && r>=rt->r) return rt->mint;
		else{
			int mid=rt->l+rt->r >> 1;
			int mint=INF;
			rt->sink();
			if(l<=mid) mint=min(mint,__queryMint(rt->lchild,l,r));
			if(r>mid)  mint=min(mint,__queryMint(rt->rchild,l,r));
			return mint;
		}
	}
	int __queryMaxt(Node *rt,int l,int r){
		if(l<=rt->l && r>=rt->r) return rt->maxt;
		else{
			int mid=rt->l+rt->r >> 1;
			int maxt=-INF;
			rt->sink();
			if(l<=mid) maxt=max(maxt,__queryMaxt(rt->lchild,l,r));
			if(r>mid)  maxt=max(maxt,__queryMaxt(rt->rchild,l,r));
			return maxt;
		}
	}
	int __querySum(Node *rt,int l,int r){
		if(l<=rt->l && r>=rt->r) return rt->sum;
		else{
			int mid=rt->l+rt->r >> 1;
			int sum=0;
			rt->sink();
			if(l<=mid) sum+=__querySum(rt->lchild,l,r);
			if(r>mid)  sum+=__querySum(rt->rchild,l,r);
			return sum;
		}
	}
	int queryMint(int l,int r) {return __queryMint(root,l,r);}
	int queryMaxt(int l,int r) {return __queryMaxt(root,l,r);}
	int querySum (int l,int r) {return __querySum (root,l,r);}
}matrix[25];
int r,c,m;

int main()
{
	while(scanf("%d%d%d",&r,&c,&m)!=EOF){
		for(int i=1;i<=r;i++) matrix[i].init(c);
		for(int i=1;i<=m;i++){
			int type,x1,y1,x2,y2;
			scanf("%d%d%d%d%d",&type,&x1,&y1,&x2,&y2);
			if(type==1 || type==2){
				int dt;scanf("%d",&dt);
				for(int j=x1;j<=x2;j++) matrix[j].modify(y1,y2,type,dt);
			}
			else{
				int sum=0,mint=INF,maxt=-INF;
				for(int j=x1;j<=x2;j++){
					sum+=matrix[j].querySum(y1,y2);
					mint=min(mint,matrix[j].queryMint(y1,y2));
					maxt=max(maxt,matrix[j].queryMaxt(y1,y2));
				}
				printf("%d %d %d\n",sum,mint,maxt);
			}
		}
	}
	return 0;
}
