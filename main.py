from jugaad_data import nse
import pandas as pd
from dateutil.relativedelta import relativedelta
from datetime import datetime, timedelta
import sys


stock_name = sys.argv[1]
startDate = sys.argv[2]
endDate = sys.argv[3]
dn = sys.argv[4]
strategy = sys.argv[5]
tDateS = sys.argv[6]
tDateE = sys.argv[7]
p = sys.argv[8]

n = int(dn)


file_name = "data.csv"

if(strategy == "LINEAR_REGRESSION"):
    train_file = "train.csv"

    start_date = datetime.strptime(tDateS, "%d/%m/%Y").date()
    # start_date = sdate - timedelta(days = 2)
    end_date = datetime.strptime(tDateE, "%d/%m/%Y").date()

    df = nse.stock_df(stock_name,start_date,end_date)
    header = ['DATE','CLOSE','OPEN','VWAP','LOW','HIGH','NO OF TRADES']



    df = df.loc[:,header]
    df = df.iloc[::-1]

    df['DATE'] = pd.to_datetime(df['DATE'])
    df['DATE'] = df['DATE'].dt.strftime('%d/%m/%Y')

    #csv file
    df.to_csv(train_file, index=False)


    end_date = start_date - timedelta(days = 1)
    start_date = start_date - timedelta(days = 10)
    df = nse.stock_df(stock_name,start_date,end_date)

    df = df.loc[:,header]

    df['DATE'] = pd.to_datetime(df['DATE'])

    # Change date format to DD/MM/YYYY
    df['DATE'] = df['DATE'].dt.strftime('%d/%m/%Y')

    #csv file
    df.to_csv("extra_data1.csv", index=False)







    file_name = "data.csv"

    start_date = datetime.strptime(startDate, "%d/%m/%Y").date()
    # start_date = sdate - timedelta(days = 2)
    end_date = datetime.strptime(endDate, "%d/%m/%Y").date()

    df = nse.stock_df(stock_name,start_date,end_date)
    header = ['DATE','CLOSE','OPEN','VWAP','LOW','HIGH','NO OF TRADES']

    df = df.loc[:,header]
    df = df.iloc[::-1]

    df['DATE'] = pd.to_datetime(df['DATE'])
    df['DATE'] = df['DATE'].dt.strftime('%d/%m/%Y')

    #csv file
    df.to_csv(file_name, index=False)

    end_date = start_date - timedelta(days = 1)
    start_date = start_date - timedelta(days = 10)
    df = nse.stock_df(stock_name,start_date,end_date)

    df = df.loc[:,header]

    df['DATE'] = pd.to_datetime(df['DATE'])

    # Change date format to DD/MM/YYYY
    df['DATE'] = df['DATE'].dt.strftime('%d/%m/%Y')

    #csv file
    df.to_csv("extra_data2.csv", index=False)

    

elif (strategy == "MACD"):
    start_date = datetime.strptime(startDate, "%d/%m/%Y").date()
    end_date = datetime.strptime(endDate, "%d/%m/%Y").date()

    df = nse.stock_df(stock_name,start_date,end_date)

    header = ['DATE','CLOSE']


    df = df.loc[:,header]
    df = df.iloc[::-1]

    df['DATE'] = pd.to_datetime(df['DATE'])

    # Change date format to DD/MM/YYYY
    df['DATE'] = df['DATE'].dt.strftime('%d/%m/%Y')

    #csv file
    df.to_csv(file_name, index=False) 
elif (strategy == "test"):
    
    start_date = datetime.strptime(startDate, "%d/%m/%Y").date()
    end_date = datetime.strptime(endDate, "%d/%m/%Y").date()
    df = nse.stock_df(stock_name,start_date,end_date)

    header = ['DATE','CLOSE']


    df = df.loc[:,header]
    df = df.iloc[::-1]

    df['DATE'] = pd.to_datetime(df['DATE'])

    # Change date format to DD/MM/YYYY
    df['DATE'] = df['DATE'].dt.strftime('%d/%m/%Y')

    #csv file
    df.to_csv(file_name, index=False) 
    #####

    end_date = start_date - timedelta(days = 1)
    start_date = start_date - timedelta(days = 10)
    df = nse.stock_df(stock_name,start_date,end_date)
    header = ['DATE','CLOSE']


    df = df.loc[:,header]

    df['DATE'] = pd.to_datetime(df['DATE'])

    # Change date format to DD/MM/YYYY
    df['DATE'] = df['DATE'].dt.strftime('%d/%m/%Y')

    #csv file
    df.to_csv("extra_data", index=False) 



else:

    sdate = datetime.strptime(startDate, "%d/%m/%Y").date()
    start_date = sdate - timedelta(days = 10*n)

    end_date = datetime.strptime(endDate, "%d/%m/%Y").date()

    df = nse.stock_df(stock_name,start_date,end_date)

    header = ['DATE','CLOSE']

    df = df.loc[:,header]
    df = df.iloc[::-1]

    df['DATE'] = pd.to_datetime(df['DATE'])

    # Change date format to DD/MM/YYYY
    df['DATE'] = df['DATE'].dt.strftime('%d/%m/%Y')

    #csv file
    df.to_csv(file_name, index=False)


