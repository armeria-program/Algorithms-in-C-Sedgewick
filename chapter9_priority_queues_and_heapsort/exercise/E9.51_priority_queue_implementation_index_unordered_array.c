/*
** The implementation for the index-item priority queue ADT, using an
** unordered-array representation.
*/
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"pqueue_index.h"

static int *pq;
static int *qp;
static int N;

extern int compare_index(int index1,int index2);
extern void print_index(int index);
static void swap_index(int a,int b);

void pqueue_init(int Nmax)
{
	pq=malloc(Nmax*sizeof(*pq));
	qp=malloc(Nmax*sizeof(*qp));
	N=0;
}

int pqueue_empty(void)
{
	return(N==0);
}

void pqueue_insert(int index)
{
	pq[N++]=index;
	qp[index]=N-1;
}

int pqueue_del_max(void)
{
	int i,max;

	assert(!pqueue_empty());

	for(max=0,i=1;i<N;i++){
		if(compare_index(pq[i],pq[max])>0){
			max=i;
		}
	}
	swap_index(max,N-1);
	N--;
	
	return(pq[N]);
}

void pqueue_change(int index)
{

}

void pqueue_delete(int index)
{
	int position=qp[index];

	swap_index(position,--N);
}

void pqueue_print(void)
{
	int i;

	for(i=0;i<N;i++){
		print_index(pq[i]);
		putchar(' ');
	}
	putchar('\n');
}

static void swap_index(int a,int b)
{
	int indexa,indexb;

	indexa=pq[a];
	indexb=pq[b];

	pq[a]=indexb;
	pq[b]=indexa;

	qp[indexa]=b;
	qp[indexb]=a;
}
