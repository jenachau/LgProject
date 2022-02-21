// C Program for Message Queue (Writer Process)
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>
using namespace std;

using namespace std;

#define MAX 10

bool status;
// structure for message queue
struct mesg_buffer {
	long mesg_type;
	char mesg_text[100];
    
} message;

void sendStatus(){
  	key_t key;
	int msgid;

	// ftok to generate unique key
	key = ftok("progfile.txt", 65);

	// msgget creates a message queue
	// and returns identifier
	msgid = msgget(key, 0666 | IPC_CREAT);
	message.mesg_type = 1;
    if (status == 1){
        strcpy(message.mesg_text, "Hang Nguyen: online");
    }
    else {
        strcpy(message.mesg_text, "Hang Nguyen: offline");
    }
	// msgsnd to send message
	msgsnd(msgid, &message, sizeof(message), 0);

	// display the message
	cout<<"Data send is : "<< message.mesg_text<<endl;  
}
int main()
{
    cout<<"Hi Hang Nguyen !!!!!"<<endl;
    cout<<"Choose 1: turn on"<<endl;
    cout<<"Choose 0: turn off"<<endl;
    int choose;
    while(1){
        cin>>choose;
        if (choose == 1){
            status = 1;
            sendStatus();
        }
        if (choose == 0){
            cout<<"Bye Hang Nguyen"<<endl;
            status = 0;
            sendStatus();
            break;
        }
    }
    sendStatus();
	return 0;
}
