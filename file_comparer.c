/*
 *
 *      file_comparer.c
 *
 *                      By Nagi Nikaido
 *
 ******************************************/
 
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 100000000
char buf1[MAX_LINE_LENGTH],buf2[MAX_LINE_LENGTH];
int cmp(char *a,char *b){
	int la=strlen(a),lb=strlen(b);
	int i;
	if(la<lb) return la+1;
	else if(lb<la) return lb+1;
	for(i=0;i<la;i++) if(a[i]!=b[i]) return i+1;
	return 0;
}
int main(int argc,char **argv)
{
   if(argc!=3){
       puts("Usage:file_comparer filename1 filename2");
   }
   else{
        FILE *f1,*f2;
        int flag1=1,flag2=1,diff_l=0,diff_c=0;
        if((f1=fopen(argv[1],"r"))==NULL){
        	puts("Failed in opening the first file.");
        	return 1;
        }
        if((f2=fopen(argv[2],"r"))==NULL){
			puts("Failed in opening the first file.");
			return 2;
		}
		
		while(1){
			flag1=fscanf(f1,"%[^\n\r]",buf1);
			flag2=fscanf(f2,"%[^\n\r]",buf2);
			if(flag1==EOF || flag2==EOF) break;
			diff_l++;
			if((diff_c=cmp(buf1,buf2))!=0) break;
			flag1=fscanf(f1,"%[\n\r]",buf1);
			flag2=fscanf(f2,"%[\n\r]",buf2);
		}
		if(flag1==EOF && flag2==EOF) puts("FC:Same");
		else {puts("FC:Not Same");printf("Different at (%d,%d)\n",diff_l,diff_c);}
		fclose(f1);
		fclose(f2);
   }
   return 0;
}

