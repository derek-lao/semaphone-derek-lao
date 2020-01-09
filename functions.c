#include "functions.h"

void createStory(int * shmid, int * semid, int * fileDescriptor)
{
	* shmid = shmget(SHMKEY, SIZE, IPC_CREAT | 0600);
	* semid = semget(SEMKEY, 1, IPC_CREAT | 0600);
	* fileDescriptor = open("story.txt", O_RDWR | O_CREAT | O_TRUNC , 0666);
	semctl(semid, 1, SETVAL);//only one person can access the story at a time
	printf("story created\n");
}

void removeStory(int * shmid, int * semid, int * fileDescriptor)
{
	int semval = shmctl(*shmid, GETVAL, 0);
	while(!semval)
	{//do nothing
	}
	// semctl(*semid, 0, SETVAL, semval - 1);//down the semaphore
	// semval--;

	struct sembuf sb;
	sb.sem_num = 0
	sb.sem_op = -1
	semop(semd, &sb, 1);

	shmctl(*shmid, IPC_RMID, 0);
	printf("shared memory removed\n");
	semctl(*semid, 0, IPC_RMID);
	printf("semaphore removed\n");
	char story[10000];
	viewStory(fileDescriptor);
	close(*fileDescriptor)
	printf("file closed, but not removed yet\n");

	sb.sem_op = 1;
	semop(semd, &sb, 1);

	// semctl(*semid, 0, SETVAL, semval + 1);//up the semaphore
	// semval++;
}

void viewStory(int * fileDescriptor)
{
	char story[10000];
	fgets(story, 10000, fileDescriptor);
	printf("%s\n", story);
}

void writeStory()
{
	int shmid = shmget(SHMKEY, SIZE, 0);
	int semid = semget(SEMKEY, 1, 0);
	printf("Last addition: ");
	int fileDescriptor = open("story.txt", O_RDWR | O_TRUNC, 0666);
	viewStory(fileDescriptor);
	int semval = semctl(*semid, 0, GETVAL);
	while(!semval)
	{//do nothing
	}
	// semctl(*semid, 0, SETVAL, semval - 1);//down the semaphore
	// semval --;

	struct sembuf sb;
	sb.sem_num = 0
	sb.sem_op = -1
	semop(semd, &sb, 1);

	printf("\nYour addition:");
	char story[10000];
	// read(stdin, story, 10000);
	// write(*fileDescriptor, story, 10000);
	// write(stdout, story, 10000);
	fgets(story, 10000, stdin);

	// semctl(*semid, 0, SETVAL, semval + 1);//up the semaphore
	// semval++;

	sb.sem_op = 1;
	semop(semd, &sb, 1);
}
