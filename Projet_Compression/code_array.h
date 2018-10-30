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
	int* _codes;
	unsigned int _size;
}CodeArray_t;

/**
*@brief resume les codes dans codeArray
*
*@param const CodeArray_t* codeArray le tableau a resume
*@return une chaine avec le resume
*/
char* summaryCodeArray(const CodeArray_t* codeArray);

#endif