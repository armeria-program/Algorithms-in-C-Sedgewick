/*
** This program generates N random 64-bit keys, and sorts them using the method of
** using LSD radix sort on the first three bytes, then using insertion sort to clean
** up. The choice of byte size that minimizes the total running time will be found.
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"item.h"
#include"radix.h"

void print_array(item_t *array,int n_elements);
void lsd_radixsort(item_t *array,int left,int right);
void insertion_sort(item_t *array,int left,int right);
long long rand_64(void);

int main(int argc,char *argv[])
{
	int N=atoi(argv[1]);
	item_t *array=malloc(N*sizeof(*array));
	int i;
	clock_t c1,c2;

	srand((unsigned)time(NULL));

	printf("R: %d\n",R);

	for(i=0;i<N;i++){
		array[i]=rand_64();
	}
//	print_array(array,N);

	c1=clock();
	lsd_radixsort(array,0,N-1);
	c2=clock();
//	print_array(array,N);
	printf("sorted time: %.5fs\n",(double)(c2-c1)/CLOCKS_PER_SEC);

	return(0);
}

void print_array(item_t *array,int n_elements)
{
	int i;

	for(i=0;i<n_elements;i++){
		print_item(array[i]);
		putchar('\n');
	}
	putchar('\n');
}

/*
** This LSD radix sort implementation uses insertion sort to clean up, because insertion
** sort is effective when the file is almost ordered.
*/
void lsd_radixsort(item_t *array,int left,int right)
{
	int i;
	int w;
	int n=right-left+1;
	int count[R+1];
	item_t *aux;

	if(right-left+1<=1){
		return;
	}


	aux=malloc(n*sizeof(*aux));

	for(w=2;w>=0;w--){
		for(i=0;i<=R;i++){
			count[i]=0;
		}
	
		for(i=left;i<=right;i++){
			count[digit(array[i],w)+1]++;
		}
	
		for(i=1;i<=R;i++){
			count[i]+=count[i-1];
		}


		for(i=left;i<=right;i++){
			copy_item(&aux[count[digit(array[i],w)]++],&array[i]);
		}
	
		for(i=left;i<=right;i++){
			copy_item(&array[i],&aux[i-left]);	
		}
	}

	free(aux);


	insertion_sort(array,left,right);
}

void insertion_sort(item_t *array,int left,int right)
{
	int i,j;
	item_t t;

	for(i=left+1;i<=right;i++){
		if(compare_item(array[i],array[left])<0){
			swap_item(&array[i],&array[left]);
		}
	}

	for(i=left+2;i<=right;i++){
		copy_item(&t,&array[i]);

		for(j=i-1;compare_item(array[j],t)>0;j--){
			copy_item(&array[j+1],&array[j]);
		}

		copy_item(&array[j+1],&t);
	} 
}

/*
** This function generates a random 64-bit integer.
*/
long long rand_64(void)
{
	long long a=rand();
	long long b=rand();

	a=a<<32;

	b=b<<1;
	a+=b;
	a+=rand()%1;

	return(a);
}
