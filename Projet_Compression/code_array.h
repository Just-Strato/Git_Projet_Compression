/**
* @file code_array.h
* @brief en-tete de code_array.cpp
*/
#ifndef DEF_LIST
#define DEF_LIST

#include <stdio.h>

/**
*@struct CodeArray_t
*@brief Array de code
*
*CodeArray_t est une structure avec un pointeur d'entier
*pour recevoir un tableau de size entier
*/
typedef struct CodeArray_t {
	unsigned int* codes;
	unsigned int size;
	unsigned int capacity;
}CodeArray_t;

/**
*@brief alloue la memoire d'un tableau de code
*
*@return un pointeur sur tableau de code
*/
CodeArray_t* allocateCodeArray();

/**
*@brief ajoute un code au tableau tout en créant de l'espace 
*si nécessaire
*
*@param CodeArray_t* caray la structure de code
*@param const int code le code à ajouter
@return l'indice du code ajouté
*/
unsigned int addCode(CodeArray_t* caray, const int code);
/**
*@brief resume les codes dans codeArray
*
*@param const CodeArray_t* codeArray le tableau a resume
*@return une chaine avec le resume
*/
char* summaryCodeArray(const CodeArray_t* caray);

#endif