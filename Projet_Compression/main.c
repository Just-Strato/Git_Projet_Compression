#include "global.h"
#include "bytes_array.h"
#include "code_array.h"
#include "lzw_coder.h"

int pid_son;
int pipe_data[2];
int sign = SIGNAL;

int server(const char* msg, const Byte_t key) {

	printf("Server beginning ...\n");

	/*Fermeture de la sortie dans le père*/
	close(pipe_data[0]);

	char *sumD, *sumC;

	Dictionary_t* diary = allocateDiary();

	printf("Code by using message ...\n");
	CodeArray_t* caray = lzwCoder(diary, msg);
	printf("Code made.\n");
	
	printf("%s\n", sumD = summaryDiary(diary));
	printf("%s\n", sumC = summaryCodeArray(caray));

	printf("Compressing the code ... \n");
	ByteTripletArray_t* bytray = compressCode(caray);
	printf("Code compressed.\n");

	printf("Encrypting the code ...\n");
	encryDecryByteTripletArray(bytray, key);
	printf("Code Encrypted.\n");
	
	printf("Signal to the client ...\n");
	write(pipe_data[1], sign, sizeof(sign));
	printf("Send.\n");

	printf("Waiting for client's Decrypt Confirmation ...\n");
	wait(NULL);
	printf("Confirmation received.\n");

	shmdt(bytray->array);
	shmdt(bytray);

	releaseDiary(diary);
	releaseCodeArray(caray);
	free(sumD);
	free(sumC);

	return EXIT_SUCCESS;
}

int client(Byte_t key) {

	printf("Client beginning ...\n");
	sleep(1);

	/*Fermeture de l'entrée dans le fils*/
	close(pipe_data[1]);

	Dictionary_t *diary = allocateDiary();

	ByteTripletArray_t* bytray;

	CodeArray_t* caray;

	char *sumD, *sumC;

	printf("Receptionning Server's Signal ...\n");
	read(pipe_data[0], sign, sizeof(sign));
	printf("Server's Signal received.\n");

	int byte_mem, byteArray_mem;

	byteArray_mem = shmget(BYTE_TRIPLET_MEM_KEY, sizeof(ByteTripletArray_t), IPC_CREAT | 0666); assert(byteArray_mem != -1);
	bytray = (ByteTripletArray_t*)shmat(byte_mem, NULL, 0); assert((int)bytray != -1);

	byte_mem = shmget(BYTE_TRIPLET_MEM_KEY, bytray->size * sizeof(ByteTriplet_t)
		, IPC_CREAT | 0666); assert(byte_mem != -1);

	bytray->array = (ByteTriplet_t*)shmat(byte_mem, NULL, 0); assert((int)bytray->array != -1);

	printf("Decrypting Code ...\n");
	encryDecryByteTripletArray(bytray, key);
	printf("Code Decrypted.\n");

	printf("Uncompressing the Code ...\n");
	caray = uncompressCode(bytray);
	printf("Code Uncompressed.\n");

	printf("Decoding the code ...\n");
	lzwDecoder(diary, caray);
	printf("Code Decoded.\n");

	printf("%s\n", sumD = summaryDiary(diary));
	printf("%s\n", sumC = summaryCodeArray(caray));

	shmdt(bytray->array);
	shmdt(bytray);

	releaseDiary(diary);
	releaseCodeArray(caray);
	releaseByteTripletArray(bytray);
	free(sumD);
	free(sumC);

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

	return EXIT_SUCCESS;
}