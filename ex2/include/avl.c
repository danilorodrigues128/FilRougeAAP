#include "avl.h"

char * outputPath = "."; 

static T_node* newNode(T_elt element, T_elt signature);
static T_node* balanceAVL(T_node* root);
static T_node* rotateLeft(T_node* B);
static T_node* rotateRight(T_node* A);

static T_elt selectionSort(T_elt str, int n);

int insertAVL (T_node** root, T_elt element, int size)
{
	T_elt signature = selectionSort(element, size);

	if((*root) == NULL)
	{
		(*root) = newNode(element, signature);
		return 1;
	}
	int deltaH;
	int sizeAVL = heightAVL(*root);
	int comparaison = eltcmp(element, (*root)->signature);
	if(comparaison == 0)
	{
		(*root)->mots = addNode(element, (*root)->mots);
	}
	else if(comparaison < 0)
	{
		deltaH = insertAVL(&((*root)->left), element, size);
		(*root)->balance += deltaH;
	}
	else
	{
		deltaH = insertAVL(&((*root)->right), element, size);
		(*root)->balance -= deltaH;
	}
	
	(*root) = balanceAVL(*root);
	
	return (sizeAVL - heightAVL(*root) != 0) ? 1 : 0;
}

void printAVL(T_avl root, int indent)
{
	int i;
	if (root != NULL)
	{
		printAVL(root->right, indent+1);
		for(i=0;i<indent;i++) printf("\t");
		//printf("(%d) %s\n", root->balance, toString(root->data));
		printAVL(root->left, indent+1);
	}
}

int heightAVL(T_avl root)
{
	if (root == NULL) return -1;

	int l = heightAVL(root->left);
	int r = heightAVL(root->right);

	return 1 + ((l >= r) ? l : r); 
}

int nbNodesAVL(T_avl root)
{
	if (root == NULL) return 0;
	
	return 1 + nbNodesAVL(root->left) + nbNodesAVL(root->right);
}

T_node* searchAVL_rec(T_avl root, T_elt element)
{
	if (root == NULL) return NULL;
	
	else {
		int test = eltcmp(element,root->signature); 
		if (test == 0) return root;
		else if (test <= 0) return searchAVL_rec(root->left,element);
		else return searchAVL_rec(root->right,element);
	}
}

T_node* searchAVL_it(T_avl root, T_elt element)
{
	int test;
	while(root != NULL)
	{	
		test = eltcmp(element,root->signature);
		
		if (test == 0) return root;
		else if  (test <= 0) root = root->left; 
		else root = root->right; 
	}

	return NULL;  
}

//-------------

static T_node* newNode(T_elt element, T_elt signature)
{
	T_node* node = (T_node*) malloc(sizeof(T_node));
	
	node->signature = signature;
	
	
	node->balance = BALANCED;
	
	node->left = NULL;
	node->right = NULL;
	
	return node;
}

static T_node* balanceAVL(T_node* root)
{
	if(root->balance == DOUBLE_LEFT)
	{
		if(root->left->balance > 0)
		{
			return rotateRight(root);
		}
		else
		{
			root->left = rotateLeft(root->left);
			return rotateRight(root);
		}
	}
	else if(root->balance == DOUBLE_RIGHT)
	{
		if(root->right->balance > 0)
		{
			root->right = rotateRight(root->right);
			return rotateLeft(root);
		}
		else
		{
			return rotateLeft(root);
		}
	}
	else
	{
		return root;
	}
}

static T_node* rotateLeft(T_node* B)
{
	T_node* A = B->right;	
	
	int a_prime = heightAVL(A->left) - heightAVL(A->right);
	int b_prime = heightAVL(B->left) - heightAVL(B->right);
	
	B->balance = b_prime + 1 - MIN2(0,a_prime);
	A->balance = a_prime + 1 + MAX2(0,B->balance);

	B->right = A->left;
	A->left = B;
	
	return A;
}

static T_node* rotateRight(T_node* A)
{
	T_node* B = A->left;

	int a = heightAVL(A->left) - heightAVL(A->right);
	int b = heightAVL(B->left) - heightAVL(B->right);

	A->balance = a - 1 - MAX2(0,b);
	B->balance = b - 1 + MIN2(0,A->balance);
	
	A->left = B->right;
	B->right = A;
	
	return B;
}

static T_elt selectionSort(T_elt str, int n)
{
	int i, j;
	char aux;
	T_elt sig = eltdup(str);
	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (sig[i] > sig[j])
			{
				aux = sig[i];
				sig[i] = sig[j];
				sig[j] = aux;
			}
		}
	}

	return sig;
}
