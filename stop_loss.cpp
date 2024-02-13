#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<bits/stdc++.h>
#include<cmath>

using namespace std;


void pairs(int x, int n, double py,int maxPos, int minPos,double threshold , double stop_loss_threshold){
    
     
    ifstream file("data1.csv");
    ifstream file2("extra_data1.csv");
    ifstream filed("data2.csv");
    ifstream file2d("extra_data2.csv");

    ofstream cashflow("daily_cashflow.csv");
    ofstream order("order_statistics_1.csv");
    ofstream orderd("order_statistics_2.csv");

    cashflow << "Date,Cashflow\n";
    order << "Date,Order_dir,Quantity,Price\n";
    orderd << "Date,Order_dir,Quantity,Price\n";


    if(!file.is_open()){
        cout << "error anup : could not open file!" << endl;
    }

    string line;
    getline(file, line); //header
    getline(file2,line); 
    
    vector<string> extra_data;
    string date;
    string p;
    
    for(int i=0;i<n;i++){
        getline(file2,line);
        istringstream oneline(line);

        getline(oneline, date, ',');
        getline(oneline, p,'\n');

        extra_data.push_back(p);
    }

    reverse(extra_data.begin(),extra_data.end());
    

    string lined;
    getline(filed, lined); //header
    getline(file2d,lined); 
    
    vector<string> extra_datad;
    
    for(int i=0;i<n;i++){
        getline(file2d,lined);
        istringstream oneline1(lined);

        string dated;
        string pd;

        getline(oneline1, dated, ',');
        getline(oneline1, pd,'\n');

        extra_datad.push_back(pd);
    }

    reverse(extra_datad.begin(),extra_datad.end());

    // int count = 0;

    // for(auto i: extra_data){
    //     cout << i << endl;
    //     count++;
    // }

    // cout << count << endl;

    // istringstream oneline(lined);

    // string date;
    string p1;

    // getline(oneline, date, ',');
    // getline(oneline, p1,'\n');
    
    
    string dated;
    string p1d;

    // getline(oneline, dated, ',');
    // getline(oneline, p1d,'\n');
    
    queue <double> bought;
    queue <double> sold;
    queue <double> n_days_data;
    double price = 0;
    double price1 = 0 ;
    double price2 = 0 ;
    double sum = 0;
    double sum_sq = 0;
    double mean = 0;
    double var = 0;
    double stand = 0;
    double queue_front = 0 ;
    double z_score = 0 ;
    double sellprice = 0;
    int iter = 0 ;
    double money = 0;
    int count = 0 ;
    for(int i=1;i<n;i++){
      
        price = stod(extra_data[i]) - stod(extra_datad[i] );
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

        price1 = stod(p1);

        getline(filed,lined);
        
        istringstream oneline1(lined);

        getline(oneline1, dated, ',');
        getline(oneline1, p1d,'\n');

        price2 = stod(p1d);

        price = price1 - price2 ;
        n_days_data.push(price);
        sum += price ;
        sum_sq += pow(price,2);
        
        mean = sum / n;
        var = (sum_sq/n) - pow(mean,2);
        stand = sqrt(var);

        z_score = ( price - mean )/stand ;
        if( (abs(z_score) < stop_loss_threshold)&&( x != 0) ){
            count = -1 ;
        }
     
            if( z_score < -threshold ){
              
                 if(x < maxPos){
                   
                  if( count == 0){
                    x++;
                    if(sold.empty()){
                        bought.push(price);
                    }else{
                        sold.pop();
                    }
                    money = money - price;
                    string w =  date + ",BUY" ;
                    w = w + "," + to_string(1) + ","  + to_string(price1) +  "\n";
                    order << w;
                     string wd =  date + ",SELL" ;
                    wd = wd + "," + to_string(1) +  "," + to_string(price2)  + "\n";
                    orderd << wd;
                  }

                }else if ( x == maxPos && count == -1){
                    x--;
                    if(bought.empty()){
                        sold.push(price);
                    }else{
                        bought.pop();
                    }
                    money = money + price;
                     string wd =  date + ",BUY" ;
                    wd = wd + "," + to_string(1) + ","  + to_string(price2) +  "\n";
                    orderd << wd;
                    string w =  date + ",SELL" ;
                    w = w + "," + to_string(1) +  "," + to_string(price1)  + "\n";
                    order << w;
                }
               
               
            }else if (z_score  > threshold ){
                if (x > minPos){
                  if(count == 0){
                    x--;
                    if(bought.empty()){
                        sold.push(price);
                    }else{
                        bought.pop();
                    }
                    money = money + price;
                     string wd =  date + ",BUY" ;
                    wd = wd + "," + to_string(1) + ","  + to_string(price2) +  "\n";
                    orderd << wd;
                    string w =  date + ",SELL" ;
                    w = w + "," + to_string(1) +  "," + to_string(price1)  + "\n";
                    order << w;
                  }
                }else if( x == minPos && count == -1 ){
                     x++;
                    if(sold.empty()){
                        bought.push(price);
                    }else{
                        sold.pop();
                    }
                    money = money - price;
                    string w =  date + ",BUY" ;
                    w = w + "," + to_string(1) + ","  + to_string(price1) +  "\n";
                    order << w;
                     string wd =  date + ",SELL" ;
                    wd = wd + "," + to_string(1) +  "," + to_string(price2)  + "\n";
                    orderd << wd;
                }
            }
       
        string w2 = date + "," + to_string(money) + "\n";
        cashflow << w2;
        count = 0 ;
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
    int n = stoi(argv[2]);
    double p = stod(argv[3]);
    double threshold = stod(argv[4]);
    double stop_loss_threshold = stod(argv[5]) ;
    // cout << "weeeeeeeeeeeeeeeeeeeeee" << endl;
    int maxPos = x;
    int minPos = -x;


    pairs(0,n,p,maxPos,minPos,threshold,stop_loss_threshold );
    
    return 0;
}