#include<stdio.h>
#include<stdlib.h>
#define Max 100
typedef struct      //矩阵里面的元素
{
	int line;//行
	int column;//列
	int number;//非零数值
}Node;


typedef struct      //矩阵
{
	int Arrline;//行
	int Arrclou;//列
	int ArrNZ;//非零元素个数
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
	printf("    第一个稀疏矩阵：\n");
	Input(A);
	printf("    第二个稀疏矩阵：\n");
	Input(B);
	AddTogether(A,B,C);
	Print(C);
	return 0;
}
void Input(SPA *Head)
{
	int i;
	printf("输入稀疏矩阵的行数：");
	scanf("%d",&Head->Arrline);
	printf("输入稀疏矩阵的列数：");
	scanf("%d",&Head->Arrclou);
	printf("输入非零元素的个数：");
	scanf("%d",&Head->ArrNZ);
	for(i=0;i<Head->ArrNZ;i++)
	{
		printf("输入第 %d 个非零元素的行号：",i+1);
		scanf("%d",&Head->data[i].line);
		printf("输入第 %d 个非零元素的列号：",i+1);
		scanf("%d",&Head->data[i].column);
		printf("输入第 %d 个非零元素的数值：",i+1);
		scanf("%d",&Head->data[i].number);
	}
}

void Enqueue(SPA *X,int *m,SPA *Y,int *n)       //矩阵非零元素复制
{
	X->data[*m].line  =Y->data[*n].line;
    X->data[*m].column=Y->data[*n] .column;
    X->data[*m].number=Y->data[*n].number;
	*m=*m+1;       *n=*n+1;
}

void AddTogether(SPA *A,SPA *B,SPA *C)
{
	int i=0,j=0,k=0;
	for(i=0;i<Max;i++)          //初始化矩阵C全部为0
		C->data[i].number=0;
	C->Arrline=A->Arrline;
	C->Arrclou=A->Arrclou;
	C->ArrNZ=A->ArrNZ+B->ArrNZ;     //97行有处理
	i=j=k=0;
	while((i<A->ArrNZ) && (j<B->ArrNZ) )    //i、j、k记录矩阵A、B、C的第N个非零元素
    {
		if(A->data[i].line < B->data[j].line)// 找出最小行号
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
	while(i < A->ArrNZ)     //B的非零元素已解决，现将A剩余的非零元素一一复制
		Enqueue(C,&k,A,&i);
	while(j < B->ArrNZ)     //A的非零元素已解决，现将B剩余的非零元素一一复制
		Enqueue(C,&k,B,&j);
	for(i=0;i+1<=C->ArrNZ;i++)       //索引比个数少1
	{
		if(C->data[i].number==0)        //处理A+B对应元素相加后等于0的元素
		{
			for(j=i;j+1<=C->ArrNZ;j++)    //索引比个数少1
			{
				C->data[j].line  =C->data[j+1].line;        //前移覆盖元素为0
				C->data[j].column=C->data[j+1].column;
				C->data[j].number=C->data[j+1].number;
			}
			C->ArrNZ--;         //去掉0元，ArrNZ-1
			i--;                //if结束后会+1，所以先-1  已对准位置
		}
	}

}
void Print(SPA *C)
{
	int i,j,k,d=0,flag; //flag判断输出是否为0
	printf("\n");
	printf("\n行数:%d",C->Arrline);
	printf("\n列数:%d",C->Arrclou);
	printf("\n非零元素个数:%d\n",C->ArrNZ);
	for(i=1;i<=C->Arrline;i++)//行
	{
		for(j=1;j<=C->Arrclou;j++)//列
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
				printf("0 ");//输出 零
		}
		printf("\n");
	}
}
