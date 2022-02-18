#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
    ifstream binary("binary_image_data.txt", ios::in | ios::binary);
    ofstream image("img1.png", ios::out | ios::app);

    char ch;
    while(!binary.eof()){
        ch = binary.get();
        image.put(ch);
    }
    cout<<"Convert Binary File into new image"<<endl;
    binary.close();
    image.close();
}