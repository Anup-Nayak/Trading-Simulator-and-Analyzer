#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<bits/stdc++.h>
#include<cmath>

using namespace std;

// int basic(int x, int n, int maxPos, int minPos){
//     ifstream file("data.csv");
//     ifstream file2("extra_data.csv");

//     queue <double> bought;
//     queue <double> sold;

//     double money = 0;

//     //setting flags
//     bool incFlag = false;
//     bool decFlag = false;

//     string line;
//     getline(file, line); //header
//     getline(file2,line); 

//     vector<string> extra_data;

//     for(int i=0;i<n;i++){
//         getline(file2,line);
//         istringstream oneline(line);

//         string date;
//         string p;

//         getline(oneline, date, ',');
//         getline(oneline, p,'\n');

//         extra_data.push_back(p);
//     }

//     reverse(extra_data.begin(),extra_data.end());

//     istringstream oneline(line);

//     string date;
//     string p;

//     getline(oneline, date, ',');
//     getline(oneline, p,'\n');

//     double prevPrice = stod(extra_data[0]);
//     int days = 1;
//     double price = 0;
    

//     for(int i=1;i<n;i++){

//         price = stod(extra_data[i]);

//         if(price < prevPrice){
//             incFlag = false;
//             if(decFlag){
//                 days++;
//             }
//             else{
//                 days = 1;
//                 decFlag = true;
//             }
//         }else if(price > prevPrice){
//             decFlag = false;
//             if(incFlag){
//                 days++;
//             }
//             else{
//                 days = 1;
//                 incFlag=true;
//             }
//         }else{
//             days = 0;
//             incFlag = false;
//             decFlag = false;
//         }

//         prevPrice = price;


//     }

//     while(getline(file, line)){
//         istringstream oneline(line);

//         getline(oneline, date, ',');
//         getline(oneline, p,'\n');
        
//         price = stod(p);

//         if(price < prevPrice){
//             incFlag = false;
//             if(decFlag){
//                 days++;
//             }
//             else{
//                 days = 1;
//                 decFlag = true;
//             }
//         }else if(price > prevPrice){
            
//             decFlag = false;
//             if(incFlag){
//                 days++;
//             }
//             else{
//                 days = 1;
//                 incFlag = true;
//             }
//         }else{
//             days = 0;
//             incFlag = false;
//             decFlag = false;
//         }

//         if (days >= n){
//             if(incFlag){
//                 if(x < maxPos){
//                     x++;
//                     if(sold.empty()){
//                         bought.push(price);
//                     }else{
//                         sold.pop();
//                     }
//                     money = money - price;
//                     string w =  date + ",BUY" ;
//                     w = w + "," + to_string(1) + ","  + to_string(price) +  "\n";
//                 }
//             }else if (decFlag){
//                 if (x > minPos){
//                     x--;
//                     if(bought.empty()){
//                         sold.push(price);
//                     }else{
//                         bought.pop();
//                     }
//                     money = money + price;
//                     string w =  date + ",SELL" ;
//                     w = w + "," + to_string(1) +  "," + to_string(price)  + "\n";
//                 }
//             }
//         }
//         prevPrice = price;
//         string w2 = date + "," + to_string(money) + "\n";
//     }

//     file.close();
    

//     if(!(bought.empty() and sold.empty())){
//         while(!bought.empty()){
//             money = money + price ;
//             bought.pop();
//         }
//         while(!sold.empty()){
//             money = money - price ;
//             sold.pop();
//         }
//     }

//     return money;
// }



// int main(int argc, char *argv[]){
//     int n_basic = 7;
//     int n_dma = 50;
//     int n_else = 14;
//     int x = 5;
//     int adx_threshold = 25;
//     int oversold_threshold = 30;
//     int max_hold_days = 28;
//     int c1 = 2;
//     int c2 = 0.2;
//     int p_dma = 2;
//     int p_dmapp = 5;s

//     string startDate = argv[1];
//     string endDate = argv[2];
//     int p_lr = 2;

//     int ans = INT_MIN;

//     int a = basic(0,n_basic,x,-x);
//     int b = linear()

// }