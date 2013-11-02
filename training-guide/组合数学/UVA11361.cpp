#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>

using namespace std;

int t,a,b,p;
int g[15][100][100];
int f(int t){
	if(!t) return 1;
	int sum=0;
	int res=0,tmp1=t,tmp2=t,ds=1,cnt=0;
	while(tmp1){
		sum+=tmp1%10;
		tmp1/=10;
	}
	tmp1=t;
	while(tmp1){
		int q=tmp1%10;
		sum-=q;
		tmp2-=q*ds;
		if(cnt==0){
			for(int i=0;i<=q;i++) if((tmp2+i)%p==0 && (sum+i)%p==0) res++;
		}
		else{
			for(int i=0;i<q;i++) res+=g[cnt][(p-(sum+i)%p)%p][(p-(tmp2+i*ds)%p)%p];
		}
		cnt++;ds*=10;tmp1/=10;
	}
	return res;
}
int main()
{
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&a,&b,&p);
		if(p>90 || a>b){puts("0");continue;}
		memset(g,0,sizeof(g));
		g[0][0][0]=1;
		for(int i=0;i<10;i++)
			for(int j=0;j<p;j++)
				for(int k=0;k<p;k++) if(g[i][j][k])
					for(int l=0;l<10;l++)
						g[i+1][(j+l)%p][(k*10+l)%p]+=g[i][j][k];
//		for(int i=0;i<10;i++)
//			for(int j=0;j<p;j++)
//				for(int k=0;k<p;k++)
//					printf("g[%d][%d][%d]=%d\n",i,j,k,g[i][j][k]);
		printf("%d\n",f(b)-f(a-1));
	}
	return 0;
}
