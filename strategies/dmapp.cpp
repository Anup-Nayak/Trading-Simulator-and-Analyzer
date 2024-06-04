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