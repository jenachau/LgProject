// C Program for Message Queue (Reader Process)
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <thread>
#include <iostream>
using namespace std;

#define MAX 50
#define PERMS 0644
#define SEVER_ID 999

// struct for message queue
struct mesg_buffer {
	long mesg_type;
    char mesg_text[100];
    int send_key;
    char name[20];
};

// choose person to chat
int choosePerson(){
    int choose;
    cout<<"Choose one person to chat"<<endl;
    cout<<"1. Thu Chau"<<endl;
    cout<<"2. Thi Tran"<<endl;
    cout<<"3. Hang Tran"<<endl;
    cin>>choose;
    cout<<"Enter text to chat."<<endl;
    cout<<"Enter 0 to exit chat."<<endl;
    if (choose >= 1 && choose <= 3) return choose;
    else return 1;
}

// use ftok to create key
int generate_key(int my_key){
    int key;
    if ((key = ftok("progfile.txt", my_key)) == -1) {
        printf("ftok");
        exit(1);
    }
    return key;
}

int generate_msgid(int key){
    int msgid;
    if ((msgid = msgget(key, PERMS | IPC_CREAT)) == -1) { 
        printf("msgget");
        exit(1);
    }
    return msgid;
}
