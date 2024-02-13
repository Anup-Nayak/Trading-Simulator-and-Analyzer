#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<bits/stdc++.h>
#include<cmath>

using namespace std;

int main(int argc, char *argv[]){
    int n_basic = 7;
    int n_dma = 50;
    int n_else = 14;
    int x = 5;
    int adx_threshold = 25;
    int oversold_threshold = 30;
    int max_hold_days = 28;
    int c1 = 2;
    int c2 = 0.2;
    int p_dma = 2;
    int p_dmapp = 5;

    string startDate = argv[1];
    string endDate = argv[2];
    int p_lr = 2;

    int ans = INT_MIN;

}