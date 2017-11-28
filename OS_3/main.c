#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define PR 4
struct pcb { /* 定义进程控制块PCB */
       char name[10]; //进程名称
       char status; //进程状态
       int prio; //进程优先级
       int ntime; //进程需要的时间
       int rtime; //进程到达时间
       struct pcb* link;// 进程的结构体的指针
}*ready=NULL,*p;

typedef struct pcb PCB;

  //ready等于link
int sort(void) /* 进程进行优先级排列函数*/
{
  PCB *first, *second;
  int insert=0;
  if((ready==NULL)||((p->prio)>(ready->prio))) /*优先级最大者,插入队首*/
  {
    p->link=ready; //把ready插入刚刚申请的后面
    ready=p;
  }
  else /* 进程比较优先级,插入适当的位置中*/
  {
    first=ready;
    second=first->link;
    while(second!=NULL)
    {
      if((p->prio)>(second->prio)) /*若插入进程比当前进程优先数大,*/
      { /*插入到当前进程前面*/
        p->link=second;
        first->link=p;
        second=NULL;
        insert=1;
      }
      else /* 插入进程优先数最低,则插入到队尾*/
      {
        first=first->link;
        second=second->link;
      }
    }
    if(insert==0) first->link=p;
  }
}

int input(void) /* 建立进程控制块函数*/
{
  int i,num;
  /*clrscr();  */   /*清屏*/
  printf("\n 请输入进程数?");
  scanf("%d",&num);
  for(i=0;i<num;i++)
  {
    printf("\n 进程号No.%d:\n",i);
    p=(PCB*)malloc(sizeof(PCB));
    printf("\n 输入进程名:");
    scanf("%s",p->name);
    /*printf("\n 输入进程优先数:");
    scanf("%d",&p->prio); */
    p->prio=PR;
    printf("\n 输入进程运行时间:");
    scanf("%d",&p->ntime);
    printf("\n");
    p->rtime=0;
    p->status='r'; //进程的状态
    p->link=NULL;
    sort(); /* 调用sort函数*/
  }

}


int space(void) //该函数的作用？计算一共有多少个进程
{
  int l=0; PCB* pr=ready;
  while(pr!=NULL)
  {
  l++;
  pr=pr->link;
  }
  return(l);
}


int disp(PCB * pr) /*单个进程显示函数*/
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
  printf("\n ****当前第%d级队列(优先数为%d)的就绪进程有:\n",(PR+1)-prio,prio); /*显示就绪队列状态*/
  printf("\n qname \tstatus\t prio \tndtime\t runtime \n");
  while(pr!=NULL)
  {
    if (pr->prio==prio) disp(pr);
    pr=pr->link;
  }
}

int check(void) /* 显示所有进程状态函数 */
{
  PCB* pr;
  int i;
  printf("\n /\\/\\/\\/\\当前正在运行的进程是:%s",p->name); /*显示当前运行进程*/
   printf("\n qname \tstatus\t prio \tndtime\t runtime \n");
  disp(p); //进行显示进程

  printf("\n 当前就绪队列状态为:\n"); /*显示就绪队列状态*/
  for(i=PR;i>=1;i--)
    printbyprio(i);//显示进程状态
  /*
  while(pr!=NULL)
  {
    disp(pr);
    pr=pr->link;
    }
  */
}


int destroy(void) /*进程撤消函数(进程运行结束,撤消进程)*/
{
  printf("\n 进程 [%s] 已完成.\n",p->name);
  free(p); //释放链表资源
}


int running(void) /* 运行函数。判断是否完成，完成则撤销，否则置就绪状态并插入就绪队列*/
{
  int slice,i;
  slice=1;//3.思考：slice的作用？以及赋值变化的原因？其作用是用来记录需要运行时间的调度算法
  for(i=1;i<((PR+1)-p->prio);i++)
    slice=slice*2;

  for(i=1;i<=slice;i++)
  {
     (p->rtime)++;
     if (p->rtime==p->ntime)
       break;

  }
  if(p->rtime==p->ntime)
      destroy(); /* 调用destroy函数进行释放资源*/
  else
  {
    if(p->prio>1) (p->prio)--;
    p->status='r';
    sort(); /*调用sort函数*/
  }
}
void cteatpdisp(void)
/*显示(运行过程中)增加新进程后,所有就绪队列中的进程*/
{

  int i;

  printf("\n 当增加新进程后,所有就绪队列中的进程(此时无运行进程):\n"); /*显示就绪队列状态*/
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
 printf("运行完毕\n");
  // disp(p);
  destroy();
 }
 else
 {
  (p->prio)++;
  sort();
  printf("正在运行进程%s\n",p->name);

 }


}

int main(void) /*主函数*/
{
  int len,h=0,select;
  char ch;
  input();
  len=space();
  printf("\n*******请选择作业调度算法**********\n");
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
    printf("\n 按任一键继续......");
    ch=getchar();
  }
  printf("\n\n 进程已经完成.\n");
  ch=getchar();
  ch=getchar();
  return 0;
}
