#include "elt.h" // T_elt 

#ifndef _LIST_H_
#define _LIST_H_

typedef struct node_list {
	T_elt data;
	struct node_list *pNext;
} T_nodeList, * T_list;

T_nodeList * addNode (T_elt e, T_nodeList * n);
void showList(T_list l);
void freeList(T_list l);
T_elt getFirstElt(T_list l);

#endif 


