#pragma once


/**
*byte type definition
*
*/
typedef unsigned char t_octet;

/**
*definition du type triple d'octet
*
*/
typedef t_octet byteTriplet_t[3];

/**
* @struct BytesTripletArray_t
* @brief Tableau de triplet
*
*Represente un tableau de comportant size
*triple d'octet dans array 
*/
typedef struct {
	byteTriplet_t *array;
	unsigned int size;
}BytesTripletArray_t;

/**
 * signature des fonctions bit à bit
 */

 /**
  * @brief afficher un octet au format binaire
  * Entrées :
  * 	+ Oc, l'octet à afficher
  * 	+ ident, son identifiant
  * 	+	mode == 1, affiche également la valeur en décimal
  */
void afficher_octet(
	const t_octet Oc,
	const char *ident,
	const int mode);

/**
 * @brief lire un octet en s'assurant que sa valeur soit bien comprise
 * entre les valeurs 0 et 255 incluses
 */
t_octet lire_octet();


/**
 * @brief extraire la valeur du n^{ième} bit de l'octet Oc
 * avec n comprise entre 0 et 7
 */
int extraire_bit(const t_octet Oc, const int n);


/**
 * @brief modifier la valeur du n^{ième} bit de l'octet OC
 * avec n compris entre 0 et 7
 */
t_octet modifier_bit(const t_octet Oc, const int n);

/**
 *
 * @brief extraire les valeurs des 4 bits de poids faible de l'octet Oc
 */
t_octet lire_quartetInf(t_octet O);

/**
 *
 * @brief extraire les valeurs des 4 bits de poids fort de l'octet Oc
 */
t_octet lire_quartetSup(t_octet O);

/**
 *
 * @brief modifier les valeurs des 4 bits de poids faible de l'octet Oc
 */
t_octet ecrire_quartetInf(t_octet O, t_octet qi);

/**
 *
 * @brief modifier les valeurs des 4 bits de poids fort de l'octet Oc
 */
t_octet ecrire_quartetSup(t_octet O, t_octet qs);

/**
*
* @brief ecrire x dans la moitie superieur de b et le reste dans a, puis y dans la
* moitie inferieur de b et le reste dans c
*/
void ecrire_troisOctets(t_octet *a, t_octet *b, t_octet *c, int x, int y);

/**
*
* @brief ecrire dans x et y deux entier recuperés dans a et quartet superieur de b,
* et dans quartet inferieur de b et c
*/
void recuperer_troisOctets(t_octet a, t_octet b, t_octet c, int *x, int *y);

/**
*
*@brief ecrire par deux les entiers du tableau dans
*code sur 3 octets et retourne le tableau d'octets tabTripless
*/
T_TriplesOctet* compresserCode(const t_Code* code);

/**
*
*@brief retourne un t_code avec les valeurs compressees
* dans tabTriples
*/
t_Code* decompresserCode(T_TriplesOctet *tabTriples);

/**
*
*@brief liberer la mémoire alloué d'un T_Triples Octet
*/
void freeTabTriplesOctet(T_TriplesOctet *x);

/**
*
*@brief return chiffré ou dechiffré un octet à partir de la technique XOR avec une
*clef qui sera entré en paramètre
*/
t_octet cryptageDecryptageXOR(t_octet octet, t_octet clef);

/**
*@brief chiffre ou dechiffrechaque octet d'un T_TriplesOctet avec XOR
*/
void cryptageDecryptageTripletOctet(T_TriplesOctet *tabOctet, t_octet clef);

#endif
