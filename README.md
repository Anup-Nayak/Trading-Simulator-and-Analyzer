
# Trading Simulator & Analyzer

Implementation of some trading strategies, backtest them on past
data, and get some insights into the world of algorithmic trading.


## Installation

- Clone the Repository using
  ```
   git clone https://github.com/Anup-Nayak/Trading-Simulator-and-Analyzer.git
   ```

- *Install dependencies*
  ```
  pip install -r requirements.txt
  ```
  
- Run the simulator using appropriate make commands, e.g, 

```bash
make strategy="LINEAR_REGRESSION" symbol=SBIN x=3 p=2 train_start_date="a"
train_end_date="b" start_date="c" end_date="d"
```
## RESULT

Running the make commands with a strategy name uses that strategy to perform trades from *start_date* to *end_date* on a stock, it then generates these 3 files.

**daily_cashflow.csv** -  stores date, and the cashflow presently, for all trading days.

**order_statistics.csv** -   store date, order direction (BUY or SELL), quantity, and price at which the trade was made, only for days when trade is made.

**final_pnl.txt** - final profit/loss (along with sign) after squaring off all position.
## Constraints and Assumptions


• To simplify our analysis, we will only be considering closing price for all stocks.

• Since we should not hold any positions at the end of the trading period, any positions held is squared-off at the closing price of end date (If the end date is a non-trading day,trade is closed at the price of last trading day before end date).

• The max position we can take is +x, and the min position we can have is -x. Thus, our position always stays in [-x, +x]
## 1 Momentum Based Strategies

### 1.1 Basic Strategy

• If the price has been monotonically increasing for the last n days, we will buy 1 share today.
• If the price has been monotonically decreasing for the last n days, we will sell 1 share today.

#### Parameters

• n - The number of past days to consider.                                       
• x - The maximum position allowed.

#### Implementation

```
make strategy=BASIC symbol=SBIN n=5 x=2 start_date="b" end_date="a"
```

### 1.2 Trend-based Strategy, n-Day Moving Average (DMA)

• Calculate the mean price of past n days. Call this DMA. Also calculate the standard deviation.

• If the current price is greater than DMA by ≥ p standard deviations (sd calculated over same period), buy 1 share. Otherwise, if the current price is less than DMA by ≥ p s.d., sell 1.

#### Parameters

• n - The number of past days to consider for average.                                       
• x - The maximum position allowed.              
• p - The standard deviation threshold

#### Implementation

```
make strategy=DMA symbol=SBIN n=50 x=3 p=2 start_date="a" end_date="b"
```

### 1.3 Improving DMA

• Implement stop-loss: If we are not able to close positions for quite some time, we close it forcefully to avoid losing more money. Thus, given a parameter, max hold days, we close our positions after max hold days, if we were not able to close otherwise.

• Smoothing Factor: Instead of calculating average of price of last n days directly, we will instead use the an algorithm to calculate adaptive Moving Average. 

*Refer Algorithm used from tradingSim.pdf .*

#### Parameters

• x - The maximum position allowed        
• p - Percent change needed     
• n - Number of past days needed to calculate ER  
• max_hold_days - Maximum number of days we can hold position  
• c1 - algoritmic variable  
• c2 - algoritmic variable

#### Implementation

```
make strategy="DMA++" symbol=SBIN x=4 p=5 n=14 max_hold_days=28 c1=2 c2=0.2
start_date="a" end_date="b"
```

### 1.4 Using Indicators

### 1.4.1 MACD

• Calculate the Exponential Weighted Mean (EWM) and use a signal to buy and sell.  

*Refer Algorithm used from tradingSim.pdf .*

#### Implementation

```
make strategy=MACD symbol=SBIN x=3 start_date="a" end_date="b"
```


### 1.4.2 Relative Strength Index (RSI)

• RSI is one of the most used indicators for trend analysis.   
• We calculate Relative Strength and compare it against oversold_threshold and overbought_threshold to generate buy/sell signals.

*Refer Algorithm used from tradingSim.pdf .*

#### Implementation

