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
	int* codes;
	unsigned int size;
}CodeArray_t;

/**
*@brief alloue la memoire d'un tableau de code
*
*@return un pointeur sur tableau de code
*/
CodeArray_t* allocateCodeArray();

/**
*@brief Destructeur de CodeArray
*
*@return le nombre de code libere
*/
unsigned int releaseCodeArray(CodeArray_t* caray);

/**
*@brief resume les codes dans codeArray
*
*@param const CodeArray_t* codeArray le tableau a resume
*@return une chaine avec le resume
*/
char* summaryCodeArray(const CodeArray_t* codeArray);

#endif