all: compile execute

compile:
	g++ main.cpp isingmodel.cpp System.cpp -o main -larmadillo -llapack -lblas

execute:
	./main
	python3 read.py tempValues.csv 20 1000000