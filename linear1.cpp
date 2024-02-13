#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<bits/stdc++.h>
#include<cmath>

using namespace std;

void printMatrix(const vector<vector<double>>& vec) {
    
    for (const auto& row : vec) {
        for (const auto& element : row) {
            cout << element << " ";
        }
        cout << endl; 
    }
}

vector <vector <double>> calculate_coefficients(vector<vector<double>> &y){
    ifstream file("train.csv");
    ifstream file1("extra_data1_lr.csv");
    vector <vector <double>> matrix;
    string line;

    getline(file,line); //header
    getline(file1,line);

    string date;
    string closep;
    string openp;
    string vwapp;
    string lowp;
    string highp;
    string tradesp;
    string open;

    double closepv;
    double openpv;
    double vwappv;
    double lowpv;
    double highpv;
    double tradespv;
    double openv;


    getline(file1,line); //first value
    istringstream oneline(line);

    getline(oneline, date,',');
    getline(oneline, closep,',');
    getline(oneline, openp,',');
    getline(oneline, vwapp,',');
    getline(oneline, lowp,',');
    getline(oneline, highp,',');
    getline(oneline, tradesp,'\n');

    closepv = stod(closep);
    openpv = stod(openp);
    vwappv = stod(vwapp);
    lowpv = stod(lowp);
    highpv = stod(highp);
    tradespv = stod(tradesp);

    while(getline(file,line)){
        istringstream oneline(line);

        getline(oneline, date,',');
        getline(oneline, closep,',');
        getline(oneline, openp,',');
        getline(oneline, vwapp,',');
        getline(oneline, lowp,',');
        getline(oneline, highp,',');
        getline(oneline, tradesp,'\n');

        openv = stod(openp);

        vector<double> temp = {closepv,openpv,vwappv,lowpv,highpv,tradespv,openv};
        matrix.push_back(temp);

        closepv = stod(closep);
        openpv = stod(openp);
        vwappv = stod(vwapp);
        lowpv = stod(lowp);
        highpv = stod(highp);
        tradespv = stod(tradesp);

        y.push_back({closepv});

    }
    file.close();
    file1.close();
    return matrix;
}

vector <vector <double>> transpose_matrix(vector <vector <double>> &matrix){
    
    if(matrix.empty() or matrix[0].empty()){
        return {};
    }
    int rows = matrix.size();
    int cols = matrix[0].size();

    vector<vector<double>> transpose(cols, vector<double>(rows));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transpose[j][i] = matrix[i][j];
        }
    }

    return transpose;

}

vector <vector <double>> multiply_matrix(vector <vector <double>> &m1, vector <vector <double>> &m2){
    if (m1.empty() || m1[0].empty() || m2.empty() || m2[0].empty()) {
        return {}; 
    }

    if (m1[0].size() != m2.size()) {
        cout << "these matrices cannot be multiplied!" << endl;
        return {};
    }

    
    int rows1 = m1.size();
    int cols1 = m1[0].size();
    int cols2 = m2[0].size();

    vector<vector<double>> result(rows1, vector<double>(cols2, 0.0));

    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            for (int k = 0; k < cols1; ++k) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    return result;
}

void matrix_inverse(vector<vector<double>> &A ,vector<vector<double>> &result){
    int n = A.size();
    vector<vector<double> > B(n, vector<double>(n * 2, 0));
    // Augmenting matrix with identity matrix of similar dimensions
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            B[i][j] = A[i][j];
        }
        B[i][i + n] = 1;
    }

    // Applying Gauss Jordan Elimination
    for (int i = 0; i < n; i++)
    {
        if (B[i][i] == 0.0)
        {
            std::cerr << "Matrix is singular." << std::endl;
            exit(1);
        }

        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                double ratio = B[j][i] / B[i][i];
                for (int k = 0; k < 2 * n; k++)
                {
                    B[j][k] -= ratio * B[i][k];
                }
            }
        }
    }

    // Row operation to make principal diagonal element to 1
    for (int i = 0; i < n; i++)
    {
        double divisor = B[i][i];
        for (int j = 0; j < 2 * n; j++)
        {
            B[i][j] /= divisor;
        }
    }

    // Extracting the right half of the augmented matrix (the inverted matrix)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // cout << "10000000000000000000" << endl;
            result[i][j] = B[i][j + n];
        }
    }

}

