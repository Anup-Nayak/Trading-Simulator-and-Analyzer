#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<bits/stdc++.h>
#include<cmath>


using namespace std;

int main(){
    ifstream file("data.csv");
    string line;
    getline(file, line);

    while (getline(file, line)) {
        istringstream ss(line);
        string date;
        double close;
        getline(ss, date, ',');
        ss >> close;
        cout << "Date: " << date << ", Close: " << close << endl;
    }

    file.close();
    

    return 0;
}