#include "functions.h"

void createStory(int * shmid, int * semid)
{
	printf("createStory called!\n");
	* shmid = shmget(SHMKEY, SIZE, IPC_CREAT| IPC_EXCL | 0644);
	printf("shmid was maybe okay\n");
	* semid = semget(SEMKEY, 1, IPC_CREAT| IPC_EXCL | 0644);
	printf("semid was maybe okay\n");
	if(shmid < 0)
		printf("can't create shared memory\n");
	if(semid < 0)
		printf("can't create semaphore\n");
	open("story.txt", O_RDWR | O_CREAT | O_TRUNC , 0666);
	semctl(* semid, 1, SETVAL);//only one person can access the story at a time
	printf("file created called \"story.txt\"\n");
}

void removeStory(int * shmid, int * semid)
{
	int semval = shmctl(*shmid, GETVAL, 0);
	while(semval >= 0)
	{//do nothing
		printf("can not be removed yet, file is being used\n");
		semval = semctl(*semid, 0, GETVAL);
	}

	if(semval < 0)
		printf("error in getting semval\n");

	int fileDescriptor = open("story.txt", O_RDWR | O_TRUNC , 0666); 

	if(fileDescriptor < 0)
		printf("error, no file found?\n");

	struct sembuf sb;
	sb.sem_num = 0;
	sb.sem_op = -1;
	semop(*semid, &sb, 1);

	shmctl(*shmid, IPC_RMID, 0);
	printf("shared memory removed\n");
	semctl(*semid, 0, IPC_RMID);
	printf("semaphore removed\n");
	viewStory();

	if(fileDescriptor >= 0)
	{	close(fileDescriptor);
		printf("file closed, but not removed yet\n");
	}
	if(remove("story.txt"))
		printf("error, can't remove file\n");
	else
		printf("file removed\n");
}

void viewStory()
{
	int shmid = shmget(SHMKEY, SIZE, 0644);
        int fileDescriptor = open("story.txt", O_RDONLY, 0666);
	FILE * fileStream = fdopen(fileDescriptor, "r");
        char * story = shmat(shmid, 0, 0);

        if(fileDescriptor < 0)
                printf("error, no file found?\n");

	fgets(story, 1024, fileStream);
	printf("The story so far:\n %s\n", story);
}

void writeStory()
{
	int semid = semget(SEMKEY, 1, 0);
	int fileDescriptor = open("story.txt", O_WRONLY | O_APPEND);
	FILE * fileStream = fdopen(fileDescriptor, "w");
	printf("got up to here?\n");
	int semval = semctl(semid, 0, GETVAL);
	printf("semval is %d\n", semval);
	while(semval >= 0)
	{
		printf("Waiting for file to be available...\n");
		semval = semctl(semid, 0, GETVAL);
	}

        if(semval < 0)
                printf("error in getting semval\n");

	//file is available!

	struct sembuf sb;
        sb.sem_num = 0;
        sb.sem_op = -1;
        semop(semid, &sb, 1);

	int shmid = shmget(SHMKEY, SIZE, 0);
	char * story = shmat(shmid, 0, 0);

        if((*story) < 0)
                printf("Error\n");
        else
        {
		fgets(story, 1024, fileStream);
                printf("Last addition: %s\n", story);
        }
	printf("semval is %d\n", semval);
	printf("\nYour addition:");
	fgets(story, SIZE, stdin);
	write(fileDescriptor, story, SIZE);
	close(fileDescriptor);
	shmdt(story);
	sb.sem_op = 1;
	semop(semid, &sb, 1);
}
