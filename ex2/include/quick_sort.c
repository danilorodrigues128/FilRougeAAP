#include "quick_sort.h"

static int Partitionnement (T_elt t, int g, int d); 
static void echanger(T_elt t, int i1, int i2);
static void getAnotherPivot(T_elt t, int size) ;

T_elt quickSort_Signature(T_elt str, int n) {

	if(n == 1)
	{
		return str;
	}
	
	int pos_pivot;
	do
	{
		getAnotherPivot(str, n);
		pos_pivot = Partitionnement(str, 0, n-1);
	} while(pos_pivot == n-1);
	
	T_elt gauche = quickSort_Signature(str, pos_pivot+1);
	
	T_elt addressDroite = str+pos_pivot+1;
	quickSort_Signature(addressDroite, n - pos_pivot - 1);
	
	return gauche;
}

//-------------------//

static int Partitionnement (T_elt t, int g, int d){ 
	int pg=g , pd=d-1;

	while (pg<pd)
	{
		while ( (pg<pd) &&  (t[pg]-t[d]) <=0 ) {pg++;}
		while ( (pg<pd) && (t[pd]-t[d])>0) {pd--;}

		if (pg < pd) {
			echanger(t,pg,pd); 
			pg++ ; pd-- ; 
		}
	}
	
	if ((t[pg]-t[d]) <= 0)
	{
		pg++ ;  
	}
	echanger(t, pg, d) ;

	return pg ; 
}

static void echanger(T_elt t, int i1, int i2) {
	char eltAux = t[i1];
	t[i1] = t[i2];
	t[i2] = eltAux;
}

static void getAnotherPivot(T_elt t, int size) {
	int newPivot = rand() % (size-1);
	echanger(t, newPivot, size-1);
}
