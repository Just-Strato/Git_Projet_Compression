#include "global.h"

void displayByte(
	const Byte_t Oc ,
	const char * ident ,
	const int mode ) {
  static char buffer[8];
  int n;

  printf( "%s = 0b" , ident );
  for( n = 0 ; n < 8 ; n++ ) {
    Byte_t bit = (1 << n);
    buffer[7-n] = ((Oc & bit) ? '1' : '0');
  }
  printf( "%s" , buffer );
  if( mode == 1 )
    printf( " = %u" , Oc );
  printf( "\n" );
}

Byte_t readByte() {
  int c;

  printf( "un octet : " );
  scanf_s( " %d" , &c );

  // les seules valeurs possibles pour un octet
  assert( -1 < c && c < 256 );

  return (Byte_t) c;
}

int extractBit( const Byte_t Oc , const int n ) {
  assert( -1 < n && n < 8 );

  Byte_t Dn = (1 << n);

  return ((Oc & Dn) ? 1 : 0);
}

Byte_t editBit( const Byte_t Oc , const int n ) {
  assert( -1 < n && n < 8 );

  Byte_t Dn = (1 << n);

  return (Oc ^ Dn);
}

Byte_t readLowQuartet( Byte_t O ) {
	static Byte_t masque = 0b00001111;

	return (O & masque);
}

Byte_t readUpQuartet( Byte_t O ) {
	static unsigned int offset = 0b00001111;

	return ((O | offset) - offset);
}

Byte_t writeLowQuartet( Byte_t O, Byte_t qi ) {
		return ((O-readLowQuartet(O))|readLowQuartet(qi));
}

Byte_t writeUpQuartet( Byte_t O, Byte_t qs ) {
        return ((O-readUpQuartet(O))|readUpQuartet(qs));
}

void writeByteTriplet(Byte_t *a, Byte_t *b, Byte_t *c, int x, int y)
{
	*a = x >> 4;
	*b = writeUpQuartet(*b, x << 4);
	*b = writeLowQuartet(*b, y >> 8);
	*c = y ;
}

void recoverByteTriplet(Byte_t a, Byte_t b, Byte_t c, int *x, int *y)
{
    *x=0;
	*x = a;
	*x = *x << 4;
	*x = (*x-readLowQuartet(*x))|writeLowQuartet(*x, b>>4);
	*y=0;
	*y = writeLowQuartet(*y, b);
	*y = *y << 8;
	*y = (*y-readUpQuartet(*y))|writeUpQuartet(*y, c);
	*y = (*y-readLowQuartet(*y))|writeLowQuartet(*y, c);
}

ByteTripletArray_t* compressCode(const CodeArray_t* caray) {

	int unsigned k;
	ByteTripletArray_t* bytray = (ByteTripletArray_t *)malloc(sizeof(ByteTripletArray_t)); assert(bytray != NULL);

	/*On initialise le nombre d'octets, avec 3 octets par couples d'entiers*/
	bytray->size = caray->size / 2;
	bytray->array = (ByteTriplet_t*)malloc(bytray->size * sizeof(ByteTriplet_t)); assert(bytray->array != NULL);

	for (k = 0; k < caray->size; k++) {
		writeByteTriplet(bytray->array[k], bytray->array[k + 1], bytray->array[k + 2],
			caray->codes[k * 2], caray->codes[k * 2 + 1]);
	}

	return bytray;
}

CodeArray_t* uncompressCode(const ByteTripletArray_t *bytray) {

	int unsigned k, x, y;
	CodeArray_t* caray = allocateCodeArray();
 
    for(k = 0; k < bytray->size; k++) {
        recoverByteTriplet(bytray->array[k][0], bytray->array[k][1], bytray->array[k][2],
			x, y);
		addCode(caray, x);
		addCode(caray, y);
    }

    /*nombre de code en fonction du nombre de triples (1 triples -> 2 codes)*/
    caray->size = bytray->size * 2;
	if (caray->codes[caray->size - 1] == 0)
		caray->size--;

    return caray;
}

void releaseByteTripletArray(ByteTripletArray_t *bytray) {
    free(bytray->array);
    free(bytray);
}

Byte_t encryDecryXOR(Byte_t byte, Byte_t key) {

    return byte ^ key;
}

void encryDecryByteTripletArray(ByteTripletArray_t *bytray, const Byte_t key) {

	int unsigned i, k;

    //On chiffre/dechiffre chaques triplés de chaque tableaux du tableau dans tabOctet
    for( k = 0; k < bytray->size; k++) {

        for( i = 0; i < 3; i++) 
			bytray->array[k][i]=encryDecryXOR(bytray->array[k][i],key);
        
    }
}
