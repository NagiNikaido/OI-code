#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int n,m,i,j;
	freopen("LA3938.in","w",stdout);
	srand(time(0));
	while(!(n=rand()));
	while(!(m=rand()));
	printf("%d %d\n",n,m);
	for(i=1;i<=n;i++) printf("%d ",rand()-(RAND_MAX>>1));printf("\n");
	for(i=1;i<=m;i++){
		int l,r;
		l=rand()%n+1;
		r=l+rand()%(n-l+1);
		printf("%d %d\n",l,r);
	}
	return 0;
}
