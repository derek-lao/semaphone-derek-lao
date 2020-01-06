#include <stdlib.h>
#include <stdio.h>
#include <functions.h>

void create()
{
	int shmid;
	int semid;
	int fileDescriptor;
	shmid = shmget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
	semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
	fileDescriptor = semget("story.txt", O_RDWR | O_CREAT | O_TRUNC , 0666);
//still need to set value of semaphore
}

void remove(int shmid, int semid, int fileDescriptor)
{
	shmctl(shmid, IPC_RMID, 0);
	semctl(semid, IPC_RMID, 0);
//still need to display contents
//still need to wait for until semaphore is available
}

void view(int fileDescriptor)
{
	char story[10000];
	read(fileDescriptor, story, 10000);
	write(stdout, story, 10000);
}
