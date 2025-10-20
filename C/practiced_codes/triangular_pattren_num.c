#include<stdio.h>


int main()
{
    int i,j;

int a[5][5]={};

for(i=0,j=i+1;i<5; i++,j++)
{
    a[i][i]=i+1;
    if(i <4 ){
    a[i][j]=j+5;
    a[i][j+1]=j+9;
    }
    if(i<3)
    a[i][j+2]=j+12;
    a[i][j+3]=15;
}
i=0;
j=0;
for(j=0;j<5;j++)
{
    for(i=0;i<5;i++)
        if(i <= j)
            printf("%d ",a[i][j]);
    printf("\n");

}
}


