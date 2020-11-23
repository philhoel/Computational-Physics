all: compile execute

compile:
	g++ main_d.cpp isingmodel.cpp -o main -larmadillo -llapack -lblas

execute:
	./main 1000000 20
	python3 read.py MCvalues.csv 20 1000000