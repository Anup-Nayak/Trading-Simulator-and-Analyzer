#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<bits/stdc++.h>
#include<cmath>

using namespace std;


double rsi(int x, int n, int maxPos, int minPos,int  oversold_threshold,int overbought_threshold){
     ifstream file("data_RSI.csv");
    ifstream file2("extra_data_RSI.csv");
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
    queue <double> loss_q ;
    queue <double> gain_q ;
    double money = 0;
    
    double prevPrice = stod(p1);
    int days = 1;
    double price = 0;
    double loss ;
    double gain ;
    double loss_sum = 0 ;
    double gain_sum = 0 ;
    double avgLoss = 0 ;
    double avgGain = 0 ;
    double RS = 0 ;
    double RSI = 0 ;
    double queue_front1 = 0 ;
    double queue_front2 = 0 ;
    
    int iter = 0 ;
   
     for(int i=1;i<n;i++){

        price = stod(extra_data[i]);
       
        gain = 0 ;
        loss = 0 ;
        
        if( price - prevPrice > 0 ){
           gain =  price - prevPrice ; 
        }
        if(  prevPrice - price > 0 ){
            loss = prevPrice - price  ;
    
        }
          
        gain_sum += gain ;
        loss_sum += loss ;
        avgGain = gain_sum/n ;
        avgLoss = loss_sum/n ;
        gain_q.push(gain);
        loss_q.push(loss) ;   
        prevPrice = price ;    
    }
       

           
    
        
    while(getline(file, line)){
        istringstream oneline(line);

        getline(oneline, date, ',');
        getline(oneline, p1,'\n');

        price = stod(p1);

        gain = 0 ;
        loss = 0 ;

        if( price - prevPrice > 0 ){
            gain =  price - prevPrice ;
     
        }
        
        if(  prevPrice > price ){
            loss =  prevPrice - price ;
     
        }
           

        gain_sum += gain ;
        loss_sum += loss ;

        gain_q.push(gain);
        loss_q.push(loss) ;
        
        avgGain = gain_sum/n ;
        avgLoss = loss_sum/n ;

        RS = avgGain/avgLoss ;

        RSI = 100.0*(1.0 - (1.0/(1.0+RS))) ;
       
            if( RSI < oversold_threshold){
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
            }else if ( RSI > overbought_threshold){
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
        queue_front1 = gain_q.front();
        queue_front2 = loss_q.front();
        gain_sum -= queue_front1 ;
        loss_sum -= queue_front2 ;
        gain_q.pop() ;
        loss_q.pop() ;

        prevPrice = price;
        string w2 = date + "," + to_string(money) + "\n";
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