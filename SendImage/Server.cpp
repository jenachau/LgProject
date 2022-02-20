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

#define MAX 50
#define PERMS 0644
#define SEVER_ID '999'

// structure for message queue
struct mesg_buffer {
	long mesg_type;
    int shmid_key;
} message;

int main()
{
    
        key_t key;
        int msgid;

        // Receive message
        if ((key = ftok("progfile.txt", 65)) == -1) {
            printf("ftok");
            exit(1);
        }

        if ((msgid = msgget(key, PERMS | IPC_CREAT)) == -1) { 
            printf("msgget");
            exit(1);
        }
        // msgrcv to receive message

        msgrcv(msgid, &message, sizeof(message), 1, 0);

        // Send message
        if ((key = ftok("progfile.txt", 70)) == -1) {
            printf("ftok");
            exit(1);
        }
        if ((msgid = msgget(key, PERMS | IPC_CREAT)) == -1) { 
            printf("msgget");
            exit(1);
        }

        // msgsnd to send message
        msgsnd(msgid, &message, sizeof(message), 0);
    return 0;
}