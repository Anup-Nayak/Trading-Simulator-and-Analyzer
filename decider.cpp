#include<iostream>
#include<string>
#include<cstdlib>

using namespace std;

int main(int argc, char *argv[]){
    
    string strategy = argv[1];
    string x =  argv[2];
    string n = argv[3];
    string p = argv[4];

    if(strategy == "BASIC"){
        system("g++ basic.cpp -o a.exe");
        string c = "./a.exe " + x + " " + n;
        system(c.c_str());
    }else if(strategy == "DMA"){
        system("g++ dma.cpp -o a.exe");
        string c = "./a.exe " + x + " " + n + " " + p;
        system(c.c_str());

    }else{
        cout << "why" << endl;
    }
    return 0;
}