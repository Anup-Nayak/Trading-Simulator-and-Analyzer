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
symbol1 = sys.argv[9]
symbol2 = sys.argv[10]

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
    df.to_csv("extra_data1_lr.csv", index=False)






    file_name = "data_lr.csv"

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
    df.to_csv("extra_data2_lr.csv", index=False)

elif (strategy == "ADX"):

    file_name = "data_adx.csv"

    start_date = datetime.strptime(startDate, "%d/%m/%Y").date()
    # start_date = sdate - timedelta(days = 2)
    end_date = datetime.strptime(endDate, "%d/%m/%Y").date()

    df = nse.stock_df(stock_name,start_date,end_date)
    header = ['DATE','CLOSE','HIGH','LOW']

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
    df.to_csv("extra_data2_adx.csv", index=False)

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
    df.to_csv("data_MACD.csv", index=False) 

elif (strategy == "PAIRS"):

    start_date = datetime.strptime(startDate, "%d/%m/%Y").date()
    end_date = datetime.strptime(endDate, "%d/%m/%Y").date()
    df1 = nse.stock_df(symbol1,start_date,end_date)

    header = ['DATE','CLOSE']

    df1 = df1.loc[:,header]
    df1 = df1.iloc[::-1]

    df1['DATE'] = pd.to_datetime(df1['DATE'])

    # Change date format to DD/MM/YYYY
    df1['DATE'] = df1['DATE'].dt.strftime('%d/%m/%Y')

    #csv file
    df1.to_csv("data1.csv", index=False) 

    

    end_date = start_date - timedelta(days = 1)
    start_date = start_date - timedelta(days = 5*n)
    df1 = nse.stock_df(symbol1,start_date,end_date)
    header = ['DATE','CLOSE']

    df1 = df1.loc[:,header]

    df1['DATE'] = pd.to_datetime(df1['DATE'])

    # Change date format to DD/MM/YYYY
    df1['DATE'] = df1['DATE'].dt.strftime('%d/%m/%Y')

    #csv file
    df1.to_csv("extra_data1.csv", index=False)








    start_date = datetime.strptime(startDate, "%d/%m/%Y").date()
    end_date = datetime.strptime(endDate, "%d/%m/%Y").date()
    df2 = nse.stock_df(symbol2,start_date,end_date)

    header = ['DATE','CLOSE']

    df2 = df2.loc[:,header]
    df2 = df2.iloc[::-1]

    df2['DATE'] = pd.to_datetime(df2['DATE'])

    # Change date format to DD/MM/YYYY
    df2['DATE'] = df2['DATE'].dt.strftime('%d/%m/%Y')

    #csv file
    df2.to_csv("data2.csv", index=False) 

    

    end_date = start_date - timedelta(days = 1)
    start_date = start_date - timedelta(days = 5*n)
    df2 = nse.stock_df(symbol2,start_date,end_date)
    header = ['DATE','CLOSE']

    df2 = df2.loc[:,header]

    df2['DATE'] = pd.to_datetime(df2['DATE'])

    # Change date format to DD/MM/YYYY
    df2['DATE'] = df2['DATE'].dt.strftime('%d/%m/%Y')

    #csv file
    df2.to_csv("extra_data2.csv", index=False)

elif(strategy == "BEST_OF_ALL"):
    print("yes")

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

elif(strategy == "BASIC" or strategy == "DMA" or strategy == "DMA++" or strategy == "RSI" or strategy == "ADX") :


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
    file_name = "data_"+strategy+".csv"
    df.to_csv(file_name, index=False) 





    end_date = start_date - timedelta(days = 1)
    start_date = start_date - timedelta(days = 5*n)
    df = nse.stock_df(stock_name,start_date,end_date)
    header = ['DATE','CLOSE']

    df = df.loc[:,header]

    df['DATE'] = pd.to_datetime(df['DATE'])

    # Change date format to DD/MM/YYYY
    df['DATE'] = df['DATE'].dt.strftime('%d/%m/%Y')

    #csv file
    file_name = "extra_data_"+strategy+".csv"
    df.to_csv(file_name, index=False)


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


