#include "avl.h"

char * outputPath = "."; 

static T_node* newNodeAVL(T_elt element, T_elt signature, int nbLetters);
static T_node* balanceAVL(T_node* root);
static T_node* rotateLeft(T_node* B);
static T_node* rotateRight(T_node* A);

static T_elt selectionSort(T_elt str, int n);

int insertAVL(T_node** root, T_elt element, int size)
{
	T_elt signature = selectionSort(element, size);

	if((*root) == NULL)
	{
		(*root) = newNodeAVL(element, signature, size);
		return 1;
	}
	int deltaH = 0;
	int sizeAVL = heightAVL(*root);
	int comparaison = eltcmp(signature, (*root)->signature);
	if(comparaison == 0)
	{
		if(!inList(element, (*root)->mots))
		{
			(*root)->mots = addNode(element, (*root)->mots);
		}
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

T_avl fileToAVL(char* fileTxt)
{
	FILE* fichier = fopen(fileTxt, "r");
	CHECK_IF(fichier, NULL, "> [ERREUR] Fichier invalide !");
	
	char str[128];
	T_avl avl = NULL;
	
	int size = 0;
	
	while(fgets(str, 128, fichier) != NULL)
	{
		size = processWord(str);
	
		T_elt mot = (T_elt) malloc(size * sizeof(char));
		mot = eltdup(str);
		
		insertAVL(&avl, mot, size);
	}
	fclose(fichier);
	
	return avl;
}

void printAVL(T_avl root, int indent)
{
	int i;
	if (root != NULL)
	{
		printAVL(root->right, indent+1);
		for(i=0;i<indent;i++) printf("\t");
		printf("(%d) %s\n", root->balance, toString(root->signature));
		for(i=0;i<indent;i++) printf("\t");
		showList(root->mots);
		printf("\n");
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

void freeAVL(T_avl avl)
{
	if(avl == NULL) return;

	freeAVL(avl->left);
	freeAVL(avl->right);
	
	freeList(avl->mots);
	free(avl);
}

T_node* searchAVL(T_avl root, T_elt element, int size)
{
	element = selectionSort(element, size);
	
	int test;
	while(root != NULL)
	{
		test = eltcmp(element,root->signature);
		
		if (test == 0) return root;
		else if  (test < 0) root = root->left; 
		else root = root->right; 
	}

	return NULL;  
}

//-------------

static T_node* newNodeAVL(T_elt element, T_elt signature, int nbLetters)
{
	T_node* node = (T_node*) malloc(sizeof(T_node));
	
	node->signature = signature;
	node->mots = addNode(element, NULL);
	node->nbLetters = nbLetters;
	
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
