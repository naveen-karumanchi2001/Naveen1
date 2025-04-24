//SHAREDMEM.H FILE
#ifndef SHAREDMEM_H
#define SHAREDMEM_H
 
#include <sys/types.h>
 
// Key used to identify shared memory segment
#define SHM_KEY 0x1234
 
// Key used to identify the semaphore set
#define SEM_KEY 0x5678
 
// Maximum length for messages passed between processes
#define MAX_MESSAGE_LEN 256
 
// Structure to hold the shared data
typedef struct {
    char message[MAX_MESSAGE_LEN];
} SharedData;
 
#endif
