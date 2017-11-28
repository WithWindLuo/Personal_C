#include<stdio.h>
#include<stdlib.h>

void Matrix_Mul(int a[3][3],int b[3][3],int c[3][3])
{
    int i,j,k;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            c[i][j]=0;
            for(k=0;k<3;k++)
            {
                c[i][j]+=a[i][k]*b[k][j];
            }
        }
    }
    return ;
}

void Matrix_exp(int a[3][3],int b[3][3],int exp)
{
    int i,j,k,n,p,q;
    int c[3][3];
    for(p=0;p<3;p++)
        for(q=0;q<3;q++)
                b[p][q]=a[p][q];
    for(n=2;n<=exp;n++)
    {
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                c[i][j]=0;
                for(k=0;k<3;k++)
                    c[i][j]+=b[i][k]*a[k][j];
            }
        }
        for(p=0;p<3;p++)
            for(q=0;q<3;q++)
                b[p][q]=c[p][q];
    }

    return ;
}

int main(void)
{
    int x[3][3],y[3][3];
    int i,j;
    printf("Please enter matrix X:\n");
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            scanf("%d",*x+i*3+j);
    Matrix_exp(x,y,10);
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
            printf("%5d ",*(*y+i*3+j));
        putchar('\n');
    }
    return 0;
}
