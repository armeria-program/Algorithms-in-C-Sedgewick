#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"item.h"

void merge(item_t *a,int left,int middle,int right);
void merge_sort(item_t *array,int left,int right);
void print_array(item_t *array,int n_elements);

int count_comp=0;

void print_array(item_t *array,int n_elements)
{
	int i;

	for(i=0;i<n_elements;i++){
		print_item(array[i]);
		putchar(' ');
	}
	putchar('\n');
}

void merge(item_t *a,int left,int middle,int right)
{
	int n=right-left+1;
	item_t *aux=malloc(n*sizeof(*aux));
	int i,j,k;
	
	for(k=0,i=left;i<=middle;i++){
		aux[k++]=a[i];
	}
	for(i=right;i>middle;i--){
		aux[k++]=a[i];
	}

	for(i=0,j=n-1,k=left;k<=right;k++){
		if((count_comp++,compare_item(aux[i],aux[j]))<0){
			a[k]=aux[i++];	
		}else{
			a[k]=aux[j--];	
		}
	}

	free(aux);
}

/*
** The implementation of top-down mergesort by splitting the file
** at a random position, rather than exactly in the middle.
*/
void merge_sort(item_t *array,int left,int right)
{
	int n=right-left+1;
	int middle;	

	if(right-left+1<=1){
		return;
	}

	middle=rand()%(n-1)+left;

	merge_sort(array,left,middle);
	merge_sort(array,middle+1,right);
	merge(array,left,middle,right);
}

int main(int argc,char *argv[])
{
	int N=atoi(argv[1]);
	item_t *array=malloc(N*sizeof(*array));
	int i;

	srand((unsigned)time(NULL));

	for(i=0;i<N;i++){
		array[i]=rand()%N;
	}
//	print_array(array,N);

	merge_sort(array,0,N-1);
//	print_array(array,N);
	printf("number of comparisons: %d\n",count_comp);

	free(array);

	return(0);
}
