// C Program for Message Queue (Writer Process)
#include <sys/msg.h>
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
#define MAX 10
#define PERMS 0644

// structure for message queue
struct mesg_buffer {
	long mesg_type;
    int shmid_key;
} message;

void sendImage(){
    //message queue
	key_t key;
    int msgid;
    if ((key = ftok("progfile.txt", 65)) == -1) {
        printf("ftok");
        exit(1);
    }
     if ((msgid = msgget(key, PERMS | IPC_CREAT)) == -1) { 
            printf("msgget");
            exit(1);
    }


	message.mesg_type = 1;

    // shared memory
    int shmid1;
    int *type;
    key_t key1;
    key1 = 100;
    shmid1=shmget(key1, 27, IPC_CREAT | 0666);
    message.shmid_key = shmid1;

    type= (int*) shmat(shmid1, NULL, 0);
    ifstream image("img.png", ios::in | ios::binary);
    cout<<endl;
    int i = 0;
    while(!image.eof()){
        cout<<type[i]<<" ";
        type[i] = image.get();
        i++;
    }
    image.close();
    // msgsnd to send message
	msgsnd(msgid, &message, sizeof(message), 0);
}


int main()
{
    sendImage();
	return 0;
}