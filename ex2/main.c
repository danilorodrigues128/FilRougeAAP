#include <stdio.h>
#include <assert.h>
#include "include/avl.h"
#include "include/check.h"
#include "include/traces.h"
#include <time.h>
#include <math.h>

int processWord(char* name); // Supprimer le '\n' à la fin de chaque mot et retourner le taille du mot

int main(int argc, char* argv[])
{
	assert(argc == 2);
	char* fichierTxt = argv[1];
	
	FILE* fichier = fopen(fichierTxt, "r");
	CHECK_IF(fichier, NULL, "> [ERREUR] Fichier invalide !");
	
	char str[128];
	T_avl avl = NULL;
	
	int counter = 0, size = 0;
	
	clock_t debut = clock();
	while(fgets(str, 128, fichier) != NULL)
	{
		counter++;
		
		size = processWord(str);
	
		T_elt nom = (T_elt) malloc(size * sizeof(char));
		nom = eltdup(str);
		
		insertAVL(&avl, nom, size);
	}
	clock_t fin = clock();
	
	long int duree = (fin - debut) * 1000 / CLOCKS_PER_SEC;
	int nbNoeuds = nbNodesAVL(avl);
	int hauteur = heightAVL(avl);
	int hauteurMin = (int)log2(nbNoeuds);
	
	system("clear");
	printf("Taille des mots : %d\n", size);
	printf("Nombre de mots : %d\n",counter);
	printf("Durée de construction : %ld ms\n", duree);
	printf("Nombre de noeuds : %d\n", nbNoeuds);
	printf("Hauteur de l'arbre : %d\n", hauteur);
	printf("Hauteur minimale : %d\n", hauteurMin);
	
	T_elt buffer = (T_elt) calloc(size + 1, sizeof(char));
	
	printf("\nMot a chercher : ");
	scanf("%s", buffer);
	
	while(strcmp(buffer, "q"))
	{
		debut = clock();
		T_node* node = searchAVL_it(avl, buffer, size);
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
		
		
		printf("\nMot a chercher : ");
		scanf("%s", buffer);
	}
	
	return 0;
}

int processWord(char* name)
{
	int j;
	for(j=0;j<128;j++)
	{
		if(name[j]=='\n')
		{
			name[j]='\0';
			
			//printf("ProcessWord : %s (%d)\n",name,j);
			return j;
		}
	}
	
	return -1;
}


