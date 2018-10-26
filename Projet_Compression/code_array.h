/**
* @file code_array.h
* @brief en-tete de code_array.cpp
*/
#ifndef DEF_LIST
#define DEF_LIST

#include"stdio.h"

/**
*@struct CodeArray_t
*@brief Array de code
*
*CodeArray_t est une structure avec un pointeur d'entier
*pour recevoir un tableau de size entier
*/
typedef struct CodeArray_t {
	int *codes;
	int size;
}CodeArray_t;


#endif