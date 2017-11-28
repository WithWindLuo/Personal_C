
#include <stdio.h>
#include <string.h>
typedef int bool;
#define false 0
#define true !false
//ϵͳ�����н�������
#define PROCESSES_NUMBER	5
typedef struct {
	int	A;
	int	B;
	int	C;
}RESOURCE;

//����������
RESOURCE Max[PROCESSES_NUMBER] =
{
	{7,5,3},
	{3,2,2},
	{9,0,2},
	{2,2,2},
	{4,3,3}
};

//�ѷ�����Դ������
RESOURCE Allocation[PROCESSES_NUMBER] =
{
	{0,1,0},
	{2,0,0},
	{3,0,2},
	{2,1,1},
	{0,0,2}
};

//�������
RESOURCE Need[PROCESSES_NUMBER] =
{
	{7,4,3},
	{1,2,2},
	{6,0,0},
	{0,1,1},
	{4,3,1}
};

//������Դ����
RESOURCE Available = {3,3,2};

int safe[PROCESSES_NUMBER];
int already_finish[PROCESSES_NUMBER]={false,false,false,false,false}; //��ǽ����Ƿ����
//��̽����
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

//����̽�������벻��ȫ״̬��������ع�
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

//��ȫ�Լ��
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
		//�Ƿ��Ѽ���
		if(Finish[i] == false)
		{
			//�Ƿ����㹻����Դ������ý���
			if(Need[i].A <= Work.A && Need[i].B <= Work.B && Need[i].C <= Work.C)
			{
				//����ʹ��ִ����ɣ������ѷ�����ý��̵���Դȫ������
				Work.A += Allocation[i].A;
				Work.B += Allocation[i].B;
				Work.C += Allocation[i].C;
				Finish[i] = true;
				safe[j++] = i;
				i = -1;				//���½��б���
			}
		}
	}

	//������н��̵�Finish������Ϊtrue���ڰ�ȫ״̬������Ϊ����ȫ״̬
	for (i = 0; i < PROCESSES_NUMBER; i++)
	{
		if (Finish[i] == false)
		{
			return false;
		}
	}
	return true;
}

//��Դ��������
bool request(int process,RESOURCE *res)
{
	//request������С��Need�����ж�Ӧ������
	if(res->A <= Need[process].A && res->B <= Need[process].B && res->C <= Need[process].C)
	{
		//request������С��Available����
		if(res->A <= Available.A && res->B <= Available.B && res->C <= Available.C)
		{
			//��̽����
			ProbeAlloc(process,res);

			//�����ȫ��������������ɹ������򽫷���ع�������ʧ��
			if(SafeCheck())
			{
				return true;
			}
			else
			{
				printf("��ȫ�Լ��ʧ�ܡ�ԭ��ϵͳ�����벻��ȫ״̬���п�������������\n");
				printf("���ڻع�...\n");
				RollBack(process,res);
			}
		}
		else
		{
			printf("��ȫ�Լ��ʧ�ܡ�ԭ�������������ڿ�������Դ������\n");
		}
	}
	else
	{
		printf("��ȫ�Լ��ʧ�ܡ�ԭ������������������������\n");
	}
	return false;
}

//�����Դ�����
void PrintTable()
{
	printf("\t\t\t*********��Դ�����*********\n");
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
    printf("����P%d˳����ɲ��ɹ��ͷ���Դ\n",process);

    return ;
}

int main(void)
{
	int	ch;
    int i;
	printf("�ȼ���ʼ״̬�Ƿ�ȫ��\n");
	if (SafeCheck())
	{
		printf("ϵͳ���ڰ�ȫ״̬��\n");
		printf("��ȫ������{P%d,P%d,P%d,P%d,P%d}��\n",safe[0],safe[1],safe[2],safe[3],safe[4]);
	}
	else
	{
		printf("ϵͳ���ڲ���ȫ״̬�������˳�...\n");
        printf("ִ����ϡ�");
        return 0;
	}

	do
	{
		int process;
		RESOURCE res;
		PrintTable();
		printf("�����������������Ľ��̺Ͷ�������Դ������������");
		scanf("%d%d%d%d",&process,&res.A,&res.B,&res.C);
		if (request(process,&res))
		{
            if(Need[process].A==0 && Need[process].B==0  && Need[process].C==0)         //����������������������Ҫ���б仯
                Changetable(process);
            SafeCheck();
            printf("ϵͳ���ڰ�ȫ״̬��\n");
            printf("��ȫ������{");
            for(i=0;i<PROCESSES_NUMBER;i++)
                if(already_finish[safe[i]] == false)
                    printf("P%d,",safe[i]);
            printf("}   ");

            printf("����ɽ�����{");
            for(i=0;i<PROCESSES_NUMBER;i++)
                if(already_finish[i]==true)
                    printf("P%d,",i);
            printf("}\n");
		}
		else
		{
			printf("����ʧ�ܡ�\n");
		}
		printf("�Ƿ�������䣿(Y/N):");
		fflush(stdin);
		ch = getchar();
	} while (ch == 'Y' || ch == 'y');

	printf("ִ����ϡ�");
	return 0;
}
