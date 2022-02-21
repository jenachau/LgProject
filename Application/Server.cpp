#include "Client.cpp"
#include "Common.cpp"
using namespace std;


// varibale to save text_message
char mess[100];
int receiver_id;

//------------------------- Class Server -------------------------------------------
class Server{
public:
    Server(){
    }
    void receiveMessage(){
        int msgid = generate_msgid(SEVER_ID);
        while(1){
            // msgrcv to receive message
            msgrcv(msgid, &message, sizeof(message), 1, 0);
            strcpy(mess, message.mesg_text);
            receiver_id = message.send_key;
        }
    }
    void sendMessage(){
        int msgid = generate_msgid(receiver_id);
        strcpy(message.mesg_text, mess);
        while(1){
            msgsnd(msgid, &message, sizeof(message), 0);
        }
    }

};
//----------------------------------------------------------------------------------

int main(){
    Server server;
    while(1){
        server.receiveMessage();
        server.sendMessage();
    }
}