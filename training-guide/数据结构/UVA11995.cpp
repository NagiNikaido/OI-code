#include <cstdio>
#include <cstring>
#include <stack>
#include <queue>

using namespace std;

stack<int> st;
queue<int> qu;
priority_queue<int> pq;
int n;

void init(){
	while(!st.empty()) st.pop();
	while(!qu.empty()) qu.pop();
	while(!pq.empty()) pq.pop();
}
int main()
{
	while(scanf("%d",&n)!=EOF){
		int flag[3]={1,1,1};init();
		for(int i=1;i<=n;i++){
			int t,x;
			scanf("%d%d",&t,&x);
			if(t==1){
				st.push(x);
				qu.push(x);
				pq.push(x);
			}
			else{
				if(st.empty() || qu.empty() || pq.empty()){
					flag[0]=flag[1]=flag[2]=0;
				}
				else{
					if(st.top()!=x) flag[0]=0; st.pop();
					if(qu.front()!=x) flag[1]=0; qu.pop();
					if(pq.top()!=x) flag[2]=0; pq.pop();
				}
			}
		}
		if(flag[0]+flag[1]+flag[2]==0) puts("impossible");
		else if(flag[0]+flag[1]+flag[2]>=2) puts("not sure");
		else if(flag[0]) puts("stack");
		else if(flag[1]) puts("queue");
		else if(flag[2]) puts("priority queue");
	}
	return 0;
}
