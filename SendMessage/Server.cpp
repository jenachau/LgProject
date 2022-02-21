// C++ Program for sesrver
#include "Common.cpp"

mesg_buffer message;

int main()
{
    while(1){
        key_t key;
        int msgid;

        // Receive message
        key = generate_key(SEVER_ID);
        msgid = generate_msgid(key);

        // msgrcv to receive message
        msgrcv(msgid, &message, sizeof(message), 1, 0);

        // receiver key
        char sendKey = message.send_key;

        // Send message
        key = generate_key(sendKey);
        msgid = generate_msgid(key);

        message.mesg_type = 1;

        char mess[100];
        strcpy(mess, message.mesg_text);

        strcpy(message.mesg_text, mess);
        // msgsnd to send message
        msgsnd(msgid, &message, sizeof(message), 0);

    }
    return 0;
}