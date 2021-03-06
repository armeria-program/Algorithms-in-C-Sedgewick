#include<stdio.h>
#include"item_radix.h"
#include"radix.h"

static int keyword(item_t a);

void swap_item(item_t *a,item_t *b)
{
	item_t t;

	t=*a;
	*a=*b;
	*b=t;
}

void copy_item(item_t *a,item_t *b)
{
	*a=*b;
}

int compare_item(item_t a,item_t b)
{
	return(a-b);
}

int compare_item_digit(item_t a,item_t b,int digit_order)
{
	return(digit(keyword(a),digit_order)-digit(keyword(b),digit_order));
}

void print_item(item_t x)
{
	printf("%d",x);
}

static int keyword(item_t a)
{
	return(a);
}
