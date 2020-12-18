all: compile execute

compile:
	g++ -std=c++11 main.cpp Solver.cpp Solver2dim.cpp -o main -larmadillo -llapack -lblas -O3

execute:
	./main 3 200 1000000 0.00000000001