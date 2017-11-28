
#include <stdio.h>
#include <string.h>
typedef int bool;
#define false 0
#define true !false
//系统中所有进程数量
#define PROCESSES_NUMBER	5
typedef struct {
	int	A;
	int	B;
	int	C;
}RESOURCE;

//最大需求矩阵
RESOURCE Max[PROCESSES_NUMBER] =
{
	{7,5,3},
	{3,2,2},
	{9,0,2},
	{2,2,2},
	{4,3,3}
};

//已分配资源数矩阵
RESOURCE Allocation[PROCESSES_NUMBER] =
{
	{0,1,0},
	{2,0,0},
	{3,0,2},
	{2,1,1},
	{0,0,2}
};

//需求矩阵
RESOURCE Need[PROCESSES_NUMBER] =
{
	{7,4,3},
	{1,2,2},
	{6,0,0},
	{0,1,1},
	{4,3,1}
};

//可用资源向量
RESOURCE Available = {3,3,2};

int safe[PROCESSES_NUMBER];
int already_finish[PROCESSES_NUMBER]={false,false,false,false,false}; //标记进程是否完成
//试探分配
void ProbeAlloc(int process,RESOURCE *res)
{
	Available.A -= res->A;
	Available.B -= res->B;
	Available.C -= res->C;

	Allocation[process].A += res->A;
	Allocation[process].B += res->B;
	Allocation[process].C += res->C;

	Need[process].A -= res->A;
	Need[process].B -= res->B;
	Need[process].C -= res->C;
}

//若试探分配后进入不安全状态，将分配回滚
void RollBack(int process,RESOURCE *res)
{
	Available.A += res->A;
	Available.B += res->B;
	Available.C += res->C;

	Allocation[process].A -= res->A;
	Allocation[process].B -= res->B;
	Allocation[process].C -= res->C;

	Need[process].A += res->A;
	Need[process].B += res->B;
	Need[process].C += res->C;
}

//安全性检查
bool SafeCheck(void)
{
	RESOURCE	Work = Available;
	bool		Finish[PROCESSES_NUMBER] = {false,false,false,false,false};
	int		i;
	int		j = 0;
	//for(i=0;i<=PROCESSES_NUMBER;i++)
    //    if(already_finish[i] == true)
    //        Finish[i] = true;

	for (i = 0; i <= PROCESSES_NUMBER-1; i++)
	{
		//是否已检查过
		if(Finish[i] == false)
		{
			//是否有足够的资源分配给该进程
			if(Need[i].A <= Work.A && Need[i].B <= Work.B && Need[i].C <= Work.C)
			{
				//有则使其执行完成，并将已分配给该进程的资源全部回收
				Work.A += Allocation[i].A;
				Work.B += Allocation[i].B;
				Work.C += Allocation[i].C;
				Finish[i] = true;
				safe[j++] = i;
				i = -1;				//重新进行遍历
			}
		}
	}

	//如果所有进程的Finish向量都为true则处于安全状态，否则为不安全状态
	for (i = 0; i < PROCESSES_NUMBER; i++)
	{
		if (Finish[i] == false)
		{
			return false;
		}
	}
	return true;
}

//资源分配请求
bool request(int process,RESOURCE *res)
{
	//request向量需小于Need矩阵中对应的向量
	if(res->A <= Need[process].A && res->B <= Need[process].B && res->C <= Need[process].C)
	{
		//request向量需小于Available向量
		if(res->A <= Available.A && res->B <= Available.B && res->C <= Available.C)
		{
			//试探分配
			ProbeAlloc(process,res);

			//如果安全检查成立，则请求成功，否则将分配回滚并返回失败
			if(SafeCheck())
			{
				return true;
			}
			else
			{
				printf("安全性检查失败。原因：系统将进入不安全状态，有可能引起死锁。\n");
				printf("正在回滚...\n");
				RollBack(process,res);
			}
		}
		else
		{
			printf("安全性检查失败。原因：请求向量大于可利用资源向量。\n");
		}
	}
	else
	{
		printf("安全性检查失败。原因：请求向量大于需求向量。\n");
	}
	return false;
}

