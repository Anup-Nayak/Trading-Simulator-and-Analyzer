#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<bits/stdc++.h>
#include<cmath>

using namespace std;

double dma(int x, int n, double p,int maxPos, int minPos){
    
     
 ifstream file("data_DMA.csv");
    ifstream file2("extra_data_DMA.csv");
    ofstream cashflow("daily_cashflow.csv");
    ofstream order("order_statistics.csv");

    cashflow << "Date,Cashflow\n";
    order << "Date,Order_dir,Quantity,Price\n";

    if(!file.is_open()){
        cout << "error anup : could not open file!" << endl;
    }


    string line;
    getline(file, line); //header
    getline(file2,line); 

    vector<string> extra_data;

    for(int i=0;i<n;i++){
        getline(file2,line);
        istringstream oneline(line);

        string date;
        string p;

        getline(oneline, date, ',');
        getline(oneline, p,'\n');

        extra_data.push_back(p);
    }

    reverse(extra_data.begin(),extra_data.end());

    istringstream oneline(line);

    string date;
    string p1;

    getline(oneline, date, ',');
    getline(oneline, p1,'\n');
    
    queue <double> bought;
    queue <double> sold;
    
    queue <double> n_days_data;
    double price = 0;
    double sum = 0;
    double sum_sq = 0;
    double mean = 0;
    double var = 0;
    double stand = 0;
    double queue_front = 0 ;
    double buyprice = 0 ;
    double sellprice = 0;
    int iter = 0 ;
    double money = 0;
   

    for(int i=1;i<n;i++){
      
        price = stod(extra_data[i]);
        n_days_data.push(price);
        sum += price ;
        sum_sq += pow(price,2);
        mean = sum / n;
        var = sum_sq - pow(mean,2);
        stand = sqrt(var);
      
    }
      
   

    while(getline(file, line)){
        istringstream oneline(line);

        getline(oneline, date, ',');
        getline(oneline, p1,'\n');

        price = stod(p1);
     
        n_days_data.push(price);
        sum += price ;
        sum_sq += pow(price,2);
        
        mean = sum / n;
       var = (sum_sq/n) - pow(mean,2);
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
    return money;
}

int main(int argc, char *argv[]){

    int x = stoi(argv[1]);
    int n = stoi(argv[2]);
    double p = stoi(argv[3]);
    string start_date = argv[4];

    int maxPos = x;
    int minPos = -x;

    dma(0,n,p,maxPos,minPos);
    
    return 0;
}