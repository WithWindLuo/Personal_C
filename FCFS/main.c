#include <stdio.h>
#include <string.h>
#define n 20
struct fcfs
{
	char id[10];            //������
	int atime;         //���̵���ʱ��
	int runtime;       //��������ʱ��
	int ftime;         //�������ʱ��
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
		printf("����������������̵���ʱ�䣬��������ʱ��:\n");
		scanf("%s %d %d",&f[i].id, &f[i].atime, &f[i].runtime);
	}
	for(i=0;i<amount;i++) //�����̵���ʱ����Ⱥ�����
	{                               //�����������ͬʱ���������Ļ�������������
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
		printf("����%s��%d��ʼ,��%d֮ǰ����\n",f[i].id,f[i].atime,f[i].ftime);
		f[i+1].atime=f[i].ftime;
	}
	return 0;
}
