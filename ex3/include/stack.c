#include "stack.h"

static T_stackNode* newNode(T_node* nodeAddress)
{
	T_stackNode* node = (T_stackNode*) malloc(sizeof(T_stackNode));
	
	node->nodeAddress = nodeAddress;
	node->pNext = NULL;
	
	return node;
}

T_stack addNodeStack(T_stack stack, T_node* nodeAddress)
{
	T_stackNode* nodeStack = newNode(nodeAddress);
	
	if(stack == NULL) return nodeStack;
	
	nodeStack->pNext = stack;
	return nodeStack;
}

void printStack(T_stack stack)
{
	T_stackNode* nextNode = stack;

	while(nextNode != NULL)
	{
		showList(nextNode->nodeAddress->mots);
		printf("\n");
		
		nextNode = nextNode->pNext;
	}
	printf("\n");
}
