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
    char *type;

    key1 = 3;

    shmid1=shmget(key1, MAXSIZE, IPC_CREAT | 0666);

    type= (char*) shmat(shmid1, NULL, 0);  

    ifstream image("img.png", ios::in | ios::binary);

    char ch;
    while(!image.eof()){
        ch = char(image.get());
        strcat(type, &ch);
    }
    cout<<"Image successfully converted into binary File"<<endl;
    image.close();
    printf("Text is : %s",type);

    exit(0);
}