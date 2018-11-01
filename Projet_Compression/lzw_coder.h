/**
* @file lzw_coder.h
* @brief en-tete de lzw-coder
*/
#ifndef DEF_CODAGE
#define DEF_CODAGE

#include <stdio.h>
#include"bytes_array.h"

/**
* @struct Dictionary_t
* @brief Dictionnaire de mots
*
*Dionctionary_t est un objet comportant un 
*tableau de taille maximum DIARY_MAX_SIZE avec 
*size mots qui sont dans un 
*tableau de pointeur
*/
typedef struct {
	char** words;
	unsigned int size;
}Dictionary_t;

/**
*@brief alloue la memoire d'un dictionnaire
*
*@return un pointeur sur dictionnaire
*/
Dictionary_t* allocateDiary();

/**
*@brief Destructeur de Dictionnaire
*
*@return le nombre de mot libere
*/
unsigned int releaseDiary(Dictionary_t* diary);

/**
*@brief cherche la chaine dans le dictionnaire
*
*@param const Dictionary_t* le dictionnaire
*@param const char* str la chaine a chercher
*@return l'indice de l'element dans le dictionnaire sinon NOT_INSIDE
*/
int findWord(const Dictionary_t* diary, const char* word);

/**
*@brief Ajoute la chaine au dictionnaire 
*si le tableau n'est pas complet, sinon n'ajoute plus
*
*@param const Dictionary_t* le dictionnaire
*@param char* word la chaine a ajouter
*@return l'indice de l'element ajoute sinon NOT_INSIDE
*/
int addWord(Dictionary_t* diary, const char* word);

/**
*@brief forme une chaine contenant chaque mot
*du dictionnaire
*
*@param Dictionary_t* diary le dictionnaire a  resume
@return une chaine contenant le resume
*/
char* summaryDiary(const Dictionary_t* diary);

/**
*@brief complete le dictionnaire et renvoit un tableau de code
*realise celon le principe du codeur LZW
*
*@param const char* msg le message a code
*@param Dictionary_t* diary le dictionnaire a remplir
*Si le dictionnaire n'est pas precise, l'initialise a l"interieur et le libere
*
*@return la liste de code realise
*/
CodeArray_t* lzwCoder(Dictionary_t* diary, const char* msg);

/**
*@brief si la chaine avec le caractere est dans le dico on passe
*sinon on ajoute la chaine au dictionnaire et vide la chaine
*
*@param Dictionary_t* diary le dictionnaire a completer
*@param char* word le nouveau mot
*@param char c le nouveau caractere lu
*
*@return l'indice du message si ajouter dans le dictionnaire, sinon NOT_INSIDE
*/
int findOrAddWord(Dictionary_t* diary, char* word, char c);

/**
*@brief complete le dictionnaire et renvoit le message decode
*a partir de codeArray en suivant le principe du decodeur LZW
*
*@param const CodeArray_t* codeArray le tableau de code a decoder
*@param Dictionary_t* diary le dictionnaire a remplir
*si le dictionnaire n'est pas precise, l'initialise a l'interieur et le libere
*
*@return le message obtenu du tableau de code
*/
void lzwDecoder(Dictionary_t* diary, const CodeArray_t* codeArray);


#endif