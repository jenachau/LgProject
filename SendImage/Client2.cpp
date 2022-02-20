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

void receiveImage(){
    // message queue
	key_t key;
	int msgid;
    if ((key = ftok("progfile.txt", 70)) == -1) {
        printf("ftok");
        exit(1);
    }
     if ((msgid = msgget(key, PERMS | IPC_CREAT)) == -1) { 
            printf("msgget");
            exit(1);
    }
	msgrcv(msgid, &message, sizeof(message), 1, 0);

    // shared memory
    int *type= (int*) shmat(message.shmid_key, NULL, 0);
        if (*type != 0){
        ofstream image("img2.png", ios::out | ios::app);

        cout<<endl;
        int i = 0;
        while (type[i] >= 0)
        {
            cout<<type[i]<<" ";
            image.put(type[i]);  
            i++;     
        }
        
        image.close();
    }
}
int main()
{
    receiveImage();
}