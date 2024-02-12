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

run: 
	python3 main.py $(symbol) $(start_date) $(end_date) $(n) $(strategy) $(train_start_date) $(train_end_date) $(p)
	
	g++ decider.cpp -o a.exe
	./a.exe $(strategy) $(x) $(n) $(p) $(start_date)
	

clean:
	rm -rf $(SYMBOL).*

# make SYMBOL=SBIN num_years=1
# make strategy=BASIC symbol=SBIN n=5 x=2 start_date="b" end_date="a"
# make strategy="LINEAR_REGRESSION" symbol=SBIN x=3 p=2 train_start_date="a" train_end_date="b" start_date="c" end_date="d"