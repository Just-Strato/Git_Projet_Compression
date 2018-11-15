#include "global.h"
#include "bytes.h"

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
  scanf( " %d" , &c );

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

Byte_t encryDecryXOR(Byte_t byte, Byte_t key) {

    return byte ^ key;
}

void byteTripletEncryDecryXOR(Byte_t* bytes, Byte_t key) {
	
	static int k;

	for (k = 0; k < 3; k++)
		bytes[k] = encryDecryXOR(bytes[k], key);
}

void secureSending(int x, int y, Byte_t key) {

	static Byte_t* bytes = NULL;
	if(bytes == NULL ) bytes = (Byte_t*)malloc(3 * sizeof(Byte_t));
	assert(bytes != NULL);

	//printf("%d %d\n", x, y);

	writeByteTriplet(bytes, bytes+1, bytes+2, x, y);

	byteTripletEncryDecryXOR(bytes, key);

	//printf("%c %c %c\n", bytes[0], bytes[1], bytes[2]);

	write(pipe_data[1], bytes, 3*sizeof(Byte_t));
}

int secureReceiving(int *x, int *y, Byte_t key) {

	static Byte_t* bytes = NULL;
	if (bytes == NULL) bytes = (Byte_t*)malloc(3 * sizeof(Byte_t));
	assert(bytes != NULL);

	read(pipe_data[0], bytes, 3*sizeof(Byte_t));

	byteTripletEncryDecryXOR(bytes, key);
	
	recoverByteTriplet(bytes[0], bytes[1], bytes[2], x, y);

	printf("%d %d\n", *x, *y);

	return *x;
}

