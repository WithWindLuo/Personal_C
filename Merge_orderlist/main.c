#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int *base;  //�洢�ռ�Ļ���ַ
    int length; //��ǰ����
}Sqlist;    //������

void mergelist(Sqlist LA,Sqlist LB,Sqlist *LC)
{//��֪˳�������LA��LB��Ԫ�ذ�ֵ�ǵݼ�����
 //�鲢LA��LB�õ��µ�˳�������LC��LC��Ԫ��Ҳ��ֵ�ǵݼ�����
    LC->length=LA.length+LB.length;     //�±���Ϊ���ϲ���������֮��
    LC->base=(int *)malloc(LC->length * sizeof(int)); //Ϊ�±����ռ�
    int *pa,*pb,*pc,*pa_last,*pb_last;
    pa=LA.base;     //ָ��pa��pb�ĳ�ֵ�ֱ�ָ��������ĵ�һ��Ԫ��
    pb=LB.base;
    pc=LC->base;    //ָ��pcָ���±�ĵ�һ��Ԫ��
    pa_last=LA.base+LA.length-1;    //ָ��pa_lastָ��LA�����һ��Ԫ��
    pb_last=LB.base+LB.length-1;    //ָ��pb_laseָ��LB�����һ��Ԫ��
    while((pa<=pa_last) && (pb<=pb_last))   //LA��LB��δ�ﵽ��β
    {//����ժȡ������ֵ��С�Ľ�����LC�����
        if(*pa <= *pb)
            *pc++=*pa++;
        else
            *pc++=*pb++;
    }
    while(pa <= pa_last)
        *pc++=*pa++;    //LB�Ѵﵽ��β�����ν�LA��ʣ��Ԫ�ز���LC�����
    while(pb <= pb_last)
        *pc++=*pb++;    //LA�Ѵﵽ��λ�����ν�LB��ʣ��Ԫ�ز���LC�����
    return ;
}

int main(void)
{
    int i;
    Sqlist LA,LB,LC;
    int a[]={1,3,5,7,9};    //��ʼ����LA
    int b[]={2,4,6,8,10};   //��ʼ����LB
    LA.base=a;
    LA.length=sizeof(a)/sizeof(a[0]);   //����LA����
    LB.base=b;
    LB.length=sizeof(b)/sizeof(b[0]);   //����LB����
    mergelist(LA,LB,&LC);   //�ϲ���LA��LBΪLC
    printf("LA:");          //�����A
    for(i=0;i<=LA.length-1;i++)
        printf("%d ",*(LA.base+i));
    putchar('\n');
    printf("LB:");          //�����B
    for(i=0;i<=LB.length-1;i++)
        printf("%d ",*(LB.base+i));
    putchar('\n');
    printf("LC:");          //�����C
    for(i=0;i<=LC.length-1;i++)
        printf("%d ",*(LC.base+i));
    putchar('\n');
    return 0;
}
