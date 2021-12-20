#include "elt.h"

#ifdef ELT_CHAR
char* toString(T_elt element)
{
	static char str[2];
	str[0] = element;
	str[1] = '\0';
	return str;
}

T_elt genElt(void)
{
	static char c = 'a'-1;
	c++;
	return c;
}

T_elt eltdup(T_elt element)
{
	return element;
}

int eltcmp(T_elt element1, T_elt element2)
{
	return element1 - element2;
}
#endif

#ifdef ELT_INT
char* toString(T_elt element)
{
	static char str[11];
	sprintf(str, "%d", element);
	return str;
}

T_elt genElt(void)
{
	static int index = -1;
	index++;
	return index;
}

T_elt eltdup(T_elt element)
{
	return element;
}

int eltcmp(T_elt element1, T_elt element2)
{
	return element1 - element2;
}
#endif

#ifdef ELT_STRING
char* toString(T_elt element)
{
	return element;
}

T_elt genElt(void)
{
	char str[15];
	static int index=0;
	sprintf(str, "elt_%d", index++);
	return strdup(str);
}

T_elt eltdup(T_elt element)
{
	return strdup(element);
}

int eltcmp(T_elt element1, T_elt element2)
{
	return strcmp(element1, element2);
}

int processWord(T_elt word)
{
	int j;
	for(j=0;j<128;j++)
	{
		if(word[j]=='\n')
		{
			word[j]='\0';
			return j;
		}
	}
	
	return -1;
}
#endif

#ifdef ELT_STRUCT
char* toString(T_elt element)
{
	static char str[11];
	sprintf(str, "%d", element.t[0]);
	return str;
}

T_elt genElt(void)
{
	T_elt aux;
	static int index=0;
	
	aux.t = (int*) malloc(sizeof(int));
	aux.t[0] = index++;
	
	aux.size = 1;
	return aux;
}

T_elt eltdup(T_elt element)
{
	T_elt aux;
	
	aux.size = element.size;
	
	aux.t = (int*) malloc(element.size * sizeof(int));
	memcpy(aux.t, element.t, element.size * sizeof(int));

	return aux;
}

int eltcmp(T_elt element1, T_elt element2)
{
	return element1.t[0] - element2.t[0];
}
#endif

