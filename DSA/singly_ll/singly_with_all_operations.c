#include <stdio.h>
#include <stdlib.h>

struct node 
{
	int data;
	struct node* next;
};


typedef struct node Node;

Node * Head =NULL;

void create_node(int data)
{
	Node * new,  *temp;
	new = malloc(sizeof(Node));
	new->data = data;
	new->next = NULL;

	if(Head == NULL)
	{
		Head = new;
		return;
	}else {
		temp = Head;
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
	return;
}

void print_list()
{
	Node * temp = Head;
	while(temp != NULL)
	{
		printf(" %d\t",temp->data);
		temp =  temp->next;
	}
	printf("\n");
	return;
}

void reverse()
{
	Node *temp, *next, *prev;
	next = prev = NULL;
	temp = Head;

	while(temp != NULL)
	{
		next =  temp->next;
		temp->next = prev;
		prev = temp;
		temp = next;
	}
	Head = prev;
	return;
}

void loop_check()
{
	Node * fast, *slow;
	fast = slow = Head;

	while(fast != NULL &&  fast->next!= NULL)
	{
		fast = fast->next->next;
		slow= slow->next;

		if(fast == slow)
		{
			printf("\n loop is there\n");
			return;
		}

	}

	printf("\n loop is not there\n");
	return;
}

void reverse_k(int k)
{
	Node *temp, *next, *prev;

	next = prev = NULL;
	temp = Head;

	while(temp != NULL && k > 0)
	{
		next =  temp->next;
		temp->next = prev;
		prev = temp;
		temp = next;
		k--;
	}
	Head->next = temp;
	Head = prev;
	return;
}

void create_link()
{
	Node * temp,*prev;
	int i =0;
	temp = Head;
	prev = NULL;
	while(i< 2)
	{
		prev = temp;
		temp= temp->next;
		i++;
	}

	temp->next->next = prev;
	return;
}


int main()
{
	create_node(1);
	create_node(2);
	create_node(3);
	create_node(4);
	create_node(5);
	print_list();
	reverse();
	print_list();
	reverse_k(2);	
	print_list();
	create_link();
	printf("\nloop created\n");
	loop_check();
	return 0;
}


