#pragma once

#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<bits/stdc++.h>
#include<cmath>

using namespace std;

#include "basic1.cpp"
#include "linear1.cpp"
#include "dma1.cpp"
#include "macd1.cpp"
#include "rsi1.cpp"

int main(int argc, char *argv[]){
    int n_basic = 7;
    int n_dma = 50;
    int n_else = 14;
    int x = 5;
    int adx_threshold = 25;
    int oversold_threshold = 30;
    int overbought_threshold = 70;
    int max_hold_days = 28;
    int c1 = 2;
    int c2 = 0.2;
    int p_dma = 2;
    int p_dmapp = 5;
    int p_lr = 2;


    int ans = INT_MIN;
    string best_strat = "BASIC";

    double a = basic(0,n_basic,x,-x);
    double b = lr(p_lr,0,x,-x);
    double c = dma(0,n_dma,p_dma,x,-x);
    double d = macd(0,x,-x);
    double e = rsi(0,n_else,x,-x,oversold_threshold,overbought_threshold);

    if(a > ans){
        best_strat = "BASIC";
        ans = a;
    }

    if(b > ans){
        best_strat = "LINEAR";
        ans = b;
    }

    if(c > ans){
        best_strat = "DMA";
        ans = c;
    }

    if(d > ans){
        best_strat = "MACD";
        ans = d;
    }

    if(e > ans){
        best_strat = "RSI";
        ans = e;
    }

    cout << best_strat << " is the winner!" << endl;

    if(best_strat == "BASIC"){
        basic(0,n_basic,x,-x);
    }else if(best_strat == "LINEAR"){
        lr(p_lr,0,x,-x);
    }else if(best_strat == "DMA"){
        dma(0,n_dma,p_dma,x,-x);
    }else if(best_strat == "MACD"){
        macd(0,x,-x);
    }else if(best_strat == "RSI"){
        rsi(0,n_else,x,-x,oversold_threshold,overbought_threshold);
    }
    
}