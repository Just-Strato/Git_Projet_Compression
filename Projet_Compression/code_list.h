/**
* @file code_list.h
* @brief en-tete de code_list.cpp
*/
#ifndef DEF_LIST
#define DEF_LIST

#include"stdio.h"

/**
*@struct List_t
*@brief Liste de code
*
*List_t est un objet comportant un code
*et un pointeur sur un suivant du meme type.
*C'est une liste..
*/
typedef struct List_t {
	int code;
	List_t * next;
}List_t;


#endif