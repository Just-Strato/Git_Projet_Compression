/**
* @file lzw_coder.h
* @brief en-tete de lzw-coder
*/
#ifndef DEF_CODAGE
#define DEF_CODAGE

#include"stdio.h"

/**
* @struct Dictionary_t
* @brief Dictionnaire de mots
*
*Dionctionary_t est un objet comportant un 
*tableau de taille maximum SIZE_MAX avec 
*size mots qui sont dans un 
*tableau de pointeur
*/
typedef struct {
	char** word;
	int size;
}Dictionary_t;

/**
*@struct List_t
*@brief Liste de code
*
*List_t est un objet comportant un code
*et un pointeur sur un suivant du meme type. 
*C'est une liste..
*/
typedef struct List_t{
	int code;
	List_t * next;
}List_t;


#endif