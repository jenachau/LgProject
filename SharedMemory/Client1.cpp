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
key_t key_receive = 222222;

void sendImage(){
    int shmid;
    int *type;

    if ((shmid=shmget(key_send, MAXSIZE, IPC_CREAT | 0666)) == -1){
        cout<<"error\n";
        exit(1);
    }

    type= (int*) shmat(shmid, NULL, 0);  

    ifstream image("img.png", ios::in | ios::binary);
    int ch;
    int i = 0;
    while(!image.eof()){
        type[i] = image.get();
        i++;
    }
    image.close();
}

void receiveImage(){
    int shmid;
    int *type;

    if ((shmid=shmget(key_receive, MAXSIZE, IPC_CREAT | 0666)) == -1){
        cout<<"error\n";
        exit(1);
    }
    type= (int*) shmat(shmid, NULL, 0); 
    if (type == NULL ){
      ofstream image("img2.png", ios::out | ios::binary);

        int i = 0;
        while (type[i] >= 0)
        {
            image.put(type[i]);  
            i++;   

        }
    
        image.close();      
    }

}
int main()
{
    while(1){
        sendImage();
        receiveImage();
    }



    exit(0);
}