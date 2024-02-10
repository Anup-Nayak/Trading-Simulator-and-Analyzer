#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<bits/stdc++.h>
#include<cmath>

using namespace std;

void dma(int x, double n, double p,int maxPos, int minPos){
    ifstream file("data.csv");
    ofstream cashflow("daily_cashflow.csv");
    ofstream order("order_statistics.csv");

    cashflow << "Date,Cashflow\n";
    order << "Date,Order_dir,Quantity,Price\n";

    if(!file.is_open()){
        cout << "error anup : could not open file!" << endl;
    }

    queue <double> bought;
    queue <double> sold;

    queue <double> n_days_data;
   

    int money = 0;

    //setting flags
    bool incFlag = false;
    bool decFlag = false;

    string line;
    getline(file, line); //header
    getline(file,line); //first entry

    istringstream oneline(line);

    string date;
    string p1;

    getline(oneline, date, ',');
    getline(oneline, p1,'\n');

    double prevPrice = stod(p1);
    double price = 0;
    double sum = 0;
    double sum_sq = 0;
    double mean = 0;
    double var = 0;
    double stand = 0;
    double queue_front = 0 ;
    double buyprice = 0 ;
    double sellprice = 0;


    for(int i=0;i<n-1;i++){
        getline(file,line);
        istringstream oneline(line);

        string date;
        string p1;

        getline(oneline, date, ',');
        getline(oneline, p1,'\n');

        double price = stod(p1);

        n_days_data.push(price);
        sum += price ;
        sum_sq += pow(price,2);

    }

    while(getline(file, line)){
        istringstream oneline(line);

        string date;
        string p1;
        getline(oneline, date, ',');
        getline(oneline, p1,'\n');

        double price = stod(p1);
     
        n_days_data.push(price);
        sum += price ;
        sum_sq += pow(price,2);
        
        mean = sum / n;
        var = sum_sq - pow(mean,2);
        stand = sqrt(var);

        buyprice  = mean + p*stand ;
        sellprice = mean - p*stand ;

            if( price >= buyprice ){
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
            }else if ( price <= sellprice ){
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
       
        prevPrice = price;
        string w2 = date + "," + to_string(money) + "\n";
        cashflow << w2;

        queue_front = n_days_data.front();
        sum -= queue_front ;
        sum_sq -= pow(queue_front,2);
        n_days_data.pop() ;
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

}


int main(int argc, char *argv[]){

    int x = stoi(argv[1]);
    double n = stoi(argv[2]);
    double p = stoi(argv[3]);
    int maxPos = x;
    int minPos = -x;

    dma(0,n,p,maxPos,minPos);
    
    return 0;
}