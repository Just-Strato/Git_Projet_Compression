/**
* \file lzw_coder.h
* \brief en-tete de lzw-coder
*/
#ifndef DEF_CODAGE
#define DEF_CODAGE

#include"stdio.h"

/**
* \struct Dictionary_t
* \brief Dictionnaire de mots
*
*Dionctionary_t est un objet comportant un 
*tableau de taille maximum SIZE_MAX avec 
*size mots qui sont socke dans un 
*tableau de pointeur
*/
typedef struct {
	char** word;
	int size;
}Dictionary_t;

typedef struct Array_t{
	int code;
	Array_t * next;
}Array_t;
#endif