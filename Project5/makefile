all: compile execute

compile:
	g++ -std=c++11 main.cpp Solver.cpp -o main -larmadillo -llapack -lblas -O3

execute:
	./main