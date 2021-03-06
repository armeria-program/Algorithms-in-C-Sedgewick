#ifndef DIRLIST_H
#define DIRLIST_H

typedef int item_t;
typedef struct node* link_t;
struct node{
	item_t item;
	link_t next;
}; 

link_t allocNode(item_t);
void freeNode(link_t);
void insertNext(link_t,link_t);
link_t deleteNext(link_t);
link_t Next(link_t);
item_t Item(link_t);

#endif