//输出资源分配表
void PrintTable()
{
	printf("\t\t\t*********资源分配表*********\n");
	printf("Process       Max          Allocation          Need          Available\n");
	printf("          A    B    C     A    B    C       A    B    C      A    B    C\n");
	printf("  P0      %d    %d    %d     %d    %d    %d       %d    %d    %d      %d    %d    %d\n",Max[0].A,Max[0].B,Max[0].C,Allocation[0].A,Allocation[0].B,Allocation[0].C,Need[0].A,\
                            Need[0].B,Need[0].C,Available.A,Available.B,Available.C);
	printf("  P1      %d    %d    %d     %d    %d    %d       %d    %d    %d\n",Max[1].A,Max[1].B,Max[1].C,Allocation[1].A,Allocation[1].B,Allocation[1].C,Need[1].A,Need[1].B,Need[1].C);
	printf("  P2      %d    %d    %d     %d    %d    %d       %d    %d    %d\n",Max[2].A,Max[2].B,Max[2].C,Allocation[2].A,Allocation[2].B,Allocation[2].C,Need[2].A,Need[2].B,Need[2].C);
	printf("  P3      %d    %d    %d     %d    %d    %d       %d    %d    %d\n",Max[3].A,Max[3].B,Max[3].C,Allocation[3].A,Allocation[3].B,Allocation[3].C,Need[3].A,Need[3].B,Need[3].C);
	printf("  P4      %d    %d    %d     %d    %d    %d       %d    %d    %d\n",Max[4].A,Max[4].B,Max[4].C,Allocation[4].A,Allocation[4].B,Allocation[4].C,Need[4].A,Need[4].B,Need[4].C);
	printf("\n");
}

void Changetable(int process)
{
    already_finish[process]=true;
    Available.A += Allocation[process].A;
    Available.B += Allocation[process].B;
    Available.C += Allocation[process].C;
    Allocation[process].A=Allocation[process].B=Allocation[process].C=0;
    printf("进程P%d顺利完成并成功释放资源\n",process);

    return ;
}

int main(void)
{
	int	ch;
    int i;
	printf("先检查初始状态是否安全。\n");
	if (SafeCheck())
	{
		printf("系统处于安全状态。\n");
		printf("安全序列是{P%d,P%d,P%d,P%d,P%d}。\n",safe[0],safe[1],safe[2],safe[3],safe[4]);
	}
	else
	{
		printf("系统处于不安全状态。程序将退出...\n");
        printf("执行完毕。");
        return 0;
	}

	do
	{
		int process;
		RESOURCE res;
		PrintTable();
		printf("请依次输入请求分配的进程和对三类资源的请求数量：");
		scanf("%d%d%d%d",&process,&res.A,&res.B,&res.C);
		if (request(process,&res))
		{
            if(Need[process].A==0 && Need[process].B==0  && Need[process].C==0)         //如果分配矩阵等于需求矩阵，需要进行变化
                Changetable(process);
            SafeCheck();
            printf("系统处于安全状态。\n");
            printf("安全序列是{");
            for(i=0;i<PROCESSES_NUMBER;i++)
                if(already_finish[safe[i]] == false)
                    printf("P%d,",safe[i]);
            printf("}   ");

            printf("已完成进程是{");
            for(i=0;i<PROCESSES_NUMBER;i++)
                if(already_finish[i]==true)
                    printf("P%d,",i);
            printf("}\n");
		}
		else
		{
			printf("分配失败。\n");
		}
		printf("是否继续分配？(Y/N):");
		fflush(stdin);
		ch = getchar();
	} while (ch == 'Y' || ch == 'y');

	printf("执行完毕。");
	return 0;
}
