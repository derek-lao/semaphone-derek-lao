#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

void create();
void remove(int shmid, int semid, int fileDescriptor);
void view(int fileDescriptor);

void write(int semid, int fileDescriptor);
