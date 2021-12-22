#include "anagram_index.h"

static T_anagramNode* newNode(T_node* nodeAddress);

T_anagramIndex addAnagram(T_anagramIndex anagramIndex, T_node* nodeAddress)
{
	int nbAnagrams = getSize(nodeAddress->mots);
	
	T_anagramNode* prevNode = NULL;
	T_anagramNode* nextNode = anagramIndex;
	
	while(nextNode != NULL)
	{
		int nbAnagramsInNode = nextNode->nbAnagrams;
		if(nbAnagramsInNode == nbAnagrams)
		{
			nextNode->anagrams = addNodeStack(nextNode->anagrams, nodeAddress);
			return anagramIndex;
		}
		else if(nbAnagramsInNode < nbAnagrams)
		{
			T_anagramNode* node = newNode(nodeAddress);
			if(prevNode == NULL)
			{
				node->pNext = nextNode;
				return node;
			}
			else
			{
				prevNode->pNext = node;
				node->pNext = nextNode;
				return anagramIndex;
			}
		}
		else
		{
			prevNode = nextNode;
			nextNode = nextNode->pNext;
		}
		
	}
	
	T_anagramNode* node = newNode(nodeAddress);
	if(prevNode != NULL)
	{
		prevNode->pNext = node;
		return anagramIndex;
	}
	else
	{
		return node;
	}
}

void printAnagramIndex(T_anagramIndex anagramIndex)
{
	T_anagramNode* nextNode = anagramIndex;
	while(nextNode != NULL)
	{
		if(nextNode->nbAnagrams <= 1) break;
	
		printf("\n[%d ANAGRAMMES]\n", nextNode->nbAnagrams);
		printStack(nextNode->anagrams);
		nextNode = nextNode->pNext;
	}
}

T_anagramIndex searchAnagrams(T_avl avl)
{
	if(avl == NULL) return NULL;
	
	static T_anagramIndex index = NULL;
	index = addAnagram(index, avl);
	if(avl->left != NULL) index = searchAnagrams(avl->left);
	if(avl->right != NULL) index = searchAnagrams(avl->right);
	
	return index;
}

int countAnagrams(T_anagramIndex anagramIndex)
{
	int count = 0;
	while(anagramIndex != NULL)
	{
		if(anagramIndex->nbAnagrams <= 1) break;
	
		count += anagramIndex->nbAnagrams * getSizeStack(anagramIndex->anagrams);
		anagramIndex = anagramIndex->pNext;
	}
	return count;
}

void freeAnagramIndex(T_anagramIndex index)
{
	if(index == NULL) return;
	
	freeAnagramIndex(index->pNext);
	
	freeStack(index->anagrams);
	free(index);
}

//-----------------------------

static T_anagramNode* newNode(T_node* nodeAddress)
{
	T_anagramNode* node = (T_anagramNode*) malloc(sizeof(T_anagramNode));
	
	node->anagrams = addNodeStack(NULL, nodeAddress);
	node->nbAnagrams = getSize(nodeAddress->mots);
	node->pNext = NULL;
	
	return node;
}

