#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int sum[25][50005];
int r,c;

int main()
{
	scanf("%d%d",&r,&c);
	while(1){
		int type,x1,x2,y1,y2,dt;
		if(scanf("%d%d%d%d%d",&type,&x1,&y1,&x2,&y2)==EOF) break;
		if(type<3) scanf("%d",&dt);
		if(type==1) for(int i=x1;i<=x2;i++) for(int j=y1;j<=y2;j++) sum[i][j]+=dt;
		if(type==2) for(int i=x1;i<=x2;i++) for(int j=y1;j<=y2;j++) sum[i][j] =dt;
		if(type==3){
			int ans1=0,ans2=0x7fffffff,ans3=0x80000000;
			for(int i=x1;i<=x2;i++)
				for(int j=y1;j<=y2;j++){
					ans1+=sum[i][j];
					ans2=min(ans2,sum[i][j]);
					ans3=max(ans3,sum[i][j]);
				}
			printf("%d %d %d\n",ans1,ans2,ans3);
		}
	}
	return 0;
}
