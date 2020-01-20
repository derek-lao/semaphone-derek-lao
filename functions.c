#include "functions.h"

void createStory(int * shmid, int * semid)
{
	printf("createStory called!\n");
	* shmid = shmget(SHMKEY, SIZE, IPC_CREAT | IPC_EXCL | 0644);
	* semid = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0644);
	printf("* shmid is: %d\n", *shmid);
	printf("* semid is: %d\n", *semid);
	printf("\n");
	int semidExistedBefore = 0;
	if(* shmid < 0)
	{
		printf("can't create shared memory, likely because a segment already exists\n");
		printf("error %d: %s\n", errno, strerror(errno));
		* shmid = shmget(SHMKEY, SIZE, 0644);
		printf("getting existing shmid: %d\n", *shmid);
		printf("\n");
	}
	if(* semid < 0)
	{
		printf("can't create semaphore (likely cause: semaphore already exists)\n");
		printf("error %d: %s\n", errno, strerror(errno));
		* semid = semget(SEMKEY, 1, 0644);
		printf("getting existing semid: %d\n", *semid);
		printf("\n");
		if(* semid >= 0)
			semidExistedBefore = 1;
	}
	int fileDescriptor = open("story.txt", O_RDWR | O_CREAT | O_EXCL | O_TRUNC , 0666);
	printf("file created called \"story.txt\"\n");

	if(fileDescriptor < 1)
	{
		printf("error, likely cause is that the file already exists");
		printf("error %d: %s\n", errno, strerror(errno));
		printf("\n");
	}

	if(!semidExistedBefore)
	{
		struct sembuf sb;
	        sb.sem_num = 0;
 	        sb.sem_op = 1;
	        semop(* semid, &sb, 1);
	        int semval = semctl(*semid, 0, GETVAL, 0);
        	printf("semaphore upped to have a value of %d\n", semval);
	}
	else
	{
		printf("semaphore existed before, was not changed\n");
		int semval = semctl(*semid, 0, GETVAL, 0);
		//if(semval < 1)
		//{
		//	struct sembuf sb;
		//	sb.sem_num = 0;
		//	sb.sem_op = 1;
		//	semop(* semid, &sb, 1);
                //}
		//semval = semctl(*semid, 0, GETVAL, 0);
		printf("semaphore has a value of %d\n", semval);
	}
	printf("\n");
	printf("If you had tried to create a new game but errors came up saying that a game already exists, please call\n\"./control -r\" to remove everything, and then call\n\"./control -c\" again\n");
}

void removeStory(int * shmid, int * semid)
{
	*shmid = shmget(SHMKEY, SIZE, 0644);
	*semid = semget(SEMKEY, 1, 0);
	int semval = semctl(*semid, 0,  GETVAL, 0);
	if(semval < 0)
	{
		printf("error in getting semval\n");
   		printf("error %d: %s\n", errno, strerror(errno));
	}
	printf("semval is %d\n", semval);
	printf("trying to get in...");
	struct sembuf sb;
        sb.sem_num = 0;
        sb.sem_op = -1;
        semop(*semid, &sb, 1);
	printf("successfully got in!\n");

	int fileDescriptor = open("story.txt", O_RDWR | O_TRUNC , 0666); 

	if(fileDescriptor < 0)
	{
		printf("error %d: %s\n", errno, strerror(errno));
		printf("error, no file found?\n");
	}

	viewStory();
	shmctl(*shmid, IPC_RMID, 0);
	printf("shared memory removed\n");
	semctl(*semid, 0, IPC_RMID);
	printf("semaphore removed\n");

	if(fileDescriptor >= 0)
	{
		close(fileDescriptor);
		printf("file closed, but not removed yet\n");
	}
	if(remove("story.txt"))
	{
		printf("error, can't remove file\n");
		printf("error %d: %s\n", errno, strerror(errno));
	}
	else
		printf("file removed\n");
}

void viewStory()
{
        int fileDescriptor = open("story.txt", O_RDONLY, 0666);
	//FILE * fileStream = fdopen(fileDescriptor, "r");
        char story[10000];
        if(fileDescriptor < 0)
	{
                printf("error, no file found?\n");
		printf("error %d: %s\n", errno, strerror(errno));
	}
	//fgets(story, 10000, fileStream);
	read(fileDescriptor, story, 10000);
	printf("The story so far:\n%s\n", story);
}

void writeStory()
{
	int semid = semget(SEMKEY, 1, 0);

	if(semid < 0)
	{
		printf("error %d: %s\n", errno, strerror(errno));
	}

	int fileDescriptor = open("story.txt", O_WRONLY | O_APPEND);
	int semval = semctl(semid, 0, GETVAL, 0);
	printf("semval is %d\n", semval);
	//while(!semval)
	//{
	//	printf("Waiting for file to be available...\n");
	//	semval = semctl(semid, 0, GETVAL, 0);
	//}

        if(semval < 0)
	{
                printf("error in getting semval\n");
		printf("error %d: %s\n", errno, strerror(errno));
	}
	//file is available!

	printf("trying to get in...\n");
	struct sembuf sb;
        sb.sem_num = 0;
        sb.sem_op = -1;
        semop(semid, &sb, 1);
	printf("successfully got in!\n");


	int shmid = shmget(SHMKEY, SIZE, 0);
	char * story = shmat(shmid, 0, 0);

        if((*story) < 0)
                printf("Error\n");
        else
        {
                printf("Last addition: %s\n", story);
        }
	printf("semval is %d\n", semval);
	printf("\nYour addition:");
	fgets(story, SIZE, stdin);
	int length = strlen(story);
	write(fileDescriptor, story, length);
	close(fileDescriptor);
	shmdt(story);
	sb.sem_op = 1;
	semop(semid, &sb, 1);
}
