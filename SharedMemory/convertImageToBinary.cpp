#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
    ifstream image("img.png", ios::in | ios::binary);
    ofstream binary("binary_image_data.txt", ios::out | ios::app);

    int ch;
    while(!image.eof()){
        ch = int(image.get());
        binary.put(ch);
    }
    cout<<"Image successfully converted into binary File"<<endl;
    binary.close();
    
}