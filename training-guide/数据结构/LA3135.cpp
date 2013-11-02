#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

struct Triple{
	int num,period,last;
	Triple() : num(0),period(0),last(0) {}
	Triple(int _num,int _per,int _last)
		: num(_num),period(_per),last(_last) {}
};
bool operator <(const Triple& a,const Triple &b){
	return a.last>b.last || (a.last==b.last && a.num>b.num);
}
char buf[15];
priority_queue<Triple> q;

int main()
{
	while(1){
		scanf("%s",buf);
		if(strcmp(buf,"#")==0) break;
		int num,per;
		scanf("%d%d",&num,&per);
		q.push(Triple(num,per,per));
	}
	int k;
	scanf("%d",&k);
	for(int i=1;i<=k;i++){
		printf("%d\n",q.top().num);
		Triple tmp=q.top();q.pop();
		//printf("%d %d %d\n",tmp.num,tmp.period,tmp.last);
		q.push(Triple(tmp.num,tmp.period,tmp.last+tmp.period));
	}
	return 0;
}