double lr(int p,int x, int maxPos, int minPos){

  ofstream cashflow("daily_cashflow.csv");
  ofstream order("order_statistics.csv");

  cashflow << "Date,Cashflow\n";
  order << "Date,Order_dir,Quantity,Price\n";


  queue <double> bought;
  queue <double> sold;

  double money = 0;

  vector <vector<double>> y = {};
  vector <vector <double>> m = calculate_coefficients(y);
  // printMatrix(m);
  vector <vector <double>> t = transpose_matrix(m);
  vector <vector <double>> mul = multiply_matrix(t,m);
  
  int n = mul.size();

  vector<vector<double>> inv(n, vector<double>(n, 0));

  matrix_inverse(mul,inv);

  vector <vector <double>> a = multiply_matrix(inv,t);
  vector <vector <double>> ans = multiply_matrix(a,y);
  // printMatrix(ans);

  vector<double> coeff;

  for(auto i : ans){
    for(auto j : i){
      coeff.push_back(j);
    }
  }

  // for(auto i : coeff){
  //   cout << i << endl;
  // }

  double value1;
  double value2;

  double b0 = 1.0;
  double b1 = coeff[0];
  double b2 = coeff[1];
  double b3 = coeff[2];
  double b4 = coeff[3];
  double b5 = coeff[4];
  double b6 = coeff[5];
  double b7 = coeff[6];


  ifstream file("data_lr.csv");
  ifstream file1("extra_data2_lr.csv");
  vector <vector <double>> matrix;
  string line;

  getline(file,line); //header
  getline(file1,line);

  string date;
  string closep;
  string openp;
  string vwapp;
  string lowp;
  string highp;
  string tradesp;
  string open;

  double closepv;
  double openpv;
  double vwappv;
  double lowpv;
  double highpv;
  double tradespv;
  double openv;


  getline(file1,line); //first value
  istringstream oneline(line);

  getline(oneline, date,',');
  getline(oneline, closep,',');
  getline(oneline, openp,',');
  getline(oneline, vwapp,',');
  getline(oneline, lowp,',');
  getline(oneline, highp,',');
  getline(oneline, tradesp,'\n');

  closepv = stod(closep);
  openpv = stod(openp);
  vwappv = stod(vwapp);
  lowpv = stod(lowp);
  highpv = stod(highp);
  tradespv = stod(tradesp);

  while(getline(file,line)){
      istringstream oneline(line);

      getline(oneline, date,',');
      getline(oneline, closep,',');
      getline(oneline, openp,',');
      getline(oneline, vwapp,',');
      getline(oneline, lowp,',');
      getline(oneline, highp,',');
      getline(oneline, tradesp,'\n');

      openv = stod(openp);

      double predicted_price = b0 + b1*closepv + b2*openpv + b3*vwappv + b4*lowpv + b5*highpv + b6*tradespv + b7*openv ;

      closepv = stod(closep);
      openpv = stod(openp);
      vwappv = stod(vwapp);
      lowpv = stod(lowp);
      highpv = stod(highp);
      tradespv = stod(tradesp);
      
    //   cout << predicted_price << " " << closepv << endl;

      // value1 = ((100 + p )/(100))*closepv ;
      // value2 = ((100 - p )/(100))*closepv ;

      if(((predicted_price - closepv)/closepv)*100 > p){
        if(x < maxPos){
            x++;
            if(sold.empty()){
                bought.push(closepv);
            }else{
                sold.pop();
            }
            money = money - closepv;
            string w =  date + ",BUY" ;
            w = w + "," + to_string(1) + ","  + to_string(closepv) +  "\n";
            order << w;
        }
      }else if(((closepv - predicted_price)/closepv)*100 > p){
        if (x > minPos){
            x--;
            if(bought.empty()){
                sold.push(closepv);
            }else{
                bought.pop();
            }
            money = money + closepv;
            string w =  date + ",SELL" ;
            w = w + "," + to_string(1) +  "," + to_string(closepv)  + "\n";
            order << w;
        }
      }

      string w2 = date + "," + to_string(money) + "\n";
      cashflow << w2;
      
      // if(predicted_price > value1){
      //   cout << "buy" << endl;
      // }else if(predicted_price < value2 ){
      //   cout << "sell" << endl;
      // }


  }
  cashflow.close();
  order.close();
  file.close();
  file1.close();

  if(!(bought.empty() and sold.empty())){
      while(!bought.empty()){
          money = money + closepv ;
          bought.pop();
      }
      while(!sold.empty()){
          money = money - closepv ;
          sold.pop();
      }
  }
  ofstream final("final_pnl.txt");
  final << to_string(money);
  final.close();
    return money;
  
}