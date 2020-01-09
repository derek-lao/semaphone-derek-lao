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

#define SHMKEY 123
#define SEMKEY 456
#define SIZE 1024

union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO
                              (Linux-specific) */
};

void createStory(int * shmid, int * semid, int * fileDescriptor);
void removeStory(int * shmid, int * semid, int * fileDescriptor);
void viewStory(int * fileDescriptor);

void writeStory();
