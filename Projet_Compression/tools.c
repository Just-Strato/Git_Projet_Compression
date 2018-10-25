#include "global.h"

void afficher_octet(
	const t_octet Oc ,
	const char * ident ,
	const int mode ) {
  static char buffer[8];
  int n;

  printf( "%s = 0b" , ident );
  for( n = 0 ; n < 8 ; n++ ) {
    t_octet bit = (1 << n);
    buffer[7-n] = ((Oc & bit) ? '1' : '0');
  }
  printf( "%s" , buffer );
  if( mode == 1 )
    printf( " = %u" , Oc );
  printf( "\n" );
}

t_octet lire_octet() {
  int c;

  printf( "un octet : " );
  scanf_s( " %d" , &c );

  // les seules valeurs possibles pour un octet
  assert( -1 < c && c < 256 );

  return (t_octet) c;
}

int extraire_bit( const t_octet Oc , const int n ) {
  assert( -1 < n && n < 8 );

  t_octet Dn = (1 << n);

  return ((Oc & Dn) ? 1 : 0);
}

t_octet modifier_bit( const t_octet Oc , const int n ) {
  assert( -1 < n && n < 8 );

  t_octet Dn = (1 << n);

  return (Oc ^ Dn);
}

t_octet lire_quartetInf( t_octet O ) {
	static t_octet masque = 0b00001111;

	return (O & masque);
}

t_octet lire_quartetSup( t_octet O ) {
	static unsigned int offset = 0b00001111;

	return ((O | offset) - offset);
}

t_octet ecrire_quartetInf( t_octet O, t_octet qi ) {
		return ((O-lire_quartetInf(O))|lire_quartetInf(qi));
}

t_octet ecrire_quartetSup( t_octet O, t_octet qs ) {
        return ((O-lire_quartetSup(O))|lire_quartetSup(qs));
}

void ecrireTroisOctets(t_octet *a, t_octet *b, t_octet *c, int x, int y)
{
	*a = x >> 4;
	*b = ecrire_quartetSup(*b, x << 4);
	*b = ecrire_quartetInf(*b, y >> 8);
	*c = y ;
}

void lireTroisOctets(t_octet a, t_octet b, t_octet c, int *x, int *y)
{
    *x=0;
	*x = a;
	*x = *x << 4;
	*x = (*x-lire_quartetInf(*x))|ecrire_quartetInf(*x, b>>4);
	*y=0;
	*y = ecrire_quartetInf(*y, b);
	*y = *y << 8;
	*y = (*y-lire_quartetSup(*y))|ecrire_quartetSup(*y, c);
	*y = (*y-lire_quartetInf(*y))|ecrire_quartetInf(*y, c);
}

T_TriplesOctet* compresserCode(const t_Code* code2)
{
    t_Code * code=(t_Code *)malloc(sizeof(t_Code));
    for(int i=0;i<code2->n;i++)
        code->tab[i]=code2->tab[i];
    code->n=code2->n;
    T_TriplesOctet *tabTriples=(T_TriplesOctet *)malloc(sizeof(T_TriplesOctet));

    /*Si le nombre de code est impair, alors il ne sera pas possible de mettre 2 entiers par triplés d'octet,
    on crée alors un code suplémentaire égale à 0 qui sera retiré lors du décodage*/
    if((code->n%2)!=0) {
        code->tab[code->n]=0;
        (code->n)+=1;
    }

    /*On initialise le nombre d'octets, avec 3 octets par couples d'entiers*/
    tabTriples->n=(code->n)/2;
    tabTriples->tab=(Triples*)malloc((tabTriples->n)*sizeof(Triples));
    for(int k=0;k<code->n;k++)
        ecrireTroisOctets((tabTriples->tab[k]),(tabTriples->tab[k])+1,(tabTriples->tab[k])+2,code->tab[k*2],code->tab[k*2+1]);
    free(code);
    return tabTriples;
}

t_Code* decompresserCode(T_TriplesOctet* tabTriples){
    t_Code* code=(t_Code *)malloc(sizeof(t_Code));
    assert(code!=NULL);
    for(int k=0;k<tabTriples->n;k++) {
        lireTroisOctets(tabTriples->tab[k][0],tabTriples->tab[k][1],tabTriples->tab[k][2],(code->tab)+k*2,((code->tab)+(k*2))+1);
    }

    /*nombre de code en fonction du nombre de triples (1 triples -> 2 codes)*/
    code->n=(tabTriples->n)*2;
    if(code->tab[code->n-1]==0)
        (code->n)--;
    return code;
}

void freeTabTriplesOctet(T_TriplesOctet *x) {
    free(x->tab);
    free(x);
}

t_octet cryptageDecryptageXOR(t_octet octet, t_octet clef) {

    /*La clef doit impérativement être supérieur à 0
    et inférieur à 256*/
    return octet ^ clef;
}

void cryptageDecryptageTripletOctet(T_TriplesOctet *tabOctet, t_octet clef) {
    //On chiffre/dechiffre chaques triplés de chaque tableaux du tableau dans tabOctet
    assert(clef <= 0b11111111 && clef >= 0b00000000);
    for(int k=0;k<tabOctet->n;k++) {
        for(int i=0;i<3;i++){
        tabOctet->tab[k][i]=cryptageDecryptageXOR(tabOctet->tab[k][i],clef);
        }
    }
}
