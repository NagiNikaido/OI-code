#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int r,c,m,i;
	freopen("uva11992.in","w",stdout);
	r=20;c=50000;srand(time(0));
	m=rand() % 20000 +1;
	printf("%d %d %d\n",r,c,m);
	for(i=0;i<m;i++){
		int type,x1,y1,x2,y2,dt;
		type=rand() % 3 +1;
		x1=rand() % 5+1;y1=rand() % 5+1;
		while((x2=x1+rand() %20)>r);
		while((y2=y1+rand() %50000)>c);
		printf("%d %d %d %d %d",type,x1,y1,x2,y2);
		if(type<3) printf(" %d",rand() % 99+1);
		puts("");
	}
	return 0;
}
