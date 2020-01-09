#include "functions.h"

int main(int argc, char * argv[])
{
	int * shmid;
	int * semid;
	int * fileDescriptor;
	//printf("this is argv[0]: %s\n", argv[0]);
	if(!argv[1])
	{
		printf("please rerun the program and enter -c, -v, or -r after \"./control\"\n");
		return 0;
	}

	if(!strcmp(argv[1], "-c"))
	{
		createStory(shmid, semid, fileDescriptor);
		char someLine[100] = "things to do";
		printf("%s\n", someLine);
		printf("right before write\n");
		write(*fileDescriptor, someLine, 100);
		printf("right after write, before creation of story\n");
		char story[10000];
		printf("things\n");
		read(*fileDescriptor, story, 10);
		write(stdout, story, 10);
	}


	if(!strcmp(argv[1], "-v"))
	viewStory(fileDescriptor);

	if(!strcmp(argv[1], "-r"))
	removeStory(shmid, semid, fileDescriptor);

	if(!strcmp(argv[1], "-w"))
	writeStory(semid, fileDescriptor);

	return 0;
}
