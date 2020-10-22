all: compile execute

compile:
	g++ -std=c++11 main.cpp solarsystem.cpp -o p -larmadillo -llapack -lblas

execute:
	./p
	python3 read_script.py