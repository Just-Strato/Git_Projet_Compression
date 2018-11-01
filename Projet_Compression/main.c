#include "global.h"
#include "bytes_array.h"
#include "code_array.h"
#include "lzw_coder.h"

int main(int argc, char* argv[]) {

	char msg[] = "Bacchanales Bacchus";

	Dictionary_t* diary = allocateDiary();

	CodeArray_t* caray = lzwCoder(diary, msg);
	
	printf("%s",summaryCodeArray(caray));

	system("pause");
	return EXIT_SUCCESS;
}