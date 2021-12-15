#include <stdio.h> // printf
#include <stdlib.h> // system 
#include <libgen.h> // basename

#ifndef _TRACES_H_
#define _TRACES_H_
 
#define WHOAMI() printf("%s (%s %s)\n\n",basename(argv[0]),__DATE__,__TIME__);
// NB : pour utiliser cette macro, il faut nommer les arguments de main

#define PRINT_FILE() printf("Fichier: %s ", __FILE__);
#define PRINT_FN() printf("Fonction: %s ", __FUNCTION__);
#define PRINT_LINE() printf("Ligne: %d ", __LINE__);

#define TOUCH_HERE(s) NL(); PRINT_LBL(LBL_PROMPT); PRINT_FILE(); PRINT_FN(); PRINT_LINE(); NL(); PROMPT(s); NL(); 

#define LBL_NB "NB: "
#define LBL_CODE "CODE: "
#define LBL_PROMPT ">> "

#define LITERAL( x ) # x
#define QUOTE( x ) LITERAL( LITERAL( x ) )
// https://stackoverflow.com/questions/13741048/return-quoted-string-in-c-macro

#define CHAR char

#define PRINT_LBL(lbl) printf("%s\t",lbl); 

#define CODE(s) PRINT_LBL(LBL_CODE); printf(LITERAL(s));printf(";"); NL();

#define NOTE(s) PRINT_LBL(LBL_NB);printf(s);
#define NOTE1(s,a) PRINT_LBL(LBL_NB);printf(s,a);
#define NOTE2(s,a,b) PRINT_LBL(LBL_NB);printf(s,a,b);

#define PROMPT(s) PRINT_LBL(LBL_PROMPT);printf(s);
#define PROMPT1(s,a) PRINT_LBL(LBL_PROMPT);printf(s,a);
#define PROMPT2(s,a,b) PRINT_LBL(LBL_PROMPT);printf(s,a,b);

#define NL() printf("\n");
#define HR() printf("\n\n----------------------------------------------------------------\n\n");

// faut-il effacer l'écran avant de continuer lors des séparations ?
//#define CLEAR2CONTINUE

#define CLRSCR() system("clear");

#ifdef CLEAR2CONTINUE
	#define ENTER2CONTINUE() printf("\nAppuyer sur entree pour continuer..."); \
								getchar(); \
								CLRSCR();
#else 
	#define ENTER2CONTINUE() printf("\nAppuyer sur entree pour continuer...");	\
								getchar();
#endif 

#define DUMPHEAD()	printf("\nVariable |   Type   | Taille |     Adresse    | Valeur\n");


#define DUMPCHAR(varname) printf("%8s | %8s | %6ld | %p | %d\n",LITERAL(varname),"char",sizeof(char), &(varname), varname);

#define DUMPINT(varname) printf("%8s | %8s | %6ld | %p | %d\n",LITERAL(varname),"int",sizeof(int), &(varname), varname);

#define DUMPAD(varname) printf("%8s | %8s | %6ld | %p | %p\n",LITERAL(varname),"adresse",sizeof(varname), &(varname), varname);

#endif

