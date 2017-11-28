#include <stdio.h>
#include <stdlib.h>
#define MAX 30
void insertion_sort(int **q,int n);
int main(void)
{
    FILE *fp;
    if( (fp=fopen("D://source.txt","r")) == NULL)
    {
        puts("Error.");
        exit(0);
    }
    int n=0,i;
    int *p=(int*)malloc(sizeof(int)*MAX);
    while( fscanf(fp,"%d",p+n) == 1 )
    {
        n++;
    }
    fclose(fp);
    if( (fp=fopen("D://target.txt","w")) == NULL)
    {
        puts("Error.");
        exit(0);
    }
    insertion_sort(&p,n);
    for(i=0;i<n;i++)
    {
        fprintf(fp,"%d",*(p+i));
        fprintf(fp,"%c",' ');
    }
    fclose(fp);
    for(i=0;i<=n-1;i++)
	{
		printf("%d  ",*(p+i));
	}
    return 0;
}

void insertion_sort(int **q,int k)
{
	int *p=*q;
	int i,temp,n;
	for(i=1;i<=k-1;i++)
	{
		temp=*(p+i);
		n=i-1;
		while(n>=0 && temp<*(p+n))
		{
			*(p+n+1)=*(p+n);
			n--;
		}
		*(p+n+1)=temp;
	}
	return ;
}
