#include<stdio.h>
void fabinoci(int num)
{
    int n1 =0,n2,temp;
    
    n2 =1;    
    printf("%d, ",n1);
    while(n2 < num) {
    printf("%d, ",n2);
    temp = n1;
    n1=n2;
    n2=temp+n2;
    }
}
int main()
{
    int num;
printf("enter the number");
scanf("%d",&num);
fabinoci(num);

}