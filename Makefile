all: clean
	g++ -std=c++17 *.cc -o a.out

clean:
	rm -rf ./a.out
	
