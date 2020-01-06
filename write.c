#include "functions.h"

void write(int semid, int fileDescriptor)
{
	printf("Last addition: ");
	read(fileDescriptor);
	semval = semctl(semid, 0, GETVAL); 
	while(!semval)
	{//do nothing
	}
	semctl(semid, 0, SETVAL, semval - 1);//down the semaphore
	semval --;
	printf("\nYour addition: );
	char story[10000];
	read(stdin, story, 10000);
	write(fileDescriptor, story, 10000);
	write(stdout, story, 10000);
	semctl(semid, 0, SETVAL, semval + 1);//up the semaphore
	//semval++;
}
