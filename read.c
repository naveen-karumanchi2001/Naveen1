#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <unistd.h>
#include "Sharedmem.h"
int main() {
    int shmid = shmget(SHM_KEY, sizeof(SharedData), 0666);

    SharedData *data = (SharedData *)shmat(shmid, NULL, 0);
    int semid = semget(SEM_KEY, 1, 0666);
    struct sembuf lock = {0, -1, 0};
 
    struct sembuf unlock = {0, 1, 0};
 
    // Lock semaphore before accessing shared memory
    semop(semid, &lock, 1);
 
    // Read the message from shared memory
    char received[MAX_MESSAGE_LEN];
    strncpy(received, data->message, MAX_MESSAGE_LEN);
 
    // Unlock semaphore after reading
    semop(semid, &unlock, 1);
 
    // Print received message
    printf("Received: %s\n", received);
 
    // Log to the shared log file
    FILE *ptr = fopen("shmem.txt", "a");
    fprintf(ptr, "Process ID: %d: %s\n", getpid(), received);
    fclose(ptr);

    shmdt(data);
 
    return 0;
}
 
