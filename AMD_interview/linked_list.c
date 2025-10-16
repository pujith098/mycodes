#include<stdio.h>
#include<stdlib.h>


typedef struct node Node;

struct node {
	int data;
	Node * next;
};

Node * HEAD =NULL;
void create_node(int data)
{
	Node *new, *temp;
	new=(Node *)malloc(sizeof(Node));
	if(new == NULL)
	{
		printf("malloc failed\n");
		return;
	}
	new->data=data;
	new->next=NULL;
	if(HEAD == NULL)
	{
		HEAD=new;
		return;	
	}
	else {
		temp =HEAD;
		while(temp->next)
		{
			temp= temp->next;
		}
		temp->next = new;
		return;

	}
}

void print_list()
{
	Node *temp;
	temp =HEAD;
	int i=0;
	while(temp)
	{
		printf("%d node - %d",i++,temp->data);
		temp= temp->next;
	}
}

int main()
{
	create_node(4);
	create_node(5);
	create_node(12);
	print_list();
	
	return 0;
}
