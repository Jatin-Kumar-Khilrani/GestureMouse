#include<stdio.h>
#include<stdlib.h>
struct node {
	int data;
	struct node * next;
};

void main()
{
	struct node *head;

	head=(struct node *)malloc(sizeof(struct node));
	head->data=10;
	head->next=NULL;
	printf("%d\n",head->data);
	printf("%d\n",*head);
}
