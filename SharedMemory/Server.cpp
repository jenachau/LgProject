#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
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

    ofstream image("img2.png", ios::out | ios::binary);

    int i = 0;
    while (type[i] >= 0)
    {
        cout<<type[i];
        image.put(type[i]);  
        i++;     
    }
    
    image.close();

    exit(0);
}