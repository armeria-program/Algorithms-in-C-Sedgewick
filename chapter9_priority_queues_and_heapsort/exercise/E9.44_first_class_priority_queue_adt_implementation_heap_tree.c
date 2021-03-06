/*
** This implementation for the first class priority queue ADT interface, which includes
** insert, delete the maximum, change prioriry, delete, and join operations, uses
** heap-ordered trees with explicit links. Because the client has handles into
** the data structure, you should exchange the nodes themselves instead of
** the information fields.
*/
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"pqueue_full.h"
#include"item.h"

struct PQUEUE_NODE{
	item_t item;
	pqueue_link_t parent;
	pqueue_link_t left;
	pqueue_link_t right;
};
struct PQUEUE{
	pqueue_link_t root;
	pqueue_link_t end;
};

static void do_pqueue_print(pqueue_link_t r);
static void heapify_bottom_up(pqueue_t pq,pqueue_link_t x);
static void heapify_top_down(pqueue_t pq,pqueue_link_t x);
static void swap_node(pqueue_t pq,pqueue_link_t a,pqueue_link_t b);

pqueue_t pqueue_init(int Nmax)
{
	pqueue_t pq;

	pq=malloc(sizeof(*pq));
	pq->root=pq->end=NULL;

	return(pq);
}

int pqueue_empty(pqueue_t pq)
{
	return(pq->root==NULL);
}

pqueue_link_t pqueue_insert(pqueue_t pq,item_t item)
{
	pqueue_link_t new;
	pqueue_link_t x;

	new=malloc(sizeof(*new));
	copy_item(&(new->item),&item);
	new->parent=new;
	new->left=NULL;
	new->right=NULL;

	if(pq->root==NULL){
		pq->root=pq->end=new;
		return(new);
	}

	if(pq->end==pq->root){
		pq->end->left=new;
		new->parent=pq->root;
		pq->end=new;

		heapify_bottom_up(pq,pq->end);

		return(new);
	}

	if(pq->end->parent->left==pq->end){
		pq->end->parent->right=new;
		new->parent=pq->end->parent;
		pq->end=new;

		heapify_bottom_up(pq,pq->end);

		return(new);
	}

	if(pq->end->parent->right==pq->end){
		for(x=pq->end;x->parent->right==x;x=x->parent)
			;
		if(x!=pq->root){
			x=x->parent->right;
		}
		for(;x->left!=NULL;x=x->left)
			;
	
		x->left=new;
		new->parent=x;
		pq->end=new;

		heapify_bottom_up(pq,pq->end);

		return(new);
	}
}

item_t pqueue_del_max(pqueue_t pq)
{
	item_t max_item;
	pqueue_link_t t,x;

	assert(!pqueue_empty(pq));

	copy_item(&max_item,&(pq->root->item));

	if(pq->end==pq->root){
		free(pq->root);
		pq->root=pq->end=NULL;

		return(max_item);
	}

	if(pq->end->parent->right==pq->end){
		swap_node(pq,pq->end,pq->root);

		t=pq->end;
		pq->end->parent->right=NULL;
		pq->end=pq->end->parent->left;
		free(t);

		heapify_top_down(pq,pq->root);
		return(max_item);
	}

	if(pq->end->parent->left==pq->end){
		swap_node(pq,pq->end,pq->root);

		t=pq->end;
		pq->end->parent->left=NULL;
		x=pq->end->parent;
		free(t);

		for(;x->parent->left==x;x=x->parent)
			;
		if(x!=pq->root){
			x=x->parent->left;
		}
		for(;x->right!=NULL;x=x->right)
			;
		pq->end=x;
	
		heapify_top_down(pq,pq->root);

		return(max_item);
	}
}

// pqueue_change untested
void pqueue_change(pqueue_t pq,pqueue_link_t node,item_t new_item)
{
	copy_item(&(node->item),&new_item);

	heapify_top_down(pq,node);
	heapify_bottem_up(pq,node);
}

void pqueue_delete(pqueue_t pq,pqueue_link_t node)
{
	pqueue_link_t t,x,y;

	y=pq->end;
	swap_node(pq,node,pq->end);

	if(pq->end==pq->root){
		free(pq->root);
		pq->root=pq->end=NULL;

		return;
	}

	if(pq->end->parent->right==pq->end){
		t=pq->end;
		pq->end->parent->right=NULL;
		pq->end=pq->end->parent->left;
		free(t);

		heapify_top_down(pq,y);

		return;
	}

	if(pq->end->parent->left==pq->end){
		t=pq->end;
		pq->end->parent->left=NULL;
		x=pq->end->parent;
		free(t);

		for(;x->parent->left==x;x=x->parent)
			;
		if(x!=pq->root){
			x=x->parent->left;
		}
		for(;x->right!=NULL;x=x->right)
			;
		pq->end=x;

		heapify_top_down(pq,y);

		return;
	}
}

