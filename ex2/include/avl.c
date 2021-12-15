#include "avl.h"

char * outputPath = "."; 

static T_node* newNode(T_elt element);
static T_node* balanceAVL(T_node* root);
static T_node* rotateLeft(T_node* B);
static T_node* rotateRight(T_node* A);

static void genDotAVL(const T_avl root, FILE* basename);

int insertAVL (T_node** root, T_elt element)
{
	T_elt signature = quick_sort(element, size);

	if((*root) == NULL)
	{
		(*root) = newNode(element);
		return 1;
	}
	int deltaH;
	int sizeAVL = heightAVL(*root);
	if(eltcmp(element, (*root)->data) <= 0)
	{
		deltaH = insertAVL(&((*root)->left), element);
		(*root)->balance += deltaH;
	}
	else
	{
		deltaH = insertAVL(&((*root)->right), element);
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
		printf("(%d) %s\n", root->balance, toString(root->data));
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
		int test = eltcmp(element,root->data); 
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
		test = eltcmp(element,root->data);
		
		if (test == 0) return root;
		else if  (test <= 0) root = root->left; 
		else root = root->right; 
	}

	return NULL;  
}

void createDotAVL(const T_avl root, const char* basename)
{
	static char oldBasename[FILENAME_MAX + 1] = "";
	static unsigned int noVersion = 0;

	char DOSSIER_DOT[FILENAME_MAX + 1]; 
	char DOSSIER_PNG[FILENAME_MAX + 1]; 

	char fnameDot [FILENAME_MAX + 1];
	char fnamePng [FILENAME_MAX + 1];
	char	cmdLine [2 * FILENAME_MAX + 20];
	FILE *fp;
	struct stat sb;
	
	if (stat(outputPath, &sb) == 0 && S_ISDIR(sb.st_mode)) {
    } else {
        printf("Création du répertoire %s\n", outputPath);
		mkdir(outputPath, 0777);
    }

	sprintf(DOSSIER_DOT, "%s/img/dot/",outputPath);
	sprintf(DOSSIER_PNG, "%s/img/png/",outputPath);

	if (oldBasename[0] == '\0') {
		mkdir(DOSSIER_DOT,	S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
		mkdir(DOSSIER_PNG,	S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	}

	if (strcmp(oldBasename, basename) != 0) {
		noVersion = 0;
		strcpy(oldBasename, basename); 
	}

	sprintf(fnameDot, "%s%s_v%02u.dot", DOSSIER_DOT, basename, noVersion);
	sprintf(fnamePng, "%s%s_v%02u.png", DOSSIER_PNG, basename, noVersion);

	CHECK_IF(fp = fopen(fnameDot, "w"), NULL, "erreur fopen dans saveDotBST");
	
	noVersion ++;
    fprintf(fp, "digraph %s {\n", basename);
 	fprintf(fp, 
		"\tnode [\n"
			"\t\tfontname  = \"Arial bold\" \n"
			"\t\tfontsize  = \"14\"\n"
			"\t\tfontcolor = \"red\"\n"
			"\t\tstyle     = \"rounded, filled\"\n"
			"\t\tshape     = \"record\"\n"
			"\t\tfillcolor = \"grey90\"\n"
			"\t\tcolor     = \"blue\"\n"
			"\t\twidth     = \"2\"\n"
			"\t]\n"
		"\n"
		"\tedge [\n"
			"\t\tcolor     = \"blue\"\n"
		"\t]\n\n"
	);

    if (root == NULL)
        fprintf(fp, "\n");
    else
        genDotAVL(root, fp);

    fprintf(fp, "}\n");	
    fclose(fp);

    sprintf(cmdLine, "dot -Tpng  %s -o %s", fnameDot, fnamePng);
    system(cmdLine);

    printf("Creation de '%s' et '%s' ... effectuee\n", fnameDot, fnamePng);
}

//-------------

static T_node* newNode(T_elt element)
{
	T_node* node = (T_node*) malloc(sizeof(T_node));
	
	node->data = eltdup(element);
	node->balance = BALANCED;
	
	node->left = NULL;
	node->right = NULL;
	
	return node;
}

static T_node* balanceAVL(T_node* root)
{
	//printf("%d\n", root->balance);
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

static void genDotAVL(const T_avl root, FILE* basename)
{
	fprintf(basename, "\t%s",toString(root->data)); 
	fprintf(basename, " [label = \"{{<c> %s | <b> %d} | { <g> | <d>}}\"];\n",toString(root->data),root->balance);
	if (root->right == NULL && root->left == NULL)
	{
		fprintf(basename, "\t%s", toString(root->data));
		fprintf(basename, " [label = \"{{<c> %s | <b> %d} | { <g> NULL | <d> NULL}}\"];\n", toString(root->data),root->balance);
	}
	else if (root->right == NULL)
	{
		fprintf(basename, "\t%s", toString(root->data));
		fprintf(basename, " [label = \"{{<c> %s | <b> %d} | { <g> | <d> NULL}}\"];\n", toString(root->data),root->balance);
	}
	else if (root->left == NULL)
	{
		fprintf(basename, "\t%s",toString(root->data));
		fprintf(basename, " [label = \"{{<c> %s | <b> %d} | { <g> NULL | <d> }}\"];\n", toString(root->data),root->balance);
	}

	if (root->left)
	{
		fprintf(basename, "\t%s",toString(root->data));
		fprintf(basename, ":g -> %s;\n", toString(root->left->data));
		genDotAVL(root->left, basename);
	}

	if (root->right)
	{
		fprintf(basename, "\t%s",toString(root->data));
		fprintf(basename,":d -> %s;\n", toString(root->right->data));
		genDotAVL(root->right, basename);
	}
}
