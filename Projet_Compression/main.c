#include "global.h"
#include "bytes_array.h"
#include "code_array.h"
#include "lzw_coder.h"

int main(int argc, char* argv[]) {

	char msg[] = "1234555\0", *sumD, *sumC;
	Byte_t key=0b11111111;

	Dictionary_t* diary = allocateDiary();

	CodeArray_t* caray = lzwCoder(diary, msg);
	
	printf("%s\n", sumD=summaryDiary(diary));

	printf("%s\n", sumC=summaryCodeArray(caray));

	ByteTripletArray_t* bytray = compressCode(caray);

	encryDecryByteTripletArray(bytray, key);

	releaseDiary(diary);
	releaseCodeArray(caray);

	free(sumD);
	free(sumC);

	diary = allocateDiary();

	encryDecryByteTripletArray(bytray, key);

	caray = uncompressCode(bytray);

	lzwDecoder(diary, caray);

	printf("%s\n", sumD = summaryDiary(diary));

	printf("%s\n", sumC = summaryCodeArray(caray));

	releaseDiary(diary);
	releaseCodeArray(caray);
	releaseByteTripletArray(bytray);
	free(sumD);
	free(sumC);

	system("pause");
	return 0;
}