/*
** In the pqueue_join function, we just copy the information fileds from
** pq2 to pq1, rather than move the nodes. In the join process, we destroy
** priority queue pq2.
*/
pqueue_t pqueue_join(pqueue_t pq1,pqueue_t pq2)
{
	item_t t;

	while(!pqueue_empty(pq2)){
		t=pqueue_del_max(pq2);
		pqueue_insert(pq1,t);
	}

	free(pq2);

	return(pq1);
}

void pqueue_print(pqueue_t pq)
{
	do_pqueue_print(pq->root);
	putchar('\n');
}

static void do_pqueue_print(pqueue_link_t r)
{
	if(r==NULL){
		return;
	}

	print_item(r->item);
	putchar(' ');

	do_pqueue_print(r->left);
	do_pqueue_print(r->right);
}

static void heapify_bottom_up(pqueue_t pq,pqueue_link_t x)
{
	pqueue_link_t t;

	t=x;
	while(t!=pq->root){
		if(compare_item(t->item,t->parent->item)<=0){
			break;
		}
	
		swap_node(pq,t,t->parent);
	}
}

static void heapify_top_down(pqueue_t pq,pqueue_link_t x)
{
	pqueue_link_t current,next;

	current=x;
	while(current->left!=NULL || current->right!=NULL){
		next=current->left;
		if(current->right!=NULL && compare_item(current->right->item,next->item)>0){
			next=current->right;
		}

		if(compare_item(current->item,next->item)>=0){
			break;
		}
		swap_node(pq,current,next);
	}
}

/*
** The swap_node function swaps the positions pointed by a and b in the heap
** tree, with the nodes pointed by a and b unchanged (that means pointers a
** and b will move as the nodes move). In this process, the root pointer and
** end pointer maintains their properties, which means they still point to
** the root and end of the heap tree and they won't move as the nodes move.
*/
static void swap_node(pqueue_t pq,pqueue_link_t a,pqueue_link_t b)
{
	pqueue_link_t t;

	t=malloc(sizeof(*t));

	if(a==pq->end || b==pq->end){
		if(a==pq->end){
			pq->end=b;
		}else{
			pq->end=a;
		}
	}

	if(a==pq->root){
		t->left=a->left;
		t->right=a->right;
		t->parent=t;

		if(a->left!=NULL){
			a->left->parent=t;
		}
		if(a->right!=NULL){
			a->right->parent=t;
		}
		pq->root=t;


		a->left=b->left;
		a->right=b->right;
		a->parent=b->parent;
	
		if(b->left!=NULL){
			b->left->parent=a;
		}
		if(b->right!=NULL){
			b->right->parent=a;
		}
		if(b->parent->left==b){
			b->parent->left=a;
		}else{
			b->parent->right=a;
		}


		b->left=t->left;
		b->right=t->right;
		b->parent=b;

		if(t->left!=NULL){
			t->left->parent=b;
		}
		if(t->right!=NULL){
			t->right->parent=b;
		}
		pq->root=b;

		free(t);					
		return;	
	}

	if(b==pq->root){
		t->left=b->left;
		t->right=b->right;
		t->parent=t;

		if(b->left!=NULL){
			b->left->parent=t;
		}
		if(b->right!=NULL){
			b->right->parent=t;
		}
		pq->root=t;


		b->left=a->left;
		b->right=a->right;
		b->parent=a->parent;
	
		if(a->left!=NULL){
			a->left->parent=b;
		}
		if(a->right!=NULL){
			a->right->parent=b;
		}
		if(a->parent->left==a){
			a->parent->left=b;
		}else{
			a->parent->right=b;
		}


		a->left=t->left;
		a->right=t->right;
		a->parent=a;

		if(t->left!=NULL){
			t->left->parent=a;
		}
		if(t->right!=NULL){
			t->right->parent=a;
		}
		pq->root=a;


		free(t);

		return;	
	}

	t->left=a->left;
	t->right=a->right;
	t->parent=a->parent;

	if(a->left!=NULL){
		a->left->parent=t;
	}
	if(a->right!=NULL){
		a->right->parent=t;
	}
	if(a->parent->left==a){
		a->parent->left=t;
	}else{
		a->parent->right=t;
	}


	a->left=b->left;
	a->right=b->right;
	a->parent=b->parent;

	if(b->left!=NULL){
		b->left->parent=a;
	}
	if(b->right!=NULL){
		b->right->parent=a;
	}
	if(b->parent->left==b){
		b->parent->left=a;
	}else{
		b->parent->right=a;
	}


	b->left=t->left;
	b->right=t->right;
	b->parent=t->parent;

	if(t->left!=NULL){
		t->left->parent=b;
	}
	if(t->right!=NULL){
		t->right->parent=b;
	}
	if(t->parent->left==t){
		t->parent->left=b;
	}else{
		t->parent->right=b;
	}

	free(t);	
}
