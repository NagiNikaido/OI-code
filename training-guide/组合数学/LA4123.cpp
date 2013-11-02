#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

unsigned long long f[1010][1010][2][2];
int inq[1010][1010][2][2];
struct state{
	int a,b,c,d;
	state () : a(0),b(0),c(0),d(0) {}
	state (int _a,int _b,int _c,int _d)
		: a(_a),b(_b),c(_c),d(_d) {}
};
queue<state> q;
int l;

int main()
{
	int cnt=0;
	while(1){
		scanf("%d",&l);
		if(!l) break;
		int Rcnt=(l+4)/2,Ocnt=(l-4)/2;
		memset(f,0,sizeof(f));
		memset(inq,0,sizeof(inq));
		if((l&1) || l<=3) goto OUT_OF_LOOP;
		f[1][0][0][0]=f[0][1][1][1]=1;
		inq[1][0][0][0]=inq[0][1][1][1]=1;
		q.push(state(1,0,0,0));q.push(state(0,1,1,1));
		while(!q.empty()){
			state st=q.front();q.pop();
			if(!st.d){
				if(st.a<Rcnt){
					f[st.a+1][st.b][st.c][0]+=f[st.a][st.b][st.c][st.d];
					if(!inq[st.a+1][st.b][st.c][0]){
						inq[st.a+1][st.b][st.c][0]=1;
						q.push(state(st.a+1,st.b,st.c,0));
					}
				}
				if(st.b<Ocnt){
					f[st.a][st.b+1][st.c][1]+=f[st.a][st.b][st.c][st.d];
					if(!inq[st.a][st.b+1][st.c][1]){
						inq[st.a][st.b+1][st.c][1]=1;
						q.push(state(st.a,st.b+1,st.c,1));
					}
				}
			}
			else{
				if(st.a<Rcnt){
					f[st.a+1][st.b][st.c][0]+=f[st.a][st.b][st.c][st.d];
					if(!inq[st.a+1][st.b][st.c][0]){
						inq[st.a+1][st.b][st.c][0]=1;
						q.push(state(st.a+1,st.b,st.c,0));
					}
				}
			}
		}
		OUT_OF_LOOP:;
		printf("Case %d: %llu\n",++cnt,f[Rcnt][Ocnt][0][0]+f[Rcnt][Ocnt][1][0]+f[Rcnt][Ocnt][0][1]);
	}
	return 0;
}
