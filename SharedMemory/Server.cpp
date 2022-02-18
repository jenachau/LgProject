#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;

#define MAXSIZE 27

int main()
{
    
        key_t key_receive = 1111111;
        int shmid, shmid2;
        key_t key;
        int *type, *type2;

        if ((shmid=shmget(key_receive, MAXSIZE, IPC_CREAT | 0666)) == -1){
            cout<<"error\n";
            exit(1);
        }
        type= (int*) shmat(shmid, NULL, 0); 
        cout<<"\nfirst: "<<type<<endl;
        int i =0;
        while (type[i] >= 0)
       {
            cout<<type[i]<<" ";
            i++;     
        }
        

        int *temp = type;
        if ((shmid2=shmget(33333, MAXSIZE, IPC_CREAT | 0666)) == -1){
            cout<<"error\n";
            exit(1);
        }
        type2 = (int*) shmat(shmid, NULL, 0); 
        type2 = type;
        cout<<"\nfirst2: "<<type2<<endl;
        i = 0;
        while (type2[i] >= 0)
       {
            cout<<type2[i]<<" ";
            i++;     
        }

    exit(0);
}