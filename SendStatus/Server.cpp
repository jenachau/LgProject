// C Program for Message Queue (Writer Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>
#include <string>
using namespace std;

// structure for message queue
struct mesg_buffer {
	long mesg_type;
	char mesg_text[100];
} message;

void receiveStatus(){
	key_t key;
	int msgid;
	while(1){
		// ftok to generate unique key
		key = ftok("progfile.txt", 65);

		// msgget creates a message queue
		// and returns identifier
		msgid = msgget(key, 0666 | IPC_CREAT);

		// msgrcv to receive message
		msgrcv(msgid, &message, sizeof(message), 1, 0);

		// display the message
		cout<<"Data send is : "<< message.mesg_text<<endl;  
	}
}
int main()
{
	while(1){
    	receiveStatus();
	}
	return 0;
}
