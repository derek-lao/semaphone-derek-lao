#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void createStory(int * shmid, int * semid, int * fileDescriptor);
void removeStory(int * shmid, int * semid, int * fileDescriptor);
void viewStory(int * fileDescriptor);

void writeStory(int * semid, int * fileDescriptor);
