#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_SIZE 1024

typedef struct
{
    int ready;
    char data[SHM_SIZE - sizeof(int)];
} shared_data;

int main()
{
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    shared_data *shm = (shared_data *)shmat(shmid, NULL, 0);

    shm->ready = 0;

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0)
    {
        printf("Child: Waiting for parent to write data...\n");
        while (shm->ready == 0)
        {
            sleep(1);
        }

        printf("Child: Reading from shared memory: %s\n", shm->data);

        strcpy(shm->data, "Hello from child process!");
        shm->ready = 2;

        shmdt(shm);
        exit(0);
    }
    else
    {
        strcpy(shm->data, "Hello from parent process!");
        shm->ready = 1;

        printf("Parent: Wrote to shared memory and waiting for child to read...\n");

        while (shm->ready != 2)
        {
            sleep(1);
        }

        printf("Parent: Reading from shared memory: %s\n", shm->data);

        wait(NULL);

        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);

        return 0;
    }
}