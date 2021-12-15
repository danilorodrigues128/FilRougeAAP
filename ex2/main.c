#include <stdio.h>
#include <assert.h>
#include "include/avl.h"
#include "include/check.h"
#include "include/traces.h"
#include <time.h>

int clearName(char* name); // Supprimer le '\n' à la fin de chaque nom

int main(int argc, char* argv[])
{
	assert(argc == 2);
	char* fichierTxt = argv[1];
	
	FILE* fichier = fopen(fichierTxt, "r");
	CHECK_IF(fichier, NULL, "> [ERREUR] Fichier invalide !");
	
	char str[128];
	T_avl avl = NULL;
	
	int counter = 0;
	
	clock_t debut = clock();
	while(fgets(str, 128, fichier) != NULL)
	{
		counter++;
		
		int size = clearName(str);
	
		T_elt nom = (T_elt) malloc(size * sizeof(char));
		nom = eltdup(str);
		
		insertAVL(&avl, nom, size);
	}
	clock_t fin = clock();
	
	//printAVL(avl, 0);
	
	printf("Nombre de mots : %d\n",counter);
	printf("Durée de construction : %ld ms\n", (fin - debut) * 1000 / CLOCKS_PER_SEC);
	
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


