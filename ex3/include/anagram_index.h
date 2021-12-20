#ifndef ANAGRAM_INDEX_H
#define ANAGRAM_INDEX_H

#include "stack.h"

typedef struct anagram_node
{
	T_stack anagrams;
	int nbAnagrams;
	struct anagram_node* pNext;
} T_anagramNode, *T_anagramIndex;

T_anagramIndex addAnagram(T_anagramIndex anagramIndex, T_node* nodeAddress);
void printAnagramIndex(T_anagramIndex anagramIndex);
T_anagramIndex searchAnagrams(T_avl avl);

#endif
