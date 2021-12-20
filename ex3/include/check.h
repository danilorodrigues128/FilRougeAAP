#include <stdlib.h>

/* Lorsque stat vaut val alors l'opération dont le résultat est stat, a échoué. Pour la plupart des appels système Posix, la valeur signalant l'échec est -1. Elle correspond à NULL lorsque l'appel système retourne un pointeur.  */

#ifndef DEBUG
#define CHECK_IF(stat, val, msg)    \
	if ( (stat) == (val) )          \
	{                               \
		perror(msg);                \
		exit(EXIT_FAILURE);       \
    }                       
#else
#define CHECK_IF(stat, val, msg)    \
	if ( (stat) == (val) )          \
	{                               \
    	perror(msg);                \
		exit(EXIT_FAILURE);       \
    }                               \
    else printf("%s ... OK\n", msg)
#endif

