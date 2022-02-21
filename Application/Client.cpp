#include "Common.cpp"
#pragma once;
using namespace std;

mesg_buffer message;

//------------------------- Class Client -------------------------------------------
static int numberOfClient = 0;


class Client{
private:
    int id;
    string name;
    bool status;
public:
    int getId(){
        return id;
    }
    string getName(){
        return name;
    }
    bool getStatus(){
        return status;
    }
    void setStatus(bool status){
        this->status = status;
    }
    Client(){

    }
    Client(string name_c){
        numberOfClient++;
        id = numberOfClient;
        name = name_c;
    }
    void sendMessage(mesg_buffer message, Client receiver){
        int msgid = generate_msgid(SEVER_ID);
        while(1){
            cout<<"\nEnter your text: "<<endl;
            cout<<"\nEnter text to chat or enter 0 to exit chat"<<endl;
            fgets(message.mesg_text, MAX, stdin);
            if (message.mesg_text == "0"){
                cout<<"Exit chat"<<endl;
                break;
            }
            message.send_key = receiver.getId();
            message.name = this->getName();
            msgsnd(msgid, &message, sizeof(message), 0);
        }
    }
    void receiveMessage(mesg_buffer message){
        int msgid = generate_msgid(this->getId());

        while(1){
            // msgrcv to receive message
            msgrcv(msgid, &message, sizeof(message), 1, 0);
            // display the message
            cout<<"From "<<": "<<message.mesg_text<<endl;
        }
    }
};
//----------------------------------------------------------------------------------

//--------------------Create array to contain clients------------------------------
Client clientArray[100];
//---------------------------------------------------------------------------------

//------------------- funcion is used for client choose person to connect ----------
Client choosePerson(){
    int person;
    cout<<"Choose one person to connect: "<<endl;
    for (int i = 1; i < numberOfClient; i++){
        cout<<i<<": "<<clientArray[i].getName()<<endl;
    }
    cin>>person;
    return clientArray[person];
} 
//-----------------------------------------------------------------------------------

//--------------- function is used for client choose one activity -------------------
void chooseActive(Client client1){
    client1.setStatus(1);
    cout<<"Hi "<<client1.getName()<<"!!!!"<<endl;
    while(1){
        int activity ;
        chooseActivities: activity = chooseActivity();
        if (activity == 0){
            cout<<"Shut down car"<<endl;
            client1.setStatus(0);
            break;
        }
        else if (activity == 1){
            client1.sendMessage(message, choosePerson());
            goto chooseActivities;
        }
        else if (activity == 2){
            // do something to send image
        }
    }
}
//-----------------------------------------------------------------------------------