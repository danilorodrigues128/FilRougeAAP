#include <stdio.h>
#include <assert.h>
#include "include/avl.h"
#include "include/check.h"

void clearName(char* name); // Supprimer le '\n' à la fin de chaque nom

int main(int argc, char* argv[])
{
	assert(argc == 3);
	char* fichierTxt = argv[1];
	int mots = atoi(argv[2]);
	
	FILE* fichier = fopen(fichierTxt, "r");
	CHECK_IF(fichier, NULL, "> [ERREUR] Fichier invalide !");
	
	T_avl avl = NULL;
	
	int i;
	char str[128];
	for(i=0;i<mots;i++)
	{
		fgets(str, 128, fichier);
		clearName(str);
		insertAVL(&avl, str);
		printAVL(avl, 0);
		printf("-----------\n");
		createDotAVL(avl, "prenoms");
	}
	
	return 0;
}

void clearName(char* name)
{
	int j;
	for(j=0;j<128;j++)
	{
		if(name[j]=='\n')
		{
			name[j-1]='\0';
			break;
		}
	}
}


