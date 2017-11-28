#include <stdio.h>
#include <string.h>
#define n 20
struct fcfs
{
	char id[10];            //进程名
	int atime;         //进程到达时间
	int runtime;       //进程运行时间
	int ftime;         //进程完成时间
}f[n];
int main(void)
{
	int amount,i,j,l;
	char k[10];
	struct  fcfs f[n];
	printf("input a number:\n");
	scanf("%d",&amount);
	for(i=0;i<amount;i++)
	{
		printf("请输入进程名，进程到达时间，进程运行时间:\n");
		scanf("%s %d %d",&f[i].id, &f[i].atime, &f[i].runtime);
	}
	for(i=0;i<amount;i++) //按进程到达时间的先后排序
	{                               //如果两个进程同时到达，按在屏幕先输入的先运行
		for(j=0;j<amount-i-1;j++)
		{
			if(f[j].atime>f[j+1].atime)
			{
				l=f[j].atime;
				f[j].atime=f[j+1].atime;
				f[j+1].atime=l;

                l=f[j].runtime;
				f[j].runtime=f[j+1].runtime;
				f[j+1].runtime=l;

				strcpy(k,f[j].id);
				strcpy(f[j].id,f[j+1].id);
				strcpy(f[j+1].id,k);
			}
		}
	}
	for(i=0;i<amount;i++)
	{
		f[i].ftime=f[i].atime+f[i].runtime;
		printf("进程%s从%d开始,在%d之前结束\n",f[i].id,f[i].atime,f[i].ftime);
		f[i+1].atime=f[i].ftime;
	}
	return 0;
}
