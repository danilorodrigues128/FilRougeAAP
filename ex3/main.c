#include <stdio.h>
#include <assert.h>
#include "include/anagram_index.h"
#include "include/check.h"

int main(int argc, char* argv[])
{
	assert(argc == 2);
	char* fichierTxt = argv[1];
	
	T_avl avl = fileToAVL(fichierTxt);
	T_anagramIndex index = searchAnagrams(avl);
	
	printf("\nNombre de mots du dictionnaire disposant d'anagrammes : %d\n", countAnagrams(index));

	printf("\n[Appuyez sur n'importe quelle touche pour afficher les anagrammes]"); getchar();
	printAnagramIndex(index);
	
	freeAVL(avl);
	freeAnagramIndex(index);
	
	return 0;
}


