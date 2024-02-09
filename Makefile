.DEFAULT_GOAL := run

strategy := STRATEGY
symbol := SYMBOL
n := N
x := X
start_date := STARTDATE 
end_date := ENDDATE 

run: 
	python3 main.py $(symbol) $(start_date) $(end_date) $(n)
	
	g++ decider.cpp -o a.exe
	./a.exe $(strategy) $(x) $(n)
	

clean:
	rm -rf $(SYMBOL).*

# make SYMBOL=SBIN num_years=1
# make strategy=BASIC symbol=SBIN n=5 x=2 start_date="b" end_date="a"