#ifndef _LIST_H_
#define _LIST_H_

#include <assert.h>
#include "check.h"
#include "elt.h"

typedef struct node_list {
	T_elt data;
	struct node_list *pNext;
} T_nodeList, * T_list;

T_nodeList * addNode (T_elt e, T_nodeList * n);
void showList(T_list l);
void freeList(T_list l);
unsigned int getSize(const T_list l);
int inList(T_elt e, const T_list l);

#endif 


