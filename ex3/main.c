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
	
	/*T_anagramIndex index = NULL;
	index = addAnagram(index, avl);
	index = addAnagram(index, avl->left);
	index = addAnagram(index, avl->right);*/
	T_anagramIndex index = NULL;
	index = searchAnagrams(avl);
	
	system("clear");
	
	printAVL(avl, 0);
	
	//TESTE
	
	/*T_anagramIndex index = NULL;
	
	T_node* node3 = newNodeAVL("ABC", "ABC", 3);
	node3->mots = addNode("ACB", node3->mots);
	node3->mots = addNode("CBA", node3->mots);
	
	T_node* node3_2 = newNodeAVL("XYZ", "XYZ", 3);
	node3_2->mots = addNode("XZY", node3_2->mots);
	node3_2->mots = addNode("XYZ", node3_2->mots);
	
	T_node* node2 = newNodeAVL("DE", "ED", 2);
	node2->mots = addNode("DE", node2->mots);
	
	T_node* node2_2 = newNodeAVL("OP", "PO", 2);
	node2_2->mots = addNode("PO", node2_2->mots);
	
	T_node* node1 = newNodeAVL("F", "F", 2);
	
	node1->left = node2;
	node1->right = node3_2;
	node3_2->left = node2_2;
	node2->right = node3;
	
	printAVL(node1, 0);
	
	index = addAnagram(index, node2);
	index = addAnagram(index, node3_2);
	index = addAnagram(index, node1);
	index = addAnagram(index, node3);
	index = searchAnagrams(node1);*/
	
	///////
	
	printAnagramIndex(index);

	
	return 0;
}


