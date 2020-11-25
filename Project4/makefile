all: compile execute

compile:
	g++ main_c.cpp isingmodel.cpp -o main -larmadillo -llapack -lblas -O3

execute:
	./main 1 5 0.05 2 1000000 C_values.csv
	python3 read_c.py C_values.csv
