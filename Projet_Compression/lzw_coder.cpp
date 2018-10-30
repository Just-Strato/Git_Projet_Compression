#include "lzw_coder.h"

Dictionary_t* allocatediary() {

	Dictionary_t* diary = (Dictionary_t*)malloc(sizeof(Dictionary_t)); assert(diary != NULL);

	/*Allocation du tableau de pointeur*/
	diary->words = (char**)malloc(DIARY_MAX_SIZE * sizeof(char*)); assert(diary->words != NULL);
	
	diary->size = 0; //dictionnaire sans valeur donc vide

	return diary;
}

unsigned int releasediary(Dictionary_t* diary) {
	static unsigned int i;

	/*On libère tout les mots*/
	for (i = 0; i < diary->size; i++)
		free(diary->words[i]);

	/*Puis le tableau de pointeur sur mot*/
	free(diary->words);

	/*et pour finir le dictionnaire en lui même*/
	free(diary);

	return i;
}

int findWord(const Dictionary_t* diary, const char* word) {
	static unsigned int i;

	/*Si c'est un caractère il est dans la table ASCI*/
	if (strlen(word) == 1)
		return 0;

	/*Pour chaque mots on test l'équivalence*/
	for (i = 0; i < diary->size; i++) {

		/*Si egale ( donc strcmp retourne 0) */
		if (!strcmp(diary->words[i], word))
			return i;
	}

	/*Si on est arrivé la, alors on a pas trouvé la valeur dans le tableau*/
	return NOT_INSIDE;
}

int addWord(Dictionary_t* diary, const char* word) {
	char* str;
	int size;

	/*Si on a déjà atteint la taille max du dico on passe*/
	if (diary->size == DIARY_MAX_SIZE)
		return NOT_INSIDE;

	size = strlen(word) + 1;

	/*str aura autant de caractere que word +1 pour le '\0'*/
	str = (char*)malloc(size * sizeof(char)); assert(str != NULL);

	strcpy_s(str, size, word);

	/*on ajoute le mot au bout du dictionnaire et on incrémente la taille*/
	diary->words[diary->size++] = str;

	return diary->size - 1;
}

char* summarydiary(const Dictionary_t* diary) {
	char* sary;
	static unsigned int size = 0, i;

	/*On calcule la taille du résumé en additionnant chaque carac de chaque mot
	+1 pour un retour chariot*/
	for (i = 0; i < diary->size; i++)
		size += strlen(diary->words[i] + 1);

	/*Le fameux \0 et permettre de mettre \n dans la boucle*/
	size+=2;

	sary = (char*)malloc(size * sizeof(char));

	for (i = 0; i < diary->size; i++) {
		strcat_s(sary, size, diary->words[i]);
		strcat_s(sary, size, "\n");
	}

	return sary;
}

CodeArray_t* lzwCoder(Dictionary_t* diary, const char* msg) {

	int unsigned code = 0, k, lgth, msgSize = strlen(msg);


	CodeArray_t* caray = allocateCodeArray(); assert(caray != NULL);

	/** Dans le pire des cas s atteindra la taille 
			du nombre de motdans le dico*/
	char c, s[DIARY_MAX_SIZE] = "\0";

	for (k = 0; k < msgSize; k++) {
		c = msg[k];
		lgth = strlen(s);

		//S=S+C
		s[lgth] = c;
		s[lgth + 1] = '\0';

		if (findWord(diary, s) == NOT_INSIDE) {
			addWord(diary, s);

			//retirer C
			s[lgth] = '\0';

			//on recupère le code de S
			if (strcmp(s, ""))
				caray->codes[caray->size++] = findWord(diary, s);

			//S devient C
			s[0] = c;
			s[1] = '\0';

		}
	}

	if (strcmp(s, ""))
		caray->codes[caray->size++] = findWord(diary, s);

	return caray;

}

int findOrAddWord(Dictionary_t* diary, char* word, char c) {

	int i, size = strlen(word);

	word[size] = c;
	word[size + 1] = '\0';

	if (findWord(diary, word) == NOT_INSIDE) {

		//On ajoute S+C au dico
		i = addWord(diary, word);

		//S devient c
		word[0] = c;
		word[1] = '\0';

		return i;
	}
	
	return NOT_INSIDE;
}

void lzwDecoder(Dictionary_t* diary, const CodeArray_t* caray) {

	char* word;
	char s[DIARY_MAX_SIZE] = "\0";
	unsigned int c, k, i, lgth = 0;

	for (k = 0; k < caray->size; k++) {

		c = caray->codes[k];

		if (c < 256) {
			printf("%c", c);
			findOrAddWord(diary, s, c);
			lgth++;
		}

		else {
			word = diary->words[c - 256];
			lgth += strlen(word);

			for (i = 0; i < strlen(word); i++) {
				printf("%c", word[i]);
				findOrAddWord(diary, s, word[i]);
			}
		}
	}
	printf("\nMessage Original de longueur %d\n", lgth);
}