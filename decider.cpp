#include<iostream>
#include<string>
#include<cstdlib>

using namespace std;

int main(int argc, char *argv[]){
    
    string strategy = argv[1];
    string x =  argv[2];
    string n = argv[3];
    string p = argv[4];
    string start_date = argv[5];
    if(strategy == "BASIC"){
        system("g++ basic.cpp -o a.exe");
        string c = "./a.exe " + x + " " + n + " " + start_date;
        system(c.c_str());
        // cout << "why1" << endl;
    }else if(strategy == "DMA"){
        system("g++ dma.cpp -o a.exe");
        string c = "./a.exe " + x + " " + n + " " + p + " " + start_date;
        system(c.c_str());
        // cout << "why2" << endl;
    }else if(strategy == "MACD"){
        system("g++ macd.cpp -o a.exe");
        string c = "./a.exe " + x ;
        system(c.c_str());
        // cout << "why2" << endl;
    }else if(strategy == "LINEAR_REGRESSION"){
        system("g++ linear.cpp -o a.exe");
        string c = "./a.exe " ;
        system(c.c_str());
        // cout << "why2" << endl;
    }else{
        cout << "why" << endl;
    }
    return 0;
}