#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<bits/stdc++.h>
#include<cmath>
#include <map>
#include <vector>

using namespace std;

void dma_plus_plus(int x, int n, double p, int maxPos, int minPos, int max_hold_days, double c1, double c2)
{
    ifstream file("data.csv");
    ifstream file2("extra_data.csv");
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
        string p1;

        getline(oneline, date, ',');
        getline(oneline, p1,'\n');

        extra_data.push_back(p1);
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
    queue <double> Abs_q;
    vector <int> max_days;
    int money = 0;
    double P_0 = stod(p1) ;
    double prevPrice = P_0 ;
    double price = 0.0;
    
   
    double queue_front = 0.0 ;
    double buyprice = 0.0;
    double sellprice = 0.0;
    
    double ER_0 = 0.0;
    double ER =0.0;
    double SF_0 = 0.5 ;
    double SF_t = 0.5 ;
    double Abs_val = 0.0;
    double AMA_0 =  P_0 ;
    double AMA_t = 0.5 ;
  
    double cf ;
    double value1 ;
    double value2 ;
    bool buy = false;
    bool sell = false;
 
    int days = 0 ;
    int count = 0;
   for(int i=1;i<n;i++){
      
        price = stod(extra_data[i]);

        n_days_data.push(price);
        Abs_q.push(abs(price-prevPrice));         
        Abs_val +=  abs(price-prevPrice) ;
        prevPrice = price ;
        
    }

    while(getline(file, line)){
        istringstream oneline(line);

        string date;
        string p1;
        getline(oneline, date, ',');
        getline(oneline, p1,'\n');

        price = stod(p1);
     
        n_days_data.push(price);
        Abs_q.push(abs(price-prevPrice));  
        prevPrice = price ;
        Abs_val +=  abs(price-prevPrice) ;
        ER_0 = abs(n_days_data.front() - n_days_data.back()) ;
          
          if( !max_days.empty() ){
              if( max_days[0] == 0){
                  count-- ;
                  max_days.erase(max_days.begin());
              }
          }

        if( Abs_val != 0 ){
            ER = ER_0/Abs_val ;            
            cf = ( 2*ER - 1.0 - c2 )/(2*ER + 1.0 + c2) ;           
            SF_t = SF_0 + c1*(cf - SF_0);
            AMA_t = AMA_0 + SF_t*(price - AMA_0) ;
                   
            value1 = ((100 + p )/(100))*AMA_t ;
            value2 = ((100 - p )/(100))*AMA_t ;
               
            
                if( price >= value1  ){

                    if( x < maxPos ){
                        if( count == 0){
                        x++;
                        if(sold.empty()){
                               bought.push(price);
                               max_days.insert( max_days.begin()+max_days.size(), max_hold_days) ;
                        }else{
                              sold.pop();
                              max_days.erase(max_days.begin());
                         
                        }
                        money = money - price;
                        string w =  date + ",BUY" ;
                        w = w + "," + to_string(1) + ","  + to_string(price) +  "\n";
                        order << w ;
                     
                        }
                    }else if( x == maxPos && count == -1){
                        x--;
                        if(bought.empty()){
                              sold.push(price);
                              max_days.insert( max_days.begin()+max_days.size(), max_hold_days) ;
                        }else{
                              bought.pop();
                              max_days.erase(max_days.begin());
                        }
                        money = money + price;
                        string w =  date + ",SELL" ;
                        w = w + "," + to_string(1) +  "," + to_string(price)  + "\n";
                        order << w;
                      
                    }
                }else if ( price  <= value2 ){
                    if (x > minPos  ){
                      if( count == 0){
                          x--;
                        if(bought.empty()){
                              sold.push(price);
                              max_days.insert( max_days.begin()+max_days.size(), max_hold_days) ;
                        }else{
                              bought.pop();
                              max_days.erase(max_days.begin());
                        }
                        money = money + price;
                        string w =  date + ",SELL" ;
                        w = w + "," + to_string(1) +  "," + to_string(price)  + "\n";
                        order << w;
                      }
                    }else if( x == minPos && count == -1){
                         x++;
                        if(sold.empty()){
                               bought.push(price);
                               max_days.insert( max_days.begin()+max_days.size(), max_hold_days) ;
                        }else{
                              sold.pop();
                              max_days.erase(max_days.begin());
                         
                        }
                        money = money - price;
                        string w =  date + ",BUY" ;
                        w = w + "," + to_string(1) + ","  + to_string(price) +  "\n";
                        order << w ;
                    }

                }

         }else{
                if( count == -1){
                     if( x > 1 ){
                         x--;
                        if(bought.empty()){
                              sold.push(price);
                              max_days.insert( max_days.begin()+max_days.size(), max_hold_days) ;
                        }else{
                              bought.pop();
                              max_days.erase(max_days.begin());
                        }
                        money = money + price;
                        string w =  date + ",SELL" ;
                        w = w + "," + to_string(1) +  "," + to_string(price)  + "\n";
                        order << w;

                     }else if( x < -1){
                        x++;
                        if(sold.empty()){
                               bought.push(price);
                               max_days.insert( max_days.begin()+max_days.size(), max_hold_days) ;
                        }else{
                              sold.pop();
                              max_days.erase(max_days.begin());
                         
                        }
                        money = money - price;
                        string w =  date + ",BUY" ;
                        w = w + "," + to_string(1) + ","  + to_string(price) +  "\n";
                        order << w ;


                     }
                }

         }
       if(!max_days.empty()){
         for(int i = 0 ; i < max_days.size() ;i++){
            max_days[i]-- ;
         }
       }
         count = 0 ;
        prevPrice = price;
        string w2 = date + "," + to_string(money) + "\n";
        cashflow << w2;

        queue_front = n_days_data.front();
       
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



int main(int argc, char *argv[])
{

    int x = stoi(argv[1]);
    int n = stoi(argv[2]);
    double p = stod(argv[3]);
    int mhd = stoi(argv[4]);
    double c1 = stod(argv[5]);
    double c2 = stod(argv[6]);
    int maxPos = x;
    int minPos = -x;

    dma_plus_plus(0, n, p, maxPos, minPos, mhd, c1, c2);

    return 0;
}