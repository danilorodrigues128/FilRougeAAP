#include <assert.h>

//#define CLEAR2CONTINUE
#include "traces.h" 

//#define DEBUG
#include "check.h"

#include "elt.h"
#include "list.h"

static T_nodeList * newNode(T_elt e); 

T_nodeList * addNode (T_elt e, T_nodeList * n)
{
	T_nodeList * pNode; 
	pNode = newNode(e); 
	pNode->pNext = n; 
	return pNode;
}

static T_nodeList * newNode(T_elt e)
{
	T_nodeList * pNode; 
	CHECK_IF(pNode = malloc(sizeof(T_nodeList)), NULL, "malloc allocateNode"); 
	pNode->data = e; 
	pNode->pNext = NULL;

	return pNode;
}

void showList(T_list l) {
	while(l != NULL)
	{
		printf("%s ", toString(l->data));
		l = l->pNext; 
	}
}

void freeList(T_list l)
{
	assert(l != NULL); 
	T_nodeList * pAux; 
	
	while(l != NULL)
	{
		printf("Libération de %s\n", toString(l->data));
		pAux = l->pNext; 
		free(l); 
		l = pAux; 
	}
	printf("NULL");
}

T_elt getFirstElt(T_list l) 
{
	return l->data; 
}

