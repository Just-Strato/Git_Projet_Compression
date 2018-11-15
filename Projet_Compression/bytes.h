#ifndef DEF_BYTE
#define DEF_BYTE

#include <stdio.h>

/**
*byte type definition
*
*/
typedef unsigned char Byte_t;

/**
*definition du type triple d'octet
*
*/
typedef Byte_t ByteTriplet_t[3];

 /**
  * @brief afficher un octet au format binaire
  * Entrées :
  * 	+ Oc, l'octet à afficher
  * 	+ ident, son identifiant
  * 	+	mode == 1, affiche également la valeur en décimal
  */
void displayByte(
	const Byte_t Oc,
	const char* ident,
	const int mode);

/**
 * @brief lire un octet en s'assurant que sa valeur soit bien comprise
 * entre les valeurs 0 et 255 incluses
 */
Byte_t readByte();


/**
 * @brief extraire la valeur du n^{ième} bit de l'octet Oc
 * avec n comprise entre 0 et 7
 */
int extractBit(const Byte_t Oc, const int n);


/**
 * @brief modifier la valeur du n^{ième} bit de l'octet OC
 * avec n compris entre 0 et 7
 */
Byte_t editBit(const Byte_t Oc, const int n);

/**
 *
 * @brief extraire les valeurs des 4 bits de poids faible de l'octet Oc
 */
Byte_t readLowQuartet(Byte_t O);

/**
 *
 * @brief extraire les valeurs des 4 bits de poids fort de l'octet Oc
 */
Byte_t readUpQuartet(Byte_t O);

/**
 *
 * @brief modifier les valeurs des 4 bits de poids faible de l'octet Oc
 */
Byte_t writeLowQuartet(Byte_t O, Byte_t qi);

/**
 *
 * @brief modifier les valeurs des 4 bits de poids fort de l'octet Oc
 */
Byte_t writeUpQuartet(Byte_t O, Byte_t qs);

/**
*
* @brief ecrire x dans la moitie superieur de b et le reste dans a, puis y dans la
* moitie inferieur de b et le reste dans c
*/
void writeByteTriplet(Byte_t *a, Byte_t *b, Byte_t *c, int x, int y);

/**
*
* @brief ecrire dans x et y deux entier recuperés dans a et quartet superieur de b,
* et dans quartet inferieur de b et c
*/
void recoverByteTriplet(Byte_t a, Byte_t b, Byte_t c, int *x, int *y);

/**
*
*@brief crypte les bytes avec le système XOR
*/
Byte_t encryDecryXOR(Byte_t byte, Byte_t key);

/**
*
*@brief crypte avec le système XOR tout les Bytes d'un ByteTriplet
*/
void byteTripletEncryDecryXOR(ByteTriplet_t bytes, int key);

/**
*
*@brief compresse, crypte, et envoie les deux code x et y
*/
void secureSending(int x, int y, Byte_t key);

/**
*
*@brief décompresse, décrypte, et récupère les deux code x et y
*@return 0 si aucun code récupéré
*/
int secureReceiving(int *x, int *y, Byte_t key);


#endif
