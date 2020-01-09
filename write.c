#include "functions.h"

int main(int argc, char * argv[])
{
	int * semid;
	int * fileDescriptor;
	writeStory(semid, fileDescriptor);
	return 0;
}
