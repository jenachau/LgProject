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
#define MY_ID '2'

struct msg_buffer
{
    long mesg_type;
    char mesg_text[MAX];
    char send_key;
    char name[20];
} message;

void sendMessage()
{
    key_t key;
    int msgid;

    if ((key = ftok("progfile.txt", SEVER_ID)) == -1)
    {
        printf("ftok");
        exit(1);
    }
    strcpy(message.name, "Thi Tran"), 19;
    message.send_key = '1';
    message.mesg_type = 1;

    printf("Me: ");
    // fgets(message.mesg_text, MAX, stdin);
    scanf(" %[^\n]s", message.mesg_text);
    if ((msgid = msgget(key, PERMS | IPC_CREAT)) == -1)
    {
        printf("msgget");
        exit(1);
    }

    // msgsnd to send message
    msgsnd(msgid, &message, sizeof(message), 0);

    // display the message
}

void receiveMessage()
{
    key_t key;
    int msgid;

    if ((key = ftok("progfile.txt", MY_ID)) == -1)
    {
        printf("ftok");
        exit(1);
    }

    if ((msgid = msgget(key, PERMS | IPC_CREAT)) == -1)
    {
        printf("msgget");
        exit(1);
    }

    // msgrcv to receive message
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    if (strcmp(message.mesg_text, "off") == 0)
        printf("\r%s is offline\n", message.name);
    // display the message
    else
    {
        printf("\r%s : %s\n", message.name, message.mesg_text);
        printf("Me : ");
    }
    fflush(stdout);
}

int main()
{
    // std::thread t1(sendMessage);
    // std::thread t2(receiveMessage);
    if (fork())
    {
        while (1)
        {
            sendMessage();
        }
    }
    else
    {
        while (1)
        {
            receiveMessage();
        }
    }

    return 0;
}