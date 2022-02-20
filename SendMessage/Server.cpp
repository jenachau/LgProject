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
    int send_key;
    char name[20];
} message;

int main()
{
    while(1){
        key_t key,keyBack;
        int msgid;
        int sendkeyBack;
        // Receive message
        if ((key = ftok("progfile.txt", SEVER_ID)) == -1) {
            printf("ftok");
            exit(1);
        }

        if ((msgid = msgget(key, PERMS | IPC_CREAT)) == -1) { 
            printf("msgget");
            exit(1);
        }
        // msgrcv to receive message

        msgrcv(msgid, &message, sizeof(message), 1, 0);
        
        // display the message
        printf("Data Received is : %s", message.mesg_text);
        if (strcmp(message.mesg_text,"123")==0){
            printf("dm m");
        }
        // key to identifi recevier
        int sendKey = message.send_key;
        if (sendKey==1){
            sendkeyBack=2;
        } else sendkeyBack=1;
        if ((keyBack = ftok("progfile.txt", sendkeyBack)) == -1) {
            printf("ftok");
            exit(1);
        }
        // Send message
        if ((key = ftok("progfile.txt", sendKey)) == -1) {
            printf("ftok");
            exit(1);
        }

        message.mesg_type = 1;

        char mess[100];
        // strcpy(mess, message.mesg_text);

        if ((msgid = msgget(key, PERMS | IPC_CREAT)) == -1) { 
            printf("msgget");
            exit(1);
        }

        // strcpy(message.mesg_text, mess);
        // msgsnd to send message
        msgsnd(msgid, &message, sizeof(message), 0);
        
        if ((msgid = msgget(keyBack, PERMS | IPC_CREAT)) == -1) { 
            printf("msgget");
            exit(1);
        }
        
         int ss=strcmp(mess,"abcde");
         printf("%d\n",ss);
            // strcpy(message.mesg_text,"@456");
            // msgsnd(msgid, &message, sizeof(message), 0);
        
        // display the message
        printf("Data send is : %s", message.mesg_text);
    }
    return 0;
}