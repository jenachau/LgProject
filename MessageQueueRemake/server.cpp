// C Program for Message Queue (Reader Process)
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX 50
#define PERMS 0644
#define SEVER_ID '999'

// structure for message queue
struct mesg_buffer {
	long mesg_type;
    char mesg_text[100];
    char send_key;
    char name[20];
} message;

int main()
{
    while(1){
        key_t key;
        int msgid;

        // Receive message
        if ((key = ftok("progfile.txt", SEVER_ID)) == -1) {
            printf("ftok");
            exit(1);
        }

        // printf("server key to receive: %d\n", key);
        if ((msgid = msgget(key, PERMS | IPC_CREAT)) == -1) { 
            printf("msgget");
            exit(1);
        }
        // msgrcv to receive message

        msgrcv(msgid, &message, sizeof(message), 1, 0);

        // display the message
        printf("Data Received form %s is : %s \n",message.name, message.mesg_text);

        // key to identifi recevier
        char sendKey = message.send_key;

        // Send message
        if ((key = ftok("progfile.txt", sendKey)) == -1) {
            printf("ftok");
            exit(1);
        }
        // printf("server key to send: %d\n", key);

        message.mesg_type = 1;

        char mess[100];
        // strcpy(mess, message.mesg_text);

        if ((msgid = msgget(key, PERMS | IPC_CREAT)) == -1) { 
            printf("msgget");
            exit(1);
        }
        if (message.send_key=='1') strcpy(mess,"Thu Chau");
        else strcpy(mess,"Thi Tran");
        // strcpy(message.mesg_text, mess);
        // msgsnd to send message
        msgsnd(msgid, &message, sizeof(message), 0);

        // display the message
        printf("Data send to %s \n", mess);
    }
    return 0;
}