```
make strategy=RSI symbol=SBIN x=3 n=14 oversold_threshold=30 overbought_threshold=70
start_date="a" end_date="b"
```

### 1.4.3 ADX

• Explaining this Algorithm intuitively is a bit difficult, mostly mathematics.   

*Refer Algorithm used from tradingSim.pdf .*

#### Implementation

```
make strategy=ADX symbol=SBIN x=3 n=14 adx_threshold=25 start_date="a" end_date="b"
```
## 2 Linear Regression

We will use Linear Regression to predict the Price of Stock at day t.

Particularly, we will use the following Linear Regression Equation -   

`
Close(t) = β0 + β1*Close(t−1) + β2*Open(t−1) + β3*VWAP(t−1) + β4*Low(t−1) +         β5*High(t−1) + β6*(No of Trades)(t−1) + β7*Open(t)
`

• Learn the parameters using historical data. The data you will use will be
from train_start_date to train_end_date.  
• Use the parameters and the equation to predict the close price for the current day.  
• If the predicted price is greater than the actual price by ≥ p%, we buy the stock.  
• If the predicted price is less than the actual price by ≥ p%, we sell the stock.

#### Parameters

• x - The max position  
• train_start_date, train_end_date  
• p - The percent different required  

#### Implementation

```
make strategy="LINEAR_REGRESSION" symbol=SBIN x=3 p=2 train_start_date="a"
train_end_date="b" start_date="c" end_date="d"
```

## 3 Best of All

We define a ”best-of-all” strategy as the strategy which gives best (overall) PnL (could be negative) among all the strategies discussed so far.

To do so, we would not want to wait for each strategy to start and finish execution. Instead, we will run all the strategies in parallel. I have used pthreads for the same.

#### Implementation

```
make strategy="BEST_OF_ALL" symbol=SBIN start_date="a" end_date="b"
```

## 4 Mean-Reverting Pairs Trading Strategy

In this strategy, we move on to implement a strategy which is based on a pair of stocks, rather than a single stock. To make things simple, we will assume that we have already tested for correlation/cointegration between the stocks, and the pair is ready to use for the strategy.

In Pairs Trading Strategy, instead of betting on the price of a single stock, we instead bet on the spread between the price of a pair of stocks. Thus, even if both the prices are increasing or decreasing, we only care about the spread between the two.  

When the z-score is high, we expect the spread to return to its mean, and hence, we short the spread (sell the spread). Similarly, when z-score is low, we long the spread.

*Refer Algorithm used from tradingSim.pdf .*

#### Parameters

• x - The maximum position allowed  
• n - The lookback period  
• threshold - The z-score threshold  

#### Implementation

```
make strategy=PAIRS symbol1=SBIN symbol2=ADANIENT x=5 n=20 threshold=2
start_date="a" end_date="b"
```

### 4.1 Stop-Loss in Pairs Trading Strategy

Often, we are stuck with unwanted positions in pairs trading strategy, and we want to clear them off to take newer positions and earn profits .

Thus, we include stop-loss based constraint in our strategy, We have already seen time based stop-loss in DMA. Here we will be looking at Loss based Stop-Loss Strategy.

• Since we had taken position when the z-score crossed the threshold (in either direction), we expected the z-score to return to the mean. Instead, if the z-score has moved in the unexpected direction, we may want to close our positions.  

• Given stop_loss_threshold, we will close our (single) position when the z-score crosses the stop_loss_threshold. Note that we will use the same mean and standard deviation to calculate z-score at which we had opened the position.

#### Implementation

```
make strategy=PAIRS symbol1=SBIN symbol2=ADANIENT x=5 n=20 threshold=2
stop_loss_threshold=4 start_date="a" end_date="b"
```
## References

• https://www.investopedia.com/terms/m/macd.asp  
• https://www.investopedia.com/terms/a/adx.asp  
• https://www.investopedia.com/terms/r/rsi.asp  
• https://www.investopedia.com/terms/m/mlr.asp  
• https://scholarworks.uni.edu/cgi/viewcontent.cgi?article=1016&context=jucie  
• https://en.wikipedia.org/wiki/Linear_regression  
