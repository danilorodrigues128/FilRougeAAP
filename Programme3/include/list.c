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
		pAux = l->pNext; 
		free(l); 
		l = pAux; 
	}
}

unsigned int getSize(const T_list l)
{
	int count = 0;
	T_nodeList* nextNode = l;
	while(nextNode != NULL)
	{
		count++;
		nextNode = nextNode->pNext;
	}
	
	return count;
}

int inList(T_elt e, const T_list l)
{
	T_nodeList* nextNode = l;
	while(nextNode != NULL)
	{
		if(eltcmp(nextNode->data, e) == 0)
		{
			return 1;
		}
		nextNode = nextNode->pNext;
	}
	return 0;
}

