all: compile execute

compile:
	g++ -std=c++11 main.cpp LinearSystem.cpp -o p -larmadillo -llapack -lblas

execute:
	./p
	python3 python_plot.py this_file.txt 1
	python3 python_plot.py this_file2.txt 5