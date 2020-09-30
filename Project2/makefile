all: compile execute

compile:
	g++ -std=c++11 main.cpp LinearSystem.cpp tests.cpp -o p -larmadillo -llapack -lblas
	g++ tests.cpp LinearSystem.cpp -o t -larmadillo -llapack -lblas

execute:
	./t
	./p