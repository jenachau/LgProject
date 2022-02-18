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

key_t key_send = 1111111;
key_t key_receive = 33333;

void sendImage(){
    int shmid;
    int *type;

    if ((shmid=shmget(key_send, MAXSIZE, IPC_CREAT | 0666)) == -1){
        cout<<"error\n";
        exit(1);
    }

    type= (int*) shmat(shmid, NULL, 0);  
    if (type[0] >= 0){
    ifstream image("img.png", ios::in | ios::binary);
    int ch;
    int i = 0;
    while(!image.eof()){
        type[i] = image.get();
        i++;
    }
    image.close();
    }

}

void receiveImage(){
    int shmid;
    int *type2;

    if ((shmid=shmget(key_receive, MAXSIZE, IPC_CREAT | 0666)) == -1){
        cout<<"error\n";
        exit(1);
    }
    type2 = (int*) shmat(shmid, NULL, 0); 
    int i =0;
    while (type2[i] >= 0)
    {
        cout<<type2[i]<<" ";
        i++;     
    }
    ofstream image("img3.png", ios::out | ios::binary);

    i = 0;
    while (type2[i] >= 0)
    {
        image.put(type2[i]);  
        i++;     
    }
    
    image.close();
}
int main()
{
    
        sendImage();
        receiveImage();
    

    exit(0);
}