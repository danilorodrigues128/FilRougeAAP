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
	int deltaH = 0;
	int sizeAVL = heightAVL(*root);
	int comparaison = eltcmp(signature, (*root)->signature);
	if(comparaison == 0 && inList(element, (*root)->mots) != 1)
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

T_avl fileToAVL(char* fileTxt, int* size, int* counter)
{
	FILE* fichier = fopen(fileTxt, "r");
	CHECK_IF(fichier, NULL, "> [ERREUR] Fichier invalide !");
	
	char str[128];
	T_avl avl = NULL;
	
	int size_aux = 0;
	int counter_aux = 0;
	
	while(fgets(str, 128, fichier) != NULL)
	{
		counter_aux++;
	
		size_aux = processWord(str);
	
		T_elt mot = (T_elt) malloc(size_aux * sizeof(char));
		mot = eltdup(str);
		
		insertAVL(&avl, mot, size_aux);
	}
	fclose(fichier);
	
	*size = size_aux;
	*counter = counter_aux;
	
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

int getProfondeur(T_avl root, T_elt element, int size)
{
	element = selectionSort(element, size);
	
	int test, counter=0;
	while(root != NULL)
	{
		test = eltcmp(element,root->signature);
		
		if (test == 0) return counter;
		else if  (test < 0) root = root->left; 
		else root = root->right;
		counter++;
	}
	
	return -1;  
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

void rechercherMots(T_avl avl, int size)
{
	T_elt buffer = (T_elt) calloc(size + 1, sizeof(char));
	printf("\n[Appuyez sur \'q\' pour quitter]\n");
	printf("Mot a chercher : ");
	scanf("%s", buffer);
	
	clock_t debut, fin;

	while(strcmp(buffer, "q"))
	{
		debut = clock();
		T_node* node = searchAVL(avl, buffer, size);
		fin = clock();

		system("clear");
		if(node != NULL)
		{
			printf("Mots présentant la même signature (%s) :\n",toString(node->signature));
			showList(node->mots); printf("\n");
			printf("Profondeur du noeud : %d\n", getProfondeur(avl, buffer, size));
			printf("Temp pour trouver : %ld ms\n", (fin - debut) * 1000/CLOCKS_PER_SEC);
		}
		else
		{
			printf("> [ERREUR] Mot \"%s\" ne pas trouvé\n", buffer);
		}
		
		printf("\n[Appuyez sur \'q\' pour quitter]\n");
		printf("Mot a chercher : ");
		scanf("%s", buffer);
	}

	free(buffer);
}

//-------------

static T_node* newNode(T_elt element, T_elt signature)
{
	T_node* node = (T_node*) malloc(sizeof(T_node));
	
	node->signature = signature;
	node->mots = addNode(element, NULL);
	
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
