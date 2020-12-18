all: compile execute

compile:
	g++ -std=c++11 main.cpp Solver.cpp Solver2dim.cpp -o main -larmadillo -llapack -lblas -O3

execute:
	./main 2 2000 1000 0.001