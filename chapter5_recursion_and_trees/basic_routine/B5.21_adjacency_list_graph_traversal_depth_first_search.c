#include<stdio.h>
#include"dirlist.h"

#define V 8

link_t adj[V];
int visited[V]={0};

void visit(int vertex)
{
	printf("%d ",vertex);
}

void traverse(int k,void (*visit)(int))
{
	link_t x;
	
	visit(k);	
	visited[k]=1;
	for(x=Next(adj[k]);x!=NULL;x=Next(x))
		if(visited[Item(x)]==0)
			traverse(Item(x),visit);
}

void print_list(link_t head[])
{
	link_t x;
	int i;

	for(i=0;i<V;i++){
		printf("%d:",Item(head[i]));
		for(x=Next(head[i]);x!=NULL;x=Next(x))
			printf("%d ",Item(x));
		putchar('\n');
	}
}

int main(void)
{
	link_t t;
	int i,j,start=0;
	FILE *fp;

	fp=fopen("adjacency_list_graph_traversal_depth_first_traversal.dat","r");

	for(i=0;i<V;i++){
		adj[i]=allocNode(i);
		adj[i]->next=NULL;
	}

	while(fscanf(fp,"%d%d",&i,&j)==2){
		t=allocNode(j);
		insertNext(adj[i],t);
		t=allocNode(i);
		insertNext(adj[j],t);
	}

	fclose(fp);

	print_list(adj);

	putchar('\n');
	puts("traverse:");
	traverse(start,visit);
	putchar('\n');

	return(0);
}
