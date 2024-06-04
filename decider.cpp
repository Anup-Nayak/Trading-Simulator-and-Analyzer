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
        system("g++ strategies/basic.cpp -o a.exe");
        string c = "./a.exe " + x + " " + n + " " + start_date;
        system(c.c_str());
        
    }else if(strategy == "DMA"){
        system("g++ strategies/dma.cpp -o a.exe");
        string c = "./a.exe " + x + " " + n + " " + p + " " + start_date;
        system(c.c_str());
        
    }else if(strategy == "DMA++"){
        system("g++ strategies/dmapp.cpp -o a.exe");
        string c = "./a.exe " + x + " " + n + " " + p + " " + mhd + " " + c1 + " " + c2;
        system(c.c_str());
        
    }else if(strategy == "MACD"){
        system("g++ strategies/macd.cpp -o a.exe");
        string c = "./a.exe " + x ;
        system(c.c_str());
        
    }else if(strategy == "ADX"){
        system("g++ strategies/adx.cpp -o a.exe");
        string c = "./a.exe " + x + " " + n + " " + adx_threshold ;
        system(c.c_str());
        
    }else if(strategy == "RSI"){
        system("g++ strategies/rsi.cpp -o a.exe");
        string c = "./a.exe " + x + " " + n + " " + oversold_threshold + " " + overbought_threshold + " " + start_date;
        system(c.c_str());
        
    }else if(strategy == "PAIRS"){
        system("g++ strategies/pair.cpp -o a.exe");
        string c = "./a.exe " + x + " " + n + " " + p + " " + threshold ;
        system(c.c_str());
        
    }else if(strategy == "PAIRS_STOP"){
        system("g++ strategies/stop_loss.cpp -o a.exe");
        string c = "./a.exe " + x + " " + n + " " + p + " " + threshold + " " + stop_loss_threshold ;
        system(c.c_str());
        
    }else if(strategy == "LINEAR_REGRESSION"){
        system("g++ strategies/linear.cpp -o a.exe");
        string c = "./a.exe " + p + " " + x;
        system(c.c_str());
        
    }else if(strategy == "BEST_OF_ALL"){
        system("g++ strategies/best.cpp -o a.exe");
        string c = "./a.exe ";
        system(c.c_str());
        
    }else{
        cout << "Enter a correct strategy!" << endl;
    }
    return 0;
}