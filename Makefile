.DEFAULT_GOAL := run

strategy := STRATEGY
symbol := SYMBOL
n := N
x := X
start_date := STARTDATE 
end_date := ENDDATE 

setup: requirements.txt
	pip install -r requirements.txt

run: setup
	python3 main.py $(symbol) $(start_date) $(end_date) $(n)
	ifeq ($(strategy),BASIC)
        g++ basic.cpp -o a.exe
        ./a.exe
    endif

clean:
	rm -rf $(SYMBOL).*

# make SYMBOL=SBIN num_years=1
# make strategy=BASIC symbol=SBIN n=5 x=2 start_date="b" end_date="a"