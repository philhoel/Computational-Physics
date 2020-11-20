all: compile execute

compile:
	g++ main.cpp isingmodel.cpp -o main -larmadillo -llapack -lblas

execute:
	./main
	python3 read.py values.csv 20