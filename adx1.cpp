#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <bits/stdc++.h>
#include <cmath>

using namespace std;

double adx(int x, int n, int maxPos, int minPos, int adx_threshold)
{

    ifstream file("data_ADX.csv");
    ifstream file1("extra_data2_ADX.csv");
    ofstream cashflow("daily_cashflow.csv");
    ofstream order("order_statistics.csv");

    cashflow << "Date,Cashflow\n";
    order << "Date,Order_dir,Quantity,Price\n";

    if (!file.is_open())
    {
        cout << "error anup : could not open file!" << endl;
    }

    queue<double> bought;
    queue<double> sold;

    double money = 0;

    string line;

    getline(file1, line);
    getline(file, line);

    getline(file1, line);

    istringstream oneline1(line);

    string date;
    string p1;
    string High;
    string Low;
    string Prev;

    getline(oneline1, date, ',');
    getline(oneline1, Prev, ',');
    getline(oneline1, High, ',');

    getline(oneline1, Low, '\n');

    double High_val;
    double Low_val;

    double High_0 = 0;
    double High_t = 0.0;
    double Low_0 = 0;
    double Low_t = 0.0;
    double Close_0 = 0.0;
    double Close_t = 0.0;
    double DM_plus = 0.0;
    double DM_minus = 0.0;
    double DI_plus_t = 0.0;
    double DI_minus_0 = 0.0;
    double DI_plus_0 = 0.0;
    double DI_minus_t = 0.0;
    double TR_t = 0.0;
    double price;
    double PrevClose = stod(Prev);
    double ATR_t;
    double TR_0;
    double ATR_0 = TR_0;
    double value1;
    double value2;

    double DX = 0;
    double ADX_t = 0;
    double ADX_0 = 0;

    High_t = stod(High);
    Low_t = stod(Low);
    price = stod(Prev);

    getline(file, line);
    istringstream oneline(line);

    getline(oneline, date, ',');
    getline(oneline, p1, ',');
    getline(oneline, High, ',');
    getline(oneline, Low, '\n');

    High_t = stod(High);
    Low_t = stod(Low);
    price = stod(p1);
    TR_t = High_t - PrevClose;
    if (High_t - Low_t > High_t - PrevClose)
    {
        TR_t = High_t - Low_t;
    }
    if (Low_t - PrevClose > TR_t)
    {
        TR_t = Low_t - PrevClose;
    }

    DM_plus = max(0.0, High_t - High_0);
    DM_minus = max(0.0, Low_t - Low_0);
    ATR_t = TR_t;

    DI_plus_t = DM_plus / ATR_t;
    DI_minus_t = DM_minus / ATR_t;
    if (DI_plus_t + DI_minus_t > 0)
    {
        DX = ((DI_plus_t - DI_minus_t) / (DI_plus_t + DI_minus_t)) * 100;
    }
    else if (DI_plus_t + DI_minus_t == 0)
    {
        DX = 0;
    }
    ADX_t = DX;
    if (ADX_t > adx_threshold)
    {
        if (x < maxPos)
        {
            x++;
            if (sold.empty())
            {
                bought.push(price);
            }
            else
            {
                sold.pop();
            }
            money = money - price;
            string w = date + ",BUY";
            w = w + "," + to_string(1) + "," + to_string(price) + "\n";
            order << w;
        }
    }
    else if (ADX_t > adx_threshold)
    {
        if (x > minPos)
        {
            x--;
            if (bought.empty())
            {
                sold.push(price);
            }
            else
            {
                bought.pop();
            }
            money = money + price;
            string w = date + ",SELL";
            w = w + "," + to_string(1) + "," + to_string(price) + "\n";
            order << w;
        }
    }
    High_0 = High_t;
    Low_0 = Low_t;

    DI_plus_0 = DI_plus_t;
    DI_minus_0 = DI_minus_t;

    PrevClose = price;

    ATR_0 = ATR_t;
    ADX_0 = ADX_t;

    while (getline(file, line))
    {

        // getline(file, line);
        istringstream oneline(line);

        getline(oneline, date, ',');
        getline(oneline, p1, ',');
        getline(oneline, High, ',');
        getline(oneline, Low, '\n');

        price = stod(p1);
        TR_t = High_t - PrevClose;
        if (High_t - Low_t > High_t - PrevClose)
        {
            TR_t = High_t - Low_t;
        }
        if (Low_t - PrevClose > TR_t)
        {
            TR_t = Low_t - PrevClose;
        }
        DM_plus = max(0.0, High_t - High_0);
        DM_minus = max(0.0, Low_t - Low_0);

        ATR_t = (2 / 1 + n) * (TR_t - ATR_0) + ATR_0;

        value1 = DM_plus / ATR_t;
        value2 = DM_minus / ATR_t;

        DI_plus_t = (2 / 1 + n) * ((value1 - DI_plus_t)) + (DI_plus_0);
        DI_minus_t = (2 / 1 + n) * ((value2 - DI_plus_t)) + (DI_plus_0);

        if (DI_plus_t + DI_minus_t > 0)
        {
            DX = ((DI_plus_t - DI_minus_t) / (DI_plus_t + DI_minus_t)) * 100;
        }
        else if (DI_plus_t + DI_minus_t == 0)
        {
            DX = 0;
        }
        ADX_t = (2 / (1 + n)) * (DX - ADX_0) + ADX_0;

        if (ADX_t > adx_threshold)
        {
            if (x < maxPos)
            {
                x++;
                if (sold.empty())
                {
                    bought.push(price);
                }
                else
                {
                    sold.pop();
                }
                money = money - price;
                string w = date + ",BUY";
                w = w + "," + to_string(1) + "," + to_string(price) + "\n";
                order << w;
            }
        }
        else if (ADX_t < adx_threshold)
        {
            if (x > minPos)
            {
                x--;
                if (bought.empty())
                {
                    sold.push(price);
                }
                else
                {
                    bought.pop();
                }
                money = money + price;
                string w = date + ",SELL";
                w = w + "," + to_string(1) + "," + to_string(price) + "\n";
                order << w;
            }
        }
        High_0 = High_t;
        Low_0 = Low_t;

        DI_plus_0 = DI_plus_t;
        DI_minus_0 = DI_minus_t;

        PrevClose = price;

        ATR_0 = ATR_t;
        ADX_0 = ADX_t;
        string w2 = date + "," + to_string(money) +"\n";
        cashflow << w2;
    }

    file.close();

    cashflow.close();
    order.close();

    if (!(bought.empty() and sold.empty()))
    {
        while (!bought.empty())
        {
            money = money + price;
            bought.pop();
        }
        while (!sold.empty())
        {
            money = money - price;
            sold.pop();
        }
    }
    ofstream final("final_pnl.txt");
    final << to_string(money);
    final.close();
    return money;
}