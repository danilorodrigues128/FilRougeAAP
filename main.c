#include <stdio.h>
#include "include/avl.h"

int main(int argc, char* argv[])
{
	T_elt element = genElt();
	T_elt element2 = genElt();
	T_elt dup = eltdup(element);
	printf("%s\n",toString(element));
	printf("%d\n",eltcmp(element, dup));
	printf("%d\n",eltcmp(element2, dup));
	
	return 0;
}
