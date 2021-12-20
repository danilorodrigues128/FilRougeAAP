#include "anagram_index.h"

static T_anagramNode* newNode(T_node* nodeAddress)
{
	T_anagramNode* node = (T_anagramNode*) malloc(sizeof(T_anagramNode));
	
	node->anagrams = addNodeStack(NULL, nodeAddress);
	node->nbAnagrams = getSize(nodeAddress->mots);
	node->pNext = NULL;
	
	return node;
}

/*static unsigned int getIndexSize(T_anagramIndex index)
{
	int count = 0;
	T_anagramNode* nextNode = index;
	while(nextNode != NULL)
	{
		count++;
		nextNode = nextNode->pNext;
	}
	
	return count;
}*/

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
		printf("\n[%d ANAGRAMMES]\n", nextNode->nbAnagrams);
		printStack(nextNode->anagrams);
		nextNode = nextNode->pNext;
	}
}

T_anagramIndex searchAnagrams(T_avl avl)
{
	if(avl == NULL) return NULL;
	
	T_anagramIndex index = NULL;
	index = addAnagram(index, avl);
	if(avl->left != NULL) index = addAnagram(index, avl->left);
	if(avl->right != NULL) index = addAnagram(index, avl->right);
	
	return index;
}

