#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define PR 4
struct pcb { /* ������̿��ƿ�PCB */
       char name[10]; //��������
       char status; //����״̬
       int prio; //�������ȼ�
       int ntime; //������Ҫ��ʱ��
       int rtime; //���̵���ʱ��
       struct pcb* link;// ���̵Ľṹ���ָ��
}*ready=NULL,*p;

typedef struct pcb PCB;

  //ready����link
int sort(void) /* ���̽������ȼ����к���*/
{
  PCB *first, *second;
  int insert=0;
  if((ready==NULL)||((p->prio)>(ready->prio))) /*���ȼ������,�������*/
  {
    p->link=ready; //��ready����ո�����ĺ���
    ready=p;
  }
  else /* ���̱Ƚ����ȼ�,�����ʵ���λ����*/
  {
    first=ready;
    second=first->link;
    while(second!=NULL)
    {
      if((p->prio)>(second->prio)) /*��������̱ȵ�ǰ������������,*/
      { /*���뵽��ǰ����ǰ��*/
        p->link=second;
        first->link=p;
        second=NULL;
        insert=1;
      }
      else /* ����������������,����뵽��β*/
      {
        first=first->link;
        second=second->link;
      }
    }
    if(insert==0) first->link=p;
  }
}

int input(void) /* �������̿��ƿ麯��*/
{
  int i,num;
  /*clrscr();  */   /*����*/
  printf("\n �����������?");
  scanf("%d",&num);
  for(i=0;i<num;i++)
  {
    printf("\n ���̺�No.%d:\n",i);
    p=(PCB*)malloc(sizeof(PCB));
    printf("\n ���������:");
    scanf("%s",p->name);
    /*printf("\n �������������:");
    scanf("%d",&p->prio); */
    p->prio=PR;
    printf("\n �����������ʱ��:");
    scanf("%d",&p->ntime);
    printf("\n");
    p->rtime=0;
    p->status='r'; //���̵�״̬
    p->link=NULL;
    sort(); /* ����sort����*/
  }

}


int space(void) //�ú��������ã�����һ���ж��ٸ�����
{
  int l=0; PCB* pr=ready;
  while(pr!=NULL)
  {
  l++;
  pr=pr->link;
  }
  return(l);
}


int disp(PCB * pr) /*����������ʾ����*/
{

  printf("|%s\t",pr->name);
  printf("|%c\t",pr->status);
  printf("|%d\t",pr->prio);
  printf("|%d\t",pr->ntime);
  printf("|%d\t",pr->rtime);
  printf("\n");
}

void printbyprio(int prio)
{
  PCB* pr;
  pr=ready;
  printf("\n ****��ǰ��%d������(������Ϊ%d)�ľ���������:\n",(PR+1)-prio,prio); /*��ʾ��������״̬*/
  printf("\n qname \tstatus\t prio \tndtime\t runtime \n");
  while(pr!=NULL)
  {
    if (pr->prio==prio) disp(pr);
    pr=pr->link;
  }
}

int check(void) /* ��ʾ���н���״̬���� */
{
  PCB* pr;
  int i;
  printf("\n /\\/\\/\\/\\��ǰ�������еĽ�����:%s",p->name); /*��ʾ��ǰ���н���*/
   printf("\n qname \tstatus\t prio \tndtime\t runtime \n");
  disp(p); //������ʾ����

  printf("\n ��ǰ��������״̬Ϊ:\n"); /*��ʾ��������״̬*/
  for(i=PR;i>=1;i--)
    printbyprio(i);//��ʾ����״̬
  /*
  while(pr!=NULL)
  {
    disp(pr);
    pr=pr->link;
    }
  */
}


int destroy(void) /*���̳�������(�������н���,��������)*/
{
  printf("\n ���� [%s] �����.\n",p->name);
  free(p); //�ͷ�������Դ
}


int running(void) /* ���к������ж��Ƿ���ɣ���������������þ���״̬�������������*/
{
  int slice,i;
  slice=1;//3.˼����slice�����ã��Լ���ֵ�仯��ԭ����������������¼��Ҫ����ʱ��ĵ����㷨
  for(i=1;i<((PR+1)-p->prio);i++)
    slice=slice*2;

  for(i=1;i<=slice;i++)
  {
     (p->rtime)++;
     if (p->rtime==p->ntime)
       break;

  }
  if(p->rtime==p->ntime)
      destroy(); /* ����destroy���������ͷ���Դ*/
  else
  {
    if(p->prio>1) (p->prio)--;
    p->status='r';
    sort(); /*����sort����*/
  }
}
void cteatpdisp(void)
/*��ʾ(���й�����)�����½��̺�,���о��������еĽ���*/
{

  int i;

  printf("\n �������½��̺�,���о��������еĽ���(��ʱ�����н���):\n"); /*��ʾ��������״̬*/
  for(i=PR;i>=1;i--)
    printbyprio(i);
}
void creatp()
{
     char temp;
     printf("\nCreat one  more process?type Y (yes)");
     scanf("%c",&temp);
     if (temp=='y'||temp=='Y')
     {
        input();
        cteatpdisp();
     }

}

int running1(void)
{
 p->rtime=p->rtime+1;
 if(p->rtime==p->ntime)
 { p->status='C';

 printf("%s",p->name);
 printf("�������\n");
  // disp(p);
  destroy();
 }
 else
 {
  (p->prio)++;
  sort();
  printf("�������н���%s\n",p->name);

 }


}

int main(void) /*������*/
{
  int len,h=0,select;
  char ch;
  input();
  len=space();
  printf("\n*******��ѡ����ҵ�����㷨**********\n");
  scanf("%d\n",&select);
  while((len!=0)&&(ready!=NULL))
  {

    ch=getchar();
    /*getchar();*/
    h++;
    printf("\n The execute number:%d \n",h);
    p=ready;
    ready=p->link;
    p->link=NULL;
    p->status='R';
    check();
    if(select==1)
        running();
    if(select==2)
        running1();
    //running();
    creatp();
    printf("\n ����һ������......");
    ch=getchar();
  }
  printf("\n\n �����Ѿ����.\n");
  ch=getchar();
  ch=getchar();
  return 0;
}
