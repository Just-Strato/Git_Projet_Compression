#include "global.h"
#include "code_array.h"


CodeArray_t* allocateCodeArray() {

	CodeArray_t* caray = (CodeArray_t*)malloc(DEFAULT_CODE_SIZE * sizeof(unsigned int)); assert(caray != NULL);
	caray->size = 0;
	caray->capacity = DEFAULT_CODE_SIZE;

	return caray;
}

unsigned int addCode(CodeArray_t* caray, const int code) {

	if (caray->size == caray->capacity) {
		caray->capacity += DEFAULT_CODE_SIZE;
		caray->codes = (unsigned int*)realloc(caray->codes, caray->capacity * sizeof(unsigned int)); assert(caray != NULL);
	}

	caray->codes[caray->size++] = code;

	return caray->size - 1;
}

char* summaryCodeArray(const CodeArray_t* caray) {

	char* sary, str[BUFSIZ];
	static unsigned int size = 0, i;

	/*On calcule la taille du résumé en additionnant chaque carac de chaque entié
	 pour un retour chariot*/
	for (i = 0; i < caray->size; i++)
		size += sprintf_s(str, sizeof(str), "%d, ", caray->codes[i]);

	/*'{', ']', fameux \0 et permettre de mettre \n dans la boucle*/
	size += 4;

	sary = (char*)malloc(size * sizeof(char));
	strcpy_s(str, sizeof(str), "{");

	for (i = 0; i < caray->size; i++) {

		if (i % 7 == 0)
			sprintf_s(str, sizeof(str), "%d,\n", caray->codes[i]);
		else
			sprintf_s(str, sizeof(str), "%d, ", caray->codes[i]);

		strcat_s(sary, size, str);
	}

	strcat_s(sary, size, "}\n");

	return sary;
}