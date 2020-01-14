#include "functions.h"

int main(int argc, char * argv[])
{
	int shmid;
	int semid;
	//printf("this is argv[0]: %s\n", argv[0]);
	if(!argv[1])
	{
		printf("please rerun the program and enter -c, -v, or -r after \"./control\"\n");
		return 0;
	}

	if(!strcmp(argv[1], "-c"))
	{
		createStory(&shmid, &semid);
	}


	if(!strcmp(argv[1], "-v"))
	viewStory();

	if(!strcmp(argv[1], "-r"))
	removeStory(&shmid, &semid);

	return 0;
}
