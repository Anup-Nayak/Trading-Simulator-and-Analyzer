from jugaad_data import nse
import pandas as pd
from dateutil.relativedelta import relativedelta
from datetime import date
import sys


stock_name = sys.argv[1]
yearI = sys.argv[2]
try:
    global year
    year = int(yearI)
except ValueError:
    print("That's not a valid input for number of years, please input non-negative integer")
    quit()

df =nse.index_csv(symbol="NIFTY 50", from_date=date(2015,1,1),
            to_date=date(2020,1,30), output="NIFTY.csv")

file_name = "data.csv"

today_date = date.today()
start_date = today_date - relativedelta(years = year)

df = nse.stock_df(stock_name,start_date,today_date)

header = ['DATE','CLOSE']


df = df.loc[:,header]

#csv file
df.to_csv(file_name, index=False)


