#pragma once

#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<bits/stdc++.h>
#include<cmath>
#include <pthread.h>

using namespace std;

#include "basic1.cpp"
#include "linear1.cpp"
#include "dma1.cpp"
#include "macd1.cpp"
#include "rsi1.cpp"
#include "adx1.cpp"

void *basicThread(void *);
void *lrThread(void *);
void *dmaThread(void *);
void *macdThread(void *);
void *rsiThread(void *);
void *adxThread(void *);

double a, b, c, d, e, f;

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

void *basicThread(void *) {
    // Call the basic function here
    a = basic(0, n_basic, x, -x);
    pthread_exit(NULL);
}

void *lrThread(void *) {
    // Call the lr function here
    b = lr(p_lr, 0, x, -x);
    pthread_exit(NULL);
}

void *dmaThread(void *) {
    // Call the dma function here
    c = dma(0, n_dma, p_dma, x, -x);
    pthread_exit(NULL);
}

void *macdThread(void *) {
    // Call the macd function here
    d = macd(0, x, -x);
    pthread_exit(NULL);
}

void *rsiThread(void *) {
    // Call the rsi function here
    e = rsi(0, n_else, x, -x, oversold_threshold, overbought_threshold);
    pthread_exit(NULL);
}

void *adxThread(void *) {
    // Call the adx function here
    f = adx(0, n_else, x, -x, adx_threshold);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){

    pthread_t threads[6];
    
    pthread_create(&threads[0], NULL, basicThread, NULL);
    pthread_create(&threads[1], NULL, lrThread, NULL);
    pthread_create(&threads[2], NULL, dmaThread, NULL);
    pthread_create(&threads[3], NULL, macdThread, NULL);
    pthread_create(&threads[4], NULL, rsiThread, NULL);
    pthread_create(&threads[5], NULL, adxThread, NULL);

    // Join threads to the main thread
    for (int i = 0; i < 6; ++i) {
        pthread_join(threads[i], NULL);
    }

    int ans = INT_MIN;
    string best_strat = "BASIC";

    // double a = basic(0,n_basic,x,-x);
    // double b = lr(p_lr,0,x,-x);
    // double c = dma(0,n_dma,p_dma,x,-x);
    // double d = macd(0,x,-x);
    // double e = rsi(0,n_else,x,-x,oversold_threshold,overbought_threshold);
    // double f = adx(0,n_else,x,-x,adx_threshold);

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

    if(f > ans){
        best_strat = "ADX";
        ans = f;
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
    }else if(best_strat == "ADX"){
        adx(0,n_else,x,-x,adx_threshold);
    }
    
}