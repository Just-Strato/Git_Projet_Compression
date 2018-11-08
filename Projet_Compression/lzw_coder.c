#include "global.h"
#include "lzw_coder.h"
#include "bytes.h"


Dictionary_t* allocateDiary() {

	Dictionary_t* diary = (Dictionary_t*)malloc(sizeof(Dictionary_t)); assert(diary != NULL);

	/*Allocation du tableau de pointeur*/
	diary->words = (char**)malloc(DIARY_MAX_SIZE * sizeof(char*)); assert(diary->words != NULL);
	
	diary->size = 0; //dictionnaire sans valeur donc vide

	return diary;
}

unsigned int releaseDiary(Dictionary_t* diary) {
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
	unsigned int i;

	/*Si c'est un caractère il est dans la table ASCI*/
	if (strlen(word) == 1)
		return *word;

	/*Pour chaque mots on test l'équivalence*/
	for (i = 0; i < diary->size; i++) {

		/*Si egale ( donc strcmp retourne 0) alors
		on retourne l'indice + 256 (table ASCII) */
		if (!strcmp(diary->words[i], word)) {
			return i+256;
		}
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

	strcpy(str, word);

	/*on ajoute le mot au bout du dictionnaire et on incrémente la taille*/
	diary->words[diary->size++] = str;

	return diary->size - 1;
}

char* summaryDiary(const Dictionary_t* diary) {
	char* sary;
	static unsigned int size = 0, i;

	/*On calcule la taille du résumé en additionnant chaque carac de chaque mot
	+1 pour un retour chariot*/
	for (i = 0; i < diary->size; i++)
		size += strlen(diary->words[i])+1;

	/*Le fameux \0 et permettre de mettre \n dans la boucle*/
	size+=2;

	sary = (char*)malloc(size * sizeof(char));

	strcpy(sary, "");

	for (i = 0; i < diary->size; i++) {
		strcat(sary, diary->words[i]);
		strcat(sary, "\n");
	}

	return sary;
}

void lzwCoder(Dictionary_t* diary, const char* msg, Byte_t key) {

	int unsigned k, lgth, msgSize = strlen(msg), initDiary = 0;
	int code[2] = { -1,-1 };

	/*Si NULL est entrée à la place du dictionnaire, on l'initialise
	et on le libère*/
	if (diary == NULL) {
		initDiary++;
		diary = allocateDiary();
	}

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
				addSend(code, diary, s, key);

			//S devient C
			s[0] = c;
			s[1] = '\0';

		}
	}

	if (strcmp(s, "")) {
		if (code[0] != -1)
			secureSending(code[0], 0, key);
	}

	/*on libère le dictionnaire si initialisé dans la fonction*/
	if (initDiary)
		releaseDiary(diary);
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
	char s[DIARY_MAX_SIZE] = { '\0' };
	unsigned int c, k, i, initDiary = 0, size;

	/*Si NULL est entrée à la place du dictionnaire, on l'initialise
	et on le libère*/
	if (diary == NULL) {
		initDiary++;
		diary = allocateDiary();
	}

	for (k = 0; k < caray->size; k++) {

		c = caray->codes[k];

		if (c < 256) {
			printf("%c", c);
			findOrAddWord(diary, s, c);
		}

		else {
			word = diary->words[c - 256];

			size = strlen(word);

			for (i = 0; i < size; i++) {
				printf("%c", word[i]);
				findOrAddWord(diary, s, word[i]);
			}
		}
	}

	/*Libération du Dico initialisé dans la fonction*/
	if (initDiary)
		releaseDiary(diary);
}