all: compile execute

compile:
	g++ project1.cpp -o p -larmadillo -llapack -lblas

execute:
	./p
	python3 read_plot.py general_10.txt special_10.txt analytic_10.txt
	python3 read_plot.py general_100.txt special_100.txt analytic_100.txt
	python3 read_plot.py general_1k.txt special_1k.txt analytic_1k.txt