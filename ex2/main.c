#include <stdio.h>
#include <assert.h>
#include "include/avl.h"
#include "include/check.h"
#include "include/traces.h"

int clearName(char* name); // Supprimer le '\n' à la fin de chaque nom

int main(int argc, char* argv[])
{
	assert(argc == 2);
	char* fichierTxt = argv[1];
	
	FILE* fichier = fopen(fichierTxt, "r");
	CHECK_IF(fichier, NULL, "> [ERREUR] Fichier invalide !");
	
	char str[128];
	
	while(fgets(str, 128, fichier) != NULL)
	{
		int size = clearName(str);
	
		T_elt nom = (T_elt) malloc(size * sizeof(char));
		nom = eltdup(str);
	}
	
	return 0;
}

int clearName(char* name)
{
	int j;
	for(j=0;j<128;j++)
	{
		if(name[j]=='\n')
		{
			name[j-1]='\0';
			return j-1;
		}
	}
	
	return -1;
}


