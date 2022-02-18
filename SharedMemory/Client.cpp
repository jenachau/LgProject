#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define MAXSIZE 27

int main()
{
    int shmid1;
    key_t key1;
    int *type;

    key1 = 86;

    shmid1=shmget(key1, MAXSIZE, IPC_CREAT | 0666);

    type= (int*) shmat(shmid1, NULL, 0);  

    ifstream image("img.png", ios::in | ios::binary);
    int ch;
    int i = 0;
    while(!image.eof()){
        type[i] = image.get();
        i++;
    }
    image.close();

    exit(0);
}