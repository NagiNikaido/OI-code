#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct Node{
	int key;
	int tag_inc,tag_same;
	int size,mint,maxt,sum;
	Node *lchild,*rchild,*father;
	Node () : key(0),tag_inc(0),tag_same(0),size(0),mint(0),maxt(0)
		,sum(0),lchild(0),rchild(0),father(0) {}
	Node (int _key) : key(_key),tag_inc(0),tag_same(0),size(1),mint(_key),maxt(_key)
		,sum(_key),lchild(0),rchild(0),father(0) {}
	void update(){
		size=1+(lchild ? lchild->size : 0)+(rchild ? rchild->size : 0);
		sum=key+(lchild ? lchild->sum : 0)+(rchild ? rchild->sum : 0);
		mint=maxt=key;
		if(lchild) mint=min(mint,lchild->mint),maxt=max(maxt,lchild->maxt);
		if(rchild) mint=min(mint,rchild->mint),maxt=max(maxt,rchild->maxt);
	}
	void sink(){
		if(tag_same){
			if(lchild) lchild->modify(2,tag_same);
			if(rchild) rchild->modify(2,tag_same);
		}
		if(tag_inc){
			if(lchild) lchild->modify(1,tag_inc);
			if(rchild) rchild->modify(1,tag_inc);
		}
		tag_same=tag_inc=0;
	}
	void modify(int type,int dt){
		if(type==1) tag_inc+=dt,mint+=dt,maxt+=dt,sum+=size*dt,key+=dt;
		else tag_inc=0,tag_same=dt,mint=dt,maxt=dt,sum=size*dt,key=dt;
	}
	void zig(){
		Node *t=lchild;
		lchild=t->rchild;
		if(lchild) lchild->father=this;
		t->rchild=this;
		t->father=father;
		if(t->father){
			if(t->father->lchild==this) t->father->lchild=t;
			else t->father->rchild=t;
		}
		father=t;
		update();t->update();
	}
	void zag(){
		Node *t=rchild;
		rchild=t->lchild;
		if(rchild) rchild->father=this;
		t->lchild=this;
		t->father=father;
		if(t->father){
			if(t->father->lchild==this) t->father->lchild=t;
			else t->father->rchild=t;
		}
		father=t;
		update();t->update();
	}
};
struct SplayTree{
	Node *root;
	SplayTree () : root(0) {}
	void __build(Node *(&rt),Node *fa,int n){
		rt=new Node(0);rt->father=fa;rt->size=n--;
		if(n){
			int k=n>>1;
			if(k) 	__build(rt->lchild,rt,k);
			if(n-k)	__build(rt->rchild,rt,n-k);
		}
	}
	void build(int size){__build(root,0,size);}
	void erase(Node *(&rt)){
		if(rt){
			erase(rt->lchild);
			erase(rt->rchild);
			delete rt;rt=0;
		}
	}
	void init(int size){erase(root);build(size);}
	void splay(Node *rt,Node *goal=0){
		if(!rt) return;rt->sink();
		while(rt->father!=goal){
			if(rt->father->father!=goal){
				rt->father->father->sink();
				rt->father->sink();
				rt->sink();
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
				rt->father->sink();
				rt->sink();
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
			if(rank==1) return rt;
			rank--;rt=rt->rchild;
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
			Node *lt=select(l-1);
			splay(lt);
			if(r>=root->size) return root->rchild;
			else{
				splay(select(r+1),root);
				return root->rchild->lchild;
			}
		}
	}
	void modify(int l,int r,int type,int dt){
		Node *t;(t=getInterval(l,r))->modify(type,dt);
		splay(t);
	}
	void query(int l,int r,int &sum,int &maxt,int &mint){
		Node *t=getInterval(l,r);
		sum+=t->sum,maxt=max(maxt,t->maxt),mint=min(mint,t->mint);
	}
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
				int sum=0,mint=0x7fffffff,maxt=0x80000000;
				for(int j=x1;j<=x2;j++) matrix[j].query(y1,y2,sum,maxt,mint);
				printf("%d %d %d\n",sum,mint,maxt);
			}
		}
	}
	return 0;
}
