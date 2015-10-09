#include<stdlib.h>
#include"deque.h"

typedef struct node* link_t;
struct node{
	item_t item;
	link_t prev;
	link_t next;
};

static link_t head,tail;

void dequeInit(int Nmax)
{
	head=tail=NULL;
}

int dequeEmpty(void)
{
	return(head==NULL);
}

void dequePut_begin(item_t item)
{
	link_t x=malloc(sizeof(*x));
	x->item=item;

	if(head==NULL){
		x->prev=x->next=NULL;
		head=tail=x;
		return;		
	}

	x->next=head;
	head->prev=x;
	x->prev=NULL;
	head=x;	
}

void dequePut_end(item_t item)
{
	link_t x=malloc(sizeof(*x));
	x->item=item;

	if(tail==NULL){
		x->prev=x->next=NULL;
		head=tail=x;
		return;		
	}

	x->prev=tail;
	tail->next=x;
	x->next=NULL;
	tail=x;
}	

item_t dequeGet_begin(void)
{
	item_t x=head->item;
	link_t t=head->next;

	if(t==NULL){
		free(head);
		head=tail=NULL;
		return(x);
	}		
	
	t->prev=NULL;
	free(head);
	head=t;

	return(x);
}

item_t dequeGet_end(void)
{
	item_t x=tail->item;
	link_t t=tail->prev;

	if(t==NULL){
		free(tail);
		head=tail=NULL;
		return(x);
	}

	t->next=NULL;
	free(tail);
	tail=t;

	return(x);
}
