#ifndef STACK_H
#define STACK_H

#include "avl.h"

typedef struct stackNode
{
	T_node* nodeAddress;
	struct stackNode * pNext;
} T_stackNode, *T_stack;

T_stack addNodeStack(T_stack stack, T_node* nodeAddress);
void printStack(T_stack stack);
int getSizeStack(T_stack stack);

#endif
