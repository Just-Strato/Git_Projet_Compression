#include "global.h"
#include "bytes.h"
#include "lzw_coder.h"

int server(const char* msg, const Byte_t key) {

	Dictionary_t *diary = allocateDiary();

	printf("SERVER : Server beginning ...\n");

	/*Fermeture de la sortie dans le père*/
	close(pipe_data[0]);

	printf("SERVER : Code by using message ...\n");
	lzwCoder(diary, msg, key);
	printf("SERVER : Code made.\n");

	printf("SERVER : Waiting for client's Confirmation ...\n");
	wait(NULL);
	printf("SERVER : Confirmation received.\n");

	releaseDiary(diary);

	return EXIT_SUCCESS;
}

int client(Byte_t key) {

	char c;char* sumD;
	
	printf("Display Dictionary ? (Y/N):\n");
	scanf("%c", &c);
	printf("CLIENT : Client beginning ...\n");

	/*Fermeture de l'entrée dans le fils*/
	close(pipe_data[1]);

	Dictionary_t *diary = allocateDiary();

	printf("CLIENT : Decoding the code ...\n");
	lzwDecoder(diary, key);
	printf("CLIENT : Code Decoded.\n");

	if(c == 'O' || c == 'o' || c == 'y' || c == 'Y') 
		printf("%s\n", sumD = summaryDiary(diary));

	releaseDiary(diary);
	free(sumD);

	printf("CLIENT : Confirmation send to server\n");
	return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {

	char*msg;
	Byte_t key;

	/*On vérifie que le tube est bien crée*/
	assert(pipe(pipe_data) == 0);

	/*On vérifie que le fils est bien crée*/
	assert((pid_son = fork()) != -1);

	/*Définition de la clef de cryptage*/
	if (argc >= 3)
		key = atoi(argv[2]);
	else
		key = 0b10100101;

	/*Si on est dans le père*/
	if (pid_son != 0) {

		/*Définition du message*/
		if (argc >= 2)
			msg = argv[1];
		else
			msg = "bacchanal bacchus";

		server(msg, key);
	}
	/*On est donc dans le fils*/
	else{
		client(key);
	}

	return EXIT_SUCCESS;
}