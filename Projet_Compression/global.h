#ifndef DEF_GLOBAL
#define DEF_GLOBAL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define NOT_INSIDE -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define DIARY_MAX_SIZE 4096-256

#define false  0 
#define true  1

#define DEFAULT_CODE_SIZE 100	//nombre par défaut de code, si dépassé ajoute ce nombre
								// de code en plus 
#define BYTE_TRIPLET_MEM_KEY 1234					//Clef de l'emplacement mémoire partagée
#define BYTE_TRIPLET_ARRAY_MEM_KEY 5678

#define SIGNAL 1;

#endif
