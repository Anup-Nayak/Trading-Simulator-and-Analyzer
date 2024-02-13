.DEFAULT_GOAL := run

strategy := BASIC
symbol := SBIN
n := 0
x := 0
start_date := 07/02/2024
end_date := 07/02/2024
train_start_date := 06/02/2024
train_end_date := 06/02/2024
p := 0
oversold_threshold := 0
overbought_threshold := 0
threshold := 0
symbol1 := SBIN
symbol2 := SBIN
adx_threshold := 0
max_hold_days := 0
c1 := 0
c2 := 0
stop_loss_threshold := 0

run: 
	python3 main.py $(symbol) $(start_date) $(end_date) $(n) $(strategy) $(train_start_date) $(train_end_date) $(p) $(symbol1) $(symbol2)
	
	g++ decider.cpp -o a.exe
	./a.exe $(strategy) $(x) $(n) $(p) $(start_date) $(oversold_threshold) $(overbought_threshold) $(train_start_date) $(threshold) $(adx_threshold) $(max_hold_days) $(c1) $(c2) $(stop_loss_threshold)
	
	rm -f data_BASIC.csv
	rm -f data_DMA.csv
	rm -f data_DMA++.csv
	rm -f train.csv
	rm -f data_lr.csv
	rm -f data_MACD.csv
	rm -f data_RSI.csv
	rm -f data_ADX.csv
	rm -f extra_data_BASIC.csv
	rm -f extra_data_DMA.csv
	rm -f extra_data_DMA++.csv
	rm -f extra_data_RSI.csv
	rm -f extra_data1_lr.csv
	rm -f extra_data2_lr.csv
	rm -f extra_data2_ADX.csv
	rm -f data1.csv
	rm -f data2.csv
	rm -f extra_data1.csv
	rm -f extra_data2.csv
	rm -f *.exe
	
clean:
	rm -rf $(SYMBOL).*

# make SYMBOL=SBIN num_years=1
# make strategy=BASIC symbol=SBIN n=5 x=2 start_date="b" end_date="a"
# make strategy="LINEAR_REGRESSION" symbol=SBIN x=3 p=2 train_start_date="a" train_end_date="b" start_date="c" end_date="d"
# make strategy=RSI symbol=SBIN x=3 n=14 oversold_threshold=30 overbought_threshold=70 start_date="01/01/2023" end_date="01/01/2024"
# make strategy=ADX symbol=SBIN x=3 n=14 adx_threshold=25 start_date="a" end_date="b"