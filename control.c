#include "functions.h"

int main()
{
	createStory();
	return 0;
}

void createStory()
{
	printf("story created\n");
	int shmid;
	int semid;
	int fileDescriptor;
	shmid = shmget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
	semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
	fileDescriptor = open("story.txt", O_RDWR | O_CREAT | O_TRUNC , 0666);
	semctl(semid, 1, SETVAL);//only one person can access the story at a time
}

void removeStory(int shmid, int semid, int fileDescriptor)
{
	int semval = shmctl(shmid, GETVAL, 0);
	while(!semval)
	{//do nothing
	}
	semctl(semid, 0, SETVAL, semval - 1);//down the semaphore
	semval--;
	shmctl(shmid, IPC_RMID, 0);
	semctl(semid, 0, IPC_RMID);
	char story[10000];
	read(fileDescriptor, story, 10000);
	write(stdout, story, 10000);
	semctl(semid, 0, SETVAL, semval + 1);//up the semaphore
	semval++;
}

void viewStory(int fileDescriptor)
{
	char story[10000];
	read(fileDescriptor, story, 10000);
	write(stdout, story, 10000);
}
