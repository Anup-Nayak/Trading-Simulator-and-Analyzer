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
    string oversold_threshold = argv[6];
    string overbought_threshold = argv[7];
    string start_train_date = argv[8];
    string threshold = argv[9];
    string adx_threshold = argv[10];
    string mhd = argv[11];
    string c1 = argv[12];
    string c2 = argv[13];
    string stop_loss_threshold = argv[14];

    if(strategy == "BASIC"){
        system("g++ basic.cpp -o a.exe");
        string c = "./a.exe " + x + " " + n + " " + start_date;
        system(c.c_str());
        cout << "why1" << endl;
    }else if(strategy == "DMA"){
        system("g++ dma.cpp -o a.exe");
        string c = "./a.exe " + x + " " + n + " " + p + " " + start_date;
        system(c.c_str());
        // cout << "why2" << endl;
    }else if(strategy == "DMA++"){
        system("g++ dmapp.cpp -o a.exe");
        string c = "./a.exe " + x + " " + n + " " + p + " " + mhd + " " + c1 + " " + c2;
        system(c.c_str());
        // cout << "whyyyyyyyyyyyyyyyyyy2" << endl;
    }else if(strategy == "MACD"){
        system("g++ macd.cpp -o a.exe");
        string c = "./a.exe " + x ;
        system(c.c_str());
        // cout << "why2" << endl;
    }else if(strategy == "ADX"){
        system("g++ adx.cpp -o a.exe");
        string c = "./a.exe " + x + " " + n + " " + adx_threshold ;
        system(c.c_str());
        // cout << "why2" << endl;
    }else if(strategy == "RSI"){
        system("g++ rsi.cpp -o a.exe");
        string c = "./a.exe " + x + " " + n + " " + oversold_threshold + " " + overbought_threshold + " " + start_date;
        system(c.c_str());
        // cout << "why2" << endl;
    }else if(strategy == "PAIRS"){
        system("g++ pair.cpp -o a.exe");
        string c = "./a.exe " + x + " " + n + " " + p + " " + threshold ;
        system(c.c_str());
        // cout << "why2" << endl;
    }else if(strategy == "PAIRS_STOP"){
        system("g++ stop_loss.cpp -o a.exe");
        string c = "./a.exe " + x + " " + n + " " + p + " " + threshold + " " + stop_loss_threshold ;
        system(c.c_str());
        // cout << "why2" << endl;
    }else if(strategy == "LINEAR_REGRESSION"){
        system("g++ linear.cpp -o a.exe");
        string c = "./a.exe " + p + " " + x;
        system(c.c_str());
        // cout << "why2" << endl;
    }else if(strategy == "BEST_OF_ALL"){
        system("g++ best.cpp -o a.exe");
        string c = "./a.exe ";
        system(c.c_str());
        // cout << "why2" << endl;
    }else{
        cout << "why" << endl;
    }
    return 0;
}