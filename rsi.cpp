#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<bits/stdc++.h>
#include<cmath>

using namespace std;

bool checkDate(string &start, string &end){
    //DD/MM/YYYY
    int year1 = stoi(start.substr(6,4));
    int year2 = stoi(end.substr(6,4));
    int month1 = stoi(start.substr(3,2));
    int month2 = stoi(end.substr(3,2));
    int day1 = stoi(start.substr(0,2));
    int day2 = stoi(end.substr(0,2));

    if(year1 > year2){
        return true;
    }else if(year1 < year2){
        return false;
    }else{
        if(month1 > month2){
            return true;
        }else if(month1 < month2){
            return false;
        }else{
            if(day1 > day2){
                return true;
            }else if(day1 < day2){
                return false;
            }else{
                return false;
            }
        }
    }
}

void rsi(int x, int n, int maxPos, int minPos, string start_date,int  oversold_threshold,int overbought_threshold){
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
    queue <double> loss_q ;
    queue <double> gain_q ;
    double money = 0;
   

    string line;
    getline(file, line); //header
    getline(file,line); //first entry

    istringstream oneline(line);

    string date;
    string p1;
  
    getline(oneline, date, ',');
    getline(oneline, p1,'\n');
     
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
   
    while(checkDate(start_date,date)){
      
        getline(file,line);
        istringstream oneline(line);

        getline(oneline, date, ',');
        getline(oneline, p1,'\n');

        price = stod(p1);
        gain = 0 ;
        loss = 0 ;
        
        if( price - prevPrice > 0 ){
           gain =  price - prevPrice ;
     
        }
        if(  prevPrice - price > 0 ){
            loss = prevPrice - price  ;
     
        }
       
        // cout<<price<<" "<< prevPrice<<" "<<gain<<" "<<loss<<endl ;
        gain_sum += gain ;
        loss_sum += loss ;
        avgGain = gain_sum/n ;
        avgLoss = loss_sum/n ;
        gain_q.push(gain);
        loss_q.push(loss) ;
           
        if(iter > n-2  &&  checkDate(start_date,date)){

          queue_front1 = gain_q.front();
          queue_front2 = loss_q.front();
          gain_sum -= queue_front1 ;
          loss_sum -= queue_front2 ;
          gain_q.pop() ;
          loss_q.pop() ;
      

        }

        iter++ ;

        if( checkDate(start_date,date)){
             prevPrice = price;
        }
         
    }
       

           
    //    price = stod(p1);

    //     gain = 0 ;
    //     loss = 0 ;

    //     if( price - prevPrice > 0 ){
    //         gain =  price - prevPrice ;
     
    //     }
        // if( prevPrice - price < 0 ){
        //     loss =  prevPrice - price ;
     
        // }
        // if(  prevPrice > price ){
        //     loss =   prevPrice - price ;
     
        // }
       

        // gain_sum += gain ;
        // loss_sum += loss ;

        // gain_q.push(gain);
        // loss_q.push(loss) ;
        
        // avgGain = gain_sum/n ;
        // avgLoss = loss_sum/n ;
        // cout<<avgGain<<" "<<avgLoss<<endl ;

        RS = avgGain/avgLoss ;
        //    cout<<RS<<endl; 
        RSI = 100.0*((RS)/(1.0+RS)) ;
            //  cout<<RSI<<endl; 
            //    cout<<endl ;
            //   // cout<<price<<" "<< prevPrice<<" "<<gain<<" "<<loss<<endl ;
            //     cout<<endl ;
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
        // if( prevPrice - price < 0 ){
        //     loss =  prevPrice - price ;
     
        // }
        if(  prevPrice > price ){
            loss =  prevPrice - price ;
     
        }
           
        //   cout<<price<<" "<< prevPrice<<" "<<gain<<" "<<loss<<endl ;

        gain_sum += gain ;
        loss_sum += loss ;

        gain_q.push(gain);
        loss_q.push(loss) ;
        
        avgGain = gain_sum/n ;
        avgLoss = loss_sum/n ;

        RS = avgGain/avgLoss ;

        RSI = 100.0*(1.0 - (1.0/(1.0+RS))) ;
            // cout<<RSI<<endl; 
       
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

}


int main(int argc, char *argv[]){

   
    int x = stoi(argv[1]);
    int n = stoi(argv[2]);
    int s = stoi(argv[3]);
    int b = stoi(argv[4]);

    string start_date = argv[5]; 
    int maxPos = x;
    int minPos = -x;
    rsi(0,n,maxPos,minPos,start_date,s,b);
    
    return 0;
}