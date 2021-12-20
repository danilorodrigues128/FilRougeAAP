#include <stdio.h>
#include <assert.h>
#include "include/avl.h"
#include "include/anagram_index.h"
#include "include/check.h"
#include "include/traces.h"
#include <time.h>
#include <math.h>

int main(int argc, char* argv[])
{
	assert(argc == 2);
	char* fichierTxt = argv[1];
	
	FILE* fichier = fopen(fichierTxt, "r");
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
	
	T_anagramIndex index = NULL;
	/*index = addAnagram(index, avl);
	index = addAnagram(index, avl->left);
	index = addAnagram(index, avl->right);*/
	index = searchAnagrams(avl);
	
	system("clear");
	
	printAVL(avl, 0);
	printAnagramIndex(index);

	
	return 0;
}


