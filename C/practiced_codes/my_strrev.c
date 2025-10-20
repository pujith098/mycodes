#include<stdio.h>
#include<string.h>
void my_strrev(char *p)
{
	int i, j,len=strlen(p);
	char temp;
	for( i=0,j=len-1;i<=j;i++,j--)
	{
		if(p[i] != p[j])
		{
			temp=p[i];
			p[i]=p[j];
			p[j]=temp;
		}		
	}
}
int main()
{
	char *str="myname";
	char arr_str[]="myname";

	printf("%s\n",arr_str);
	//	str[0]='p'; 
	// above statement is not error but its a segmentation fault because above string stored in text segment so, we can access but we cant change it
	my_strrev(arr_str);
	printf("%s\n",arr_str);
	return 0;
}
