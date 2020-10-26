#include<stdio.h>
#include<stdlib.h>

struct node{
	int data;
	struct node *next;
};

struct node * revlist(struct node * head)
{
	struct node *temp2=head;
	struct node *temp=NULL,*forward=NULL;
	//temp=(struct node *)malloc(sizeof(struct node));
	//temp->data=100;
	//temp->next=NULL;
	
	while(head->next!= NULL)
	{
		forward=head->next;
		head->next=temp;
		temp=head;
		head=forward;
	}
	if(head->next==NULL)
	{
		head->next=temp;

		printf("found, data=%d\n",head->data);
		return head;
	}
	
}

void displaylist(struct node * head)
{
	while(head!=NULL)
	{
		printf("%d->",head->data);
		head=head->next;
	}
	printf("\n");
}
struct node *addlist(struct node * head, int number)
{
	struct node *newnode=NULL;
	struct node * temp=head;
	if (head == NULL)
	{
		head=(struct node *)malloc(sizeof(struct node));
		head->data=number;
		head->next=NULL;
		printf("Head not found\n");
		return head;
	}
	while(head->next != NULL)
	{
		head=head->next;
	}
	if(head->next==NULL)
	{
		newnode=(struct node *)malloc(sizeof(struct node));
		newnode->data=number;
		newnode->next=NULL;
		head->next = newnode;
	}
	return temp;
}
void main()
{
	struct node *head;
	int number=0,item=0;
	printf("1 . Create a list -\n");
	printf("2. Display a list -\n");
	printf("3. Reverse a list -\n");
	while(1)
	{
		printf("Enter what you want to do =");
		scanf("%d",&number);
		switch(number)
		{
			case 1:
				printf("Enter the number to create -");
				scanf("%d",&item);
				printf("Item = %d\n",item);
				head=addlist(head,item);
				break;
			case 2:
				displaylist(head);
				break;
			case 3:
				head=revlist(head);
				break;
			default:
				printf("Invalid number \n");
				break;
		}
	}
}
