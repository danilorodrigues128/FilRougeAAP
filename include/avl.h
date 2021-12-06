#ifndef AVL_H
#define AVL_H

#include "elt.h"

typedef enum {
    DOUBLE_RIGHT = -2,
    RIGHT = -1,
    BALANCED,
    LEFT,
    DOUBLE_LEFT
} T_bal;

typedef struct T_node
{
	T_elt data;
	T_bal balance;
	
	struct T_node* left;
	struct T_node* right;
} T_node, *T_avl;

extern char * outputPath;

int insertAVL (T_node** root, T_elt element);
void printAVL(T_avl root, int indent);
int heightAVL(T_avl root);
int nbNodesAVL(T_avl root);

T_node* searchAVL_rec(T_avl root, T_elt element);
T_node* searchAVL_it(T_avl root, T_elt element);

void createDotAVL(const T_avl root, const char *basename);

#endif
