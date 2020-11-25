import os
import sys

problem = sys.argv[1]
n = int(sys.argv[2])
mcs = int(sys.argv[3])

if problem == "c":

    # Run assignment c
    print("Compiling...")
    os.system("g++ main_c.cpp isingmodel.cpp -o main -larmadillo -llapack -lblas -O3")
    print("Executing...")
    os.system(f"./main 1 5 0.05 {n} {mcs} C_values.csv")
    os.system("python3 read_c.py C_values.csv")

elif problem == "d":

    # Run assignment d
    print("Compiling...")
    os.system("g++ main_d.cpp isingmodel.cpp -o main -larmadillo -llapack -lblas -O3")
    print("Executing...")
    os.system(f"./main {mcs} {n}")
    os.system(f"python3 read_d.py MCvalues.csv {n} {mcs}")

elif problem == "e":

    # Run assignment e
    print("Compiling...")
    os.system("g++ main_e.cpp isingmodel.cpp -o main -larmadillo -llapack -lblas -O3")
    print("Executing...")
    os.system(f"./main {mcs} {n}")
    os.system(f"python3 read_e.py prob.csv {n} {mcs}")

elif problem == "f":

    # Run assignment f
    print("Compiling...")
    os.system("g++ main_f.cpp isingmodel.cpp -o main -larmadillo -llapack -lblas -O3")
    print("Executing...")
    for i in range(40, 101, 20):
        os.system(f"./main 2 2.5 0.005 {i} {mcs} tempV_{i}.csv")

