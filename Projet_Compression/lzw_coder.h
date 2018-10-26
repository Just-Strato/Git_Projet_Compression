/**
* @file lzw_coder.h
* @brief en-tete de lzw-coder
*/
#ifndef DEF_CODAGE
#define DEF_CODAGE

#include"stdio.h"
#include"code_array.h"

#define NOT_INSIDE -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

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
*@brief alloue la memoire du tableau de pointeur
*du dictionnaire
*
*@return EXIT_SUCCESS si allocation reussite sinon EXIT_FAILURE
*/
bool allocateDiry(Dictionary_t* diry);

/**
*@brief Destructeur de Dictionnaire
*
*@return le nombre de mot libere
*/
unsigned int releaseDiry(Dictionary_t* diry);

/**
*@brief cherche la chaine dans le dictionnaire
*
*@param const Dictionary_t* le dictionnaire
*@param const char* str la chaine a chercher
*@return l'indice de l'element sinon NOT_INSIDE
*/
int findWord(const Dictionary_t* diry, const char* word);

/**
*@brief Ajoute la chaine au dictionnaire 
*si le tableau n'est pas complet, sinon n'ajoute plus
*
*@param const Dictionary_t* le dictionnaire
*@param char* word la chaine a ajouter
*@return l'indice de l'element ajoute sinon NOT_INSIDE
*/
int addWord(Dictionary_t* diry, const char* word);

/**
*@brief forme une chaine contenant chaque mot
*du dictionnaire
*
*@param Dictionary_t* diry le dictionnaire a  resume
@return une chaine contenant le resume
*/
const char* summaryDiry(const Dictionary_t* diry);

/**
*@brief complete le dictionnaire et renvoit un tableau de code
*realise celon le principe du codeur LZW
*
*@param const char* msg le message a code
*@param Dictionary_t* diry le dictionnaire a remplir
*Si le dictionnaire n'est pas precise, l'initialise a l"interieur et le libere
*
*@return la liste de code realise
*/
CodeArray_t* lzwCoder(const char* msg, Dictionary_t* diry = NULL);

/**
*@brief si la chaine avec le caractere est dans le dico on passe
*sinon on ajoute la chaine au dictionnaire et vide la chaine
*
*@param Dictionary_t* diry le dictionnaire a completer
*@param char* word le nouveau mot
*@param char c le nouveau caractere lu
*
*@return l'indice du message si ajouter dans le dictionnaire, sinon NOT_INSIDE
*/
int findOrAddDiry(Dictionary_t* diry, char* word, char c);

/**
*@brief complete le dictionnaire et renvoit le message decode
*a partir de codeArray en suivant le principe du decodeur LZW
*
*@param const CodeArray_t* codeArray le tableau de code a decoder
*@param Dictionary_t* diry le dictionnaire a remplir
*si le dictionnaire n'est pas precise, l'initialise a l'interieur et le libere
*
*@return le message obtenu du tableau de code
*/
const char* lzwDecoder(const CodeArray_t* codeArray, Dictionary_t* diry = NULL);


#endif