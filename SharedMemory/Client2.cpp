#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#define MAXSIZE 27

int main()
{
    int shmid1;
    key_t key1;
    char *type;

    key1 = 3;
    shmid1=shmget(key1, MAXSIZE, IPC_CREAT | 0666);


    type= (char*) shmat(shmid1, NULL, 0);  

    printf("Text is : %s\n",type);


    exit(0);
}