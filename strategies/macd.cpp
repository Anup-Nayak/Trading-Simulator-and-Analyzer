#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <bits/stdc++.h>
#include <cmath>

using namespace std;

double macd(int x, int maxPos, int minPos){
    ifstream file("data_MACD.csv");
    ofstream cashflow("daily_cashflow.csv");
    ofstream order("order_statistics.csv");

    cashflow << "Date,Cashflow\n";
    order << "Date,Order_dir,Quantity,Price\n";

    if(!file.is_open()){
        cout << "error anup : could not open file!" << endl;
    }

    queue <double> bought;
    queue <double> sold;

    double money = 0;

    string line;
    getline(file, line); //header
    getline(file,line); //first entry

    istringstream oneline(line);

    string date;
    string p;

    getline(oneline, date, ',');
    getline(oneline, p,'\n');

    double prevPrice = stod(p);
    int days = 1;
    double price = 0;
    double SEWM_0 = prevPrice ;
    double SEWM_t = 0.5 ;
    double LEWM_0 = prevPrice ;
    double LEWM_t = 0.5 ;
    double MACD = 0.0;
    double Signal_t = 0.0 ;
    double Signal_0 = 0.0 ;
    double alpha_9 = 0.2 ;
    double alpha_12 =  2.0/13.0 ;
    double alpha_26 =  2.0/27.0 ;
    double Short_EWM = 0.0;
    double Long_EWM = 0.0;
    
    string w2 = date + "," + to_string(money) + "\n";
    cashflow << w2;

    while(getline(file, line)){

        istringstream oneline(line);

        string date;
        string p;

        getline(oneline, date, ',');
        getline(oneline, p,'\n');

        price = stod(p);
        LEWM_t = alpha_26*(price - LEWM_0)+ LEWM_0 ;
        SEWM_t = alpha_12*(price - SEWM_0)+ SEWM_0 ;
        MACD = SEWM_t - LEWM_t ;
        Signal_t  = alpha_9*(MACD - Signal_t) + Signal_0;
      
           
           if (MACD > Signal_t){
         
                if(x < maxPos){
                    x++;
                    if(sold.empty()){
                        bought.push(price);
                    }else{
                        sold.pop();
                    }
                    money = money - price;
                    string w =  date + ",BUY" ;
                    w = w + "," + to_string(1) + ","  + to_string(price) +  "\n";
                    order << w;
                }
            }else if (MACD < Signal_t){
                if (x > minPos){
                    x--;
                    if(bought.empty()){
                        sold.push(price);
                    }else{
                        bought.pop();
                    }
                    money = money + price;
                    string w =  date + ",SELL" ;
                    w = w + "," + to_string(1) +  "," + to_string(price)  + "\n";
                    order << w;
                }
            }
              
      
        LEWM_0 =  LEWM_t ;
        SEWM_0 =  SEWM_t ;
        Signal_0 = Signal_t ;

        w2 = date + "," + to_string(money) + "\n";
        cashflow << w2;
    }

    file.close();
    

    cashflow.close();
    order.close();

    if(!(bought.empty() and sold.empty())){
        while(!bought.empty()){
            money = money + price ;
            bought.pop();
        }
        while(!sold.empty()){
            money = money - price ;
            sold.pop();
        }
    }
    ofstream final("final_pnl.txt");
    final << to_string(money);
    final.close();
    return money;
}

int main(int argc, char *argv[]){

    int x = stoi(argv[1]);
    int maxPos = x;
    int minPos = -x;

    macd(0,maxPos,minPos);
    
    return 0;
}