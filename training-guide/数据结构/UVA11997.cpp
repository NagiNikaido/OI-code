#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

typedef pair<int,int> PII;

int k;
int a[760][760];
int b[760];

int main()
{
	while(scanf("%d",&k)!=EOF){
		for(int i=1;i<=k;i++){
			for(int j=1;j<=k;j++)
				scanf("%d",&a[i][j]);
			sort(a[i]+1,a[i]+k+1);
		}
		memcpy(a[0],a[1],sizeof(b));
		for(int i=2;i<=k;i++){
			priority_queue< PII,vector<PII>,greater<PII> > q;
			for(int j=1;j<=k;j++) q.push(make_pair(a[i][j]+a[0][1],1));
			for(int j=1;j<=k;j++){
				PII t=q.top();q.pop();
				b[j]=t.first;
				if(t.second<k)
					q.push(make_pair(t.first-a[0][t.second]+a[0][t.second+1],t.second+1));
			}
			memcpy(a[0],b,sizeof(b));
		}
		printf("%d",a[0][1]);
		for(int j=2;j<=k;j++) printf(" %d",a[0][j]);
		printf("\n");
	}
	return 0;
}
