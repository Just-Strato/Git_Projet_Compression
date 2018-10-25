/**
* @file lzw_coder.h
* @brief en-tete de lzw-coder
*/
#ifndef DEF_CODAGE
#define DEF_CODAGE

#include"stdio.h"

#define NOT_INSIDE -1

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
	const char** _words;
	unsigned int _size=0;
}Dictionary_t;

/**
*@brief cherche la chaine dans le dictionnaire
*
*@param const char* str la chaine a chercher
*@return l'indice de l'element sinon NOT_INSIDE
*/
unsigned int findWord(const char* word);

/**
*@brief Ajoute la chaine au dictionnaire 
*si le tableau n'est pas complet, sinon n'ajoute plus
*
*@param char* word la chaine a ajouter
*@return l'indice de l'element ajoute sinon NOT_INSIDE
*/
unsigned int addWord(const char* word);

/**/
#endif