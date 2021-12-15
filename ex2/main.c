#include <stdio.h>
#include <assert.h>
#include "include/avl.h"
#include "include/check.h"
#include "include/traces.h"

void clearName(char* name); // Supprimer le '\n' à la fin de chaque nom

int main(int argc, char* argv[])
{
	assert(argc == 2);
	char* fichierTxt = argv[1];
	
	FILE* fichier = fopen(fichierTxt, "r");
	CHECK_IF(fichier, NULL, "> [ERREUR] Fichier invalide !");
	
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

	T_elt teste = 
	
	printf("%s (%d)\n", toString(teste), );
	//T_elt sig   = quickSort_Signature(teste);
	//printf("%s\n",toString(sig));
}

void clearName(char* name)
{
	int j;
	for(j=0;j<128;j++)
	{
		printf("%c\n",name[j]);
		if(name[j]=='\n')
		{
			name[j-1]='\0';
			return n-1;
		}
	}
}


