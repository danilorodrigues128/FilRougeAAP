#ifndef ELT_H
#define ELT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define ELT_CHAR
//#define ELT_INT
#define ELT_STRING
//#define ELT_STRUCT

#if ! defined(ELT_CHAR) && ! defined(ELT_INT) && ! defined(ELT_STRING) && ! defined(ELT_STRUCT)
	#define ELT_INT
#endif

#ifdef ELT_CHAR
typedef char T_elt;
#endif

#ifdef ELT_INT
typedef int T_elt; 
#endif

#ifdef ELT_STRING
typedef char * T_elt; 
#endif

#ifdef ELT_STRUCT
typedef struct {
	int * t;
	int size;
} T_elt; 
#endif

char* toString(T_elt e); 
T_elt genElt(void);
T_elt eltdup(T_elt); 
int eltcmp(T_elt, T_elt);
int processWord(T_elt word);
#endif
