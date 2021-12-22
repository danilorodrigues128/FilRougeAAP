#include <stdio.h>
#include <assert.h>
#include "include/avl.h"
#include "include/check.h"
#include <time.h>
#include <math.h>

int main(int argc, char* argv[])
{
	assert(argc == 2);
	char* fichierTxt = argv[1];
	
	int size, counter;
	
	clock_t debut = clock();
	T_avl avl = fileToAVL(fichierTxt, &size, &counter);
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
	
	rechercherMots(avl, size);
	
	return 0;
}

