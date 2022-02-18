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
#define MY_ID '2'

// structure for message queue
struct mesg_buffer {
	long mesg_type;
    char mesg_text[100];
    char send_key;
    char name[20];
} message;

void sendMessage(){
    key_t key;
    int msgid;
    if ((key = ftok("progfile.txt", SEVER_ID)) == -1) {
        printf("ftok");
        exit(1);
    }
    printf("%d\n", key);

    strcpy(message.name, "Thi Tran"), 19;
    message.send_key = '1';
    message.mesg_type = 1;

    printf("Enter message: ");
    fgets(message.mesg_text, MAX, stdin);

    if ((msgid = msgget(key, PERMS | IPC_CREAT)) == -1) { 
        printf("msgget");
        exit(1);
    }

    // msgsnd to send message
    msgsnd(msgid, &message, sizeof(message), 0);

    // display the message
    printf("Data send is : %s \n", message.mesg_text);
}

void receiveMessage(){
    key_t key;
    int msgid;

    if ((key = ftok("progfile.txt", MY_ID)) == -1) {
        printf("ftok");
        exit(1);
    }
    printf("%d\n", key);

    if ((msgid = msgget(key, PERMS | IPC_CREAT)) == -1) { 
        printf("msgget");
        exit(1);
    }

    // msgrcv to receive message
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    // display the message
    printf("From %s : %s \n", message.name, message.mesg_text);
}


int main()
{
    std::thread t1 {function1};

    
    return 0;
}

