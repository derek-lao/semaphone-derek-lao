#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

void * create(key_t key, sem_t sem, 
