#include <stdlib.h>
#include <stdio.h>
#include <functions.h>

void create()
{
	int shmid;
	int semaid;
	int fileDescriptor;
	shmid = shmget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
	semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);

}
