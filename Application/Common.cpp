#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#pragma once

using namespace std;

#define SEVER_ID 999
#define PERMS 0644
#define MAX 50


// structure for a message
struct mesg_buffer {
	long mesg_type = 1;
    char mesg_text[100];
    int send_key;
    string name;
};


//-------------------- use ftok to create key -------------------------------------
int generate_key(int id){
    int key;
    if ((key = ftok("progfile.txt", id)) == -1) {
        printf("ftok");
        exit(1);
    }
    return key;
}
//---------------------------------------------------------------------------------

//-------------------- use mssget to create msgid ---------------------------------
int generate_msgid(int key){
    int msgid = generate_key(key);
    if ((msgid = msgget(msgid, PERMS | IPC_CREAT)) == -1) { 
        printf("msgget");
        exit(1);
    }
    return msgid;
}
//---------------------------------------------------------------------------------

//------------------- function to client choose activity --------------------------
int chooseActivity(){
    int chooseAcitivity;
    do{
        cout<<"Choose one activity you want to use:"<<endl;
        cout<<"Enter 0: Stop car"<<endl;
        cout<<"Enter 1: Send Message"<<endl;
        cout<<"Enter 2: Send Image"<<endl;
        int chooseAcitivity;
        cin>>chooseAcitivity;
        if(chooseAcitivity == 1 || chooseAcitivity == 2 || chooseAcitivity == 0) return chooseAcitivity;
        else {
            cout<<"Please enter 1 or 2 to choose activity";
        }
    }while (chooseAcitivity != 1 && chooseAcitivity != 2 && chooseAcitivity != 0);

}



