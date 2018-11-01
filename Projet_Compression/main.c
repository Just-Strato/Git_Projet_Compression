#include "global.h"
#include "bytes_array.h"
#include "code_array.h"
#include "lzw_coder.h"

int main(int argc, char* argv[]) {

	char msg[] = "Bacchanales Bacchus", *sumD, *sumC;
	Byte_t key=0x11111111;

	Dictionary_t* diary = allocateDiary();

	CodeArray_t* caray = lzwCoder(diary, msg);
	
	printf("%s\n", sumD = summaryCodeArray(diary));

	printf("%s\n", sumC=summaryCodeArray(caray));

	ByteTripletArray_t* bytray = compressCode(caray);

	//encryDecryByteTripletArray(bytray, key);

	releaseDiary(diary);
	releaseCodeArray(caray);
	releaseByteTripletArray(bytray);

	free(sumD);
	free(sumC);

	system("pause");
	return EXIT_SUCCESS;
}