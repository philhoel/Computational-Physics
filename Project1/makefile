all: compile execute

compile:
	g++ project1.cpp -o p -larmadillo -llapack -lblas

execute:
	./p
	python3 read_plot.py general_10.txt general_1k.txt general_1M.txt