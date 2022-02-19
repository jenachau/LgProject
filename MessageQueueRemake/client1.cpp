#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <thread>
#include <unistd.h>

#define MAX 100
#define PERMS 0644
#define SEVER_ID '999'
#define MY_ID '1'

struct msg_buffer{
    long mesg_type;
    char mesg_text[MAX];
    char send_key;
    char name[20];
} message;

void sendMessage(int &running){
    key_t key;
    int msgid;

    if ((key = ftok("progfile.txt", SEVER_ID)) == -1) {
        printf("ftok");
        exit(1);
    }
    strcpy(message.name,"Thu Chau"), 19;
    message.send_key = '2';
    message.mesg_type = 1;

    printf("Me : ");
    // fgets(message.mesg_text, MAX, stdin);
    scanf(" %[^\n]s",message.mesg_text);
    
    if ((msgid = msgget(key, PERMS | IPC_CREAT)) == -1) { 
        printf("msgget");
        exit(1);
    }

    // msgsnd to send message
    msgsnd(msgid, &message, sizeof(message), 0);
    if (strcmp(message.mesg_text,"@off")==0) running=0;
    // display the message
}

void receiveMessage(int &running){
    key_t key;
    int msgid;

    if ((key = ftok("progfile.txt", MY_ID)) == -1) {
        printf("ftok");
        exit(1);
    }

    if ((msgid = msgget(key, PERMS | IPC_CREAT)) == -1) { 
        printf("msgget");
        exit(1);
    }

    // msgrcv to receive message
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    if (strcmp(message.mesg_text,"@onl")==0)
    {
        printf("\r%s is online\n",message.name);
        printf("\rMe :");
    }
    else if (strcmp(message.mesg_text,"@off")==0)
    {
        printf("\r%s is offline\n",message.name);
        printf("\rMe :");
    }
    else if (strcmp(message.mesg_text,"@offMs")==0)
    {
        running=0;
    }
    // display the message
    else {
        printf("\r%s : %s \n",message.name, message.mesg_text);
        printf("\rMe : ");
    }
    
    fflush(stdout);
}
void sendOnline(){
    key_t key;
    int msgid;

    if ((key = ftok("progfile.txt", SEVER_ID)) == -1) {
        printf("ftok");
        exit(1);
    }
    strcpy(message.name,"Thu Chau"), 19;
    message.send_key = '2';
    message.mesg_type = 1;

    // fgets(message.mesg_text, MAX, stdin);
    strcpy(message.mesg_text,"@onl");
    
    if ((msgid = msgget(key, PERMS | IPC_CREAT)) == -1) { 
        printf("msgget");
        exit(1);
    }

    // msgsnd to send message
    msgsnd(msgid, &message, sizeof(message), 0);
}

int main()
{   
    // std::thread t1(sendMessage);
    // std::thread t2(receiveMessage);
    int running=1;
    printf("Chat ready, type '@off' to exit\n");
    int crt_process=fork();
    
    if (crt_process==0){
        sendOnline();
        while(running){
            sendMessage(running);
        }
    }
    else if (crt_process>0) {
        while(running){
            receiveMessage(running);
        }
    } 
    
    
    return 0;
}