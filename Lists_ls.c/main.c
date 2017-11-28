#include<stdio.h>
#include<stdlib.h>
#define Max 100
typedef struct      //���������Ԫ��
{
	int line;//��
	int column;//��
	int number;//������ֵ
}Node;


typedef struct      //����
{
	int Arrline;//��
	int Arrclou;//��
	int ArrNZ;//����Ԫ�ظ���
	Node data[Max];
}SPA;
void Input(SPA *Head);
void Enqueue(SPA *X,int *m,SPA *Y,int *n);
void AddTogether(SPA *A ,SPA *B,SPA *C);
void Print(SPA *C);

int main(void)
{
	SPA *A,*B,*C;
	A=(SPA *)malloc(sizeof(SPA));
	B=(SPA *)malloc(sizeof(SPA));
	C=(SPA *)malloc(sizeof(SPA));
	printf("    ��һ��ϡ�����\n");
	Input(A);
	printf("    �ڶ���ϡ�����\n");
	Input(B);
	AddTogether(A,B,C);
	Print(C);
	return 0;
}
void Input(SPA *Head)
{
	int i;
	printf("����ϡ������������");
	scanf("%d",&Head->Arrline);
	printf("����ϡ������������");
	scanf("%d",&Head->Arrclou);
	printf("�������Ԫ�صĸ�����");
	scanf("%d",&Head->ArrNZ);
	for(i=0;i<Head->ArrNZ;i++)
	{
		printf("����� %d ������Ԫ�ص��кţ�",i+1);
		scanf("%d",&Head->data[i].line);
		printf("����� %d ������Ԫ�ص��кţ�",i+1);
		scanf("%d",&Head->data[i].column);
		printf("����� %d ������Ԫ�ص���ֵ��",i+1);
		scanf("%d",&Head->data[i].number);
	}
}

void Enqueue(SPA *X,int *m,SPA *Y,int *n)       //�������Ԫ�ظ���
{
	X->data[*m].line  =Y->data[*n].line;
    X->data[*m].column=Y->data[*n] .column;
    X->data[*m].number=Y->data[*n].number;
	*m=*m+1;       *n=*n+1;
}

void AddTogether(SPA *A,SPA *B,SPA *C)
{
	int i=0,j=0,k=0;
	for(i=0;i<Max;i++)          //��ʼ������Cȫ��Ϊ0
		C->data[i].number=0;
	C->Arrline=A->Arrline;
	C->Arrclou=A->Arrclou;
	C->ArrNZ=A->ArrNZ+B->ArrNZ;     //97���д���
	i=j=k=0;
	while((i<A->ArrNZ) && (j<B->ArrNZ) )    //i��j��k��¼����A��B��C�ĵ�N������Ԫ��
    {
		if(A->data[i].line < B->data[j].line)// �ҳ���С�к�
			Enqueue(C,&k,A,&i);
		if(A->data[i].line == B->data[j].line)
		{
			if(A->data[i].column > B->data[j].column)
				Enqueue(C,&k,B,&j);
			if(A->data[i].column < B->data[j].column)
				Enqueue(C,&k,A,&i);
			if(A->data[i].column == B->data[j].column)
			{
				Enqueue(C,&k,A,&i);
				C->data[k-1].number+=B->data[j++].number;
			}
		}
		if(A->data[i].line > B->data[j].line)
			Enqueue(C,&k,B,&j);
    }
	while(i < A->ArrNZ)     //B�ķ���Ԫ���ѽ�����ֽ�Aʣ��ķ���Ԫ��һһ����
		Enqueue(C,&k,A,&i);
	while(j < B->ArrNZ)     //A�ķ���Ԫ���ѽ�����ֽ�Bʣ��ķ���Ԫ��һһ����
		Enqueue(C,&k,B,&j);
	for(i=0;i+1<=C->ArrNZ;i++)       //�����ȸ�����1
	{
		if(C->data[i].number==0)        //����A+B��ӦԪ����Ӻ����0��Ԫ��
		{
			for(j=i;j+1<=C->ArrNZ;j++)    //�����ȸ�����1
			{
				C->data[j].line  =C->data[j+1].line;        //ǰ�Ƹ���Ԫ��Ϊ0
				C->data[j].column=C->data[j+1].column;
				C->data[j].number=C->data[j+1].number;
			}
			C->ArrNZ--;         //ȥ��0Ԫ��ArrNZ-1
			i--;                //if�������+1��������-1  �Ѷ�׼λ��
		}
	}

}
void Print(SPA *C)
{
	int i,j,k,d=0,flag; //flag�ж�����Ƿ�Ϊ0
	printf("\n");
	printf("\n����:%d",C->Arrline);
	printf("\n����:%d",C->Arrclou);
	printf("\n����Ԫ�ظ���:%d\n",C->ArrNZ);
	for(i=1;i<=C->Arrline;i++)//��
	{
		for(j=1;j<=C->Arrclou;j++)//��
		{
			flag=0;
			for(k=d;k<C->ArrNZ;k++)
			{
				if( (i==C->data[d].line) && (j==C->data[d].column) )
				{
					printf("%-2d",C->data[d++].number);
					flag=1;
				}
			}
			if(flag==0)
				printf("0 ");//��� ��
		}
		printf("\n");
	}
}
