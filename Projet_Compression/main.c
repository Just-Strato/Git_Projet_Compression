#include "global.h"
#include "bytes.h"
#include "lzw_coder.h"

int server(const char* msg, const Byte_t key) {

	Dictionary_t *diary = allocateDiary();

	printf("Server beginning ...\n");

	/*Fermeture de la sortie dans le père*/
	close(pipe_data[0]);

	char *sumD;

	printf("Code by using message ...\n");
	lzwCoder(diary, msg, key);
	printf("Code made.\n");
	
	printf("%s\n", sumD = summaryDiary(diary));

	printf("Waiting for client's Confirmation ...\n");
	wait(NULL);
	printf("Confirmation received.\n");

	releaseDiary(diary);
	free(sumD);

	return EXIT_SUCCESS;
}

int client(Byte_t key) {

	printf("Client beginning ...\n");

	/*Fermeture de l'entrée dans le fils*/
	close(pipe_data[1]);

	Dictionary_t *diary = allocateDiary();

	char *sumD;

	printf("Decoding the code ...\n");
	lzwDecoder(diary, key);
	printf("Code Decoded.\n");

	printf("%s\n", sumD = summaryDiary(diary));

	releaseDiary(diary);
	free(sumD);

	printf("Confirmation send to server");
	return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {

	char*msg;
	Byte_t key;

	/*On vérifie que le tube est bien crée*/
	assert(pipe(pipe_data) == 0);

	/*On vérifie que le fils est bien crée*/
	assert((pid_son = fork()) != -1);

	/*Si on est dans le père*/
	if (pid_son != 0) {

		/*Définition du message*/
		if (argc >= 2)
			msg = argv[1];
		else
			msg = "bacchanal bacchus";

		/*Définition de la clef de cryptage*/
		if (argc >= 3)
			key = atoi(argv[2]);
		else
			key = 0b10100101;

		server(msg, key);
	}
	/*On est donc dans le fils*/
	else{
		client(key);
	}

	system("pause");
	return EXIT_SUCCESS;
}