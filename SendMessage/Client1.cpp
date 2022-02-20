// C Program for Message Queue (Reader Process)
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <thread>

#define MAX 50
#define PERMS 0644
#define SEVER_ID '999'
#define MY_ID 1

// structure for message queue
struct mesg_buffer {
	long mesg_type;
    char mesg_text[100];
    int send_key;
    char name[20];
} message;

void sendMessage(){
    key_t key;
    int msgid;
    int running=1;
    if ((key = ftok("progfile.txt", SEVER_ID)) == -1) {
        printf("ftok");
        exit(1);
    }
    message.mesg_type = 1;
    while(running){
        printf("\rMe: ");
        fgets(message.mesg_text, MAX, stdin);
        message.send_key = 2;
        strcpy(message.name, "Thu Chau"), 19;
        if ((msgid = msgget(key, PERMS | IPC_CREAT)) == -1) { 
            printf("msgget");
            exit(1);
        }

        // msgsnd to send message
        msgsnd(msgid, &message, sizeof(message), 0);
        if (strcmp(message.mesg_text,"@off")==0){
            running=0;
        }
    }
}

void receiveMessage(){
    key_t key;
    int msgid;
    int running=1;
    if ((key = ftok("progfile.txt", MY_ID)) == -1) {
        printf("ftok");
        exit(1);
    }
    while(running){
        if ((msgid = msgget(key, PERMS | IPC_CREAT)) == -1) { 
            printf("msgget");
            exit(1);
        }

        // msgrcv to receive message
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        // display the message
        if (strcmp(message.mesg_text,"@onl")==0){
            printf("\r%s is online\n",message.name);
            printf("Me: ");
        }
        else if (strcmp(message.mesg_text,"@off")==0){
            printf("\r%s is offline\n",message.name);
            printf("Me: ");
        }
        else if (strcmp(message.mesg_text,"@offMs")==0){
            running=0;
        }
        else {
            printf("\rFrom %s : %s",message.name, message.mesg_text);
            printf("Me: ");
        }
        fflush(stdout);
    }
}
void OnlineNoti(){
    key_t key;
    int msgid;

    if ((key = ftok("progfile.txt", SEVER_ID)) == -1) {
        printf("ftok");
        exit(1);
    }
    message.mesg_type = 1;
        strcpy(message.mesg_text,"@onl");
        message.send_key = 2;
        strcpy(message.name, "Thu Chau"), 19;
        if ((msgid = msgget(key, PERMS | IPC_CREAT)) == -1) { 
            printf("msgget");
            exit(1);
        }

        // msgsnd to send message
        msgsnd(msgid, &message, sizeof(message), 0);
}
int main()
{   
    OnlineNoti();
    std::thread t1(sendMessage);
    std::thread t2(receiveMessage);
    t1.join();
    t2.join();
    return 0;
}