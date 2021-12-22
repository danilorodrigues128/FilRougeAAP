#include <stdio.h>
#include <assert.h>
#include "include/avl.h"
#include "include/check.h"

int main(int argc, char* argv[])
{
	assert(argc == 3);
	char* fichierTxt = argv[1];
	int mots = atoi(argv[2]);
	
	T_avl avl = fileToAVL(fichierTxt, mots);
	
	return 0;
}
