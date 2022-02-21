// C++ program for client1 
#include "Common.cpp"
#define MY_ID 1
#define MY_NAME "Thu Chau"

mesg_buffer message;

void sendMessage(){
    key_t key = generate_key(SEVER_ID);
    int msgid = generate_msgid(key);

    message.mesg_type = 1;
    int receriver_id = choosePerson();
    while(1){
        fgets(message.mesg_text, MAX, stdin);
        message.send_key = receriver_id;
        strcpy(message.name, MY_NAME), 19;
        // msgsnd to send message
        msgsnd(msgid, &message, sizeof(message), 0);
    }
}

void receiveMessage(){
    key_t key = generate_key(MY_ID);
    int msgid = generate_msgid(key);

    while(1){
        // msgrcv to receive message
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        // display the message
        printf("From %s : %s \n",message.name, message.mesg_text);
    }
}

int main()
{
    std::thread t2(receiveMessage);
    std::thread t1(sendMessage);

    t1.join();
    t2.join();
    return 0;
}