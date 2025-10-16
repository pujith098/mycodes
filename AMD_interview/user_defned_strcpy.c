#include<stdio.h>

void my_strcpy(const char * source, char * destination)
{
	int i;
	for(i=0;source[i];i++)
	{
		destination[i]=source[i];
	}
	destination[i]='\0';
}

int main()
{
	char *p;
	my_strcpy("pujit", p);
	printf("copied string %s",p);
	return 0;
}

