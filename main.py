from jugaad_data import nse
import pandas as pd
from dateutil.relativedelta import relativedelta
from datetime import datetime, timedelta
import sys


stock_name = sys.argv[1]
startDate = sys.argv[2]
endDate = sys.argv[3]
n = sys.argv[4]

dn = int(n)

# try:
#     global year
# except ValueError:
#     print("That's not a valid input for number of years, please input non-negative integer")
#     quit()

file_name = "data.csv"

sdate = datetime.strptime(startDate, "%d/%m/%Y").date()
start_date = sdate - timedelta(days = dn)

end_date = datetime.strptime(endDate, "%d/%m/%Y").date()

df = nse.stock_df(stock_name,start_date,end_date)

header = ['DATE','CLOSE']


df = df.loc[:,header]

#csv file
df.to_csv(file_name, index=False)


