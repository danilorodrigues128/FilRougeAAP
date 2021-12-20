#ifndef AVL_H
#define AVL_H

#include "elt.h"
#include <sys/stat.h>
#include "check.h"
#include "list.h"

#define	MAX2(a, b)	    ((a) >= (b) ? (a) : (b))
#define	MIN2(a, b)	    ((a) <= (b) ? (a) : (b))

typedef enum {
    DOUBLE_RIGHT = -2,
    RIGHT = -1,
    BALANCED = 0,
    LEFT = 1,
    DOUBLE_LEFT = 2
} T_bal;

typedef struct T_node
{
	T_elt signature;
	T_list mots;
	
	T_bal balance;
	
	struct T_node* left;
	struct T_node* right;
} T_node, *T_avl;

extern char * outputPath;

int insertAVL(T_node** root, T_elt element, int size);
void printAVL(T_avl root, int indent);
int heightAVL(T_avl root);
int nbNodesAVL(T_avl root);

T_node* searchAVL_rec(T_avl root, T_elt element);
T_node* searchAVL_it(T_avl root, T_elt element, int size);

void createDotAVL(const T_avl root, const char* basename);

#endif
