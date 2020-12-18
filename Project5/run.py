import numpy as np
import os
import sys
import argparse

parser = argparse.ArgumentParser(
        description="Run Script for Project 5"
    )

#default = True

parser.add_argument('Problem', help='Which problem to solve', type=int)
parser.add_argument('Default', help='Wether to run deafult or not', type=bool)

args = parser.parse_args()

if args.Default == True:

    # 1D problem
    if args.Problem == 1:

        print("Compiling...")
        os.system("g++ -std=c++11 main.cpp Solver.cpp Solver2dim.cpp -o main -larmadillo -llapack -lblas -O3")
        print("Executing...")
        os.system("./main 1 100000 100 0.001")
        print("Plotting...")
        os.system("python3 read1D.py ForwardEuler FE.csv")
        os.system("python3 read1D.py BackwardEuler BE.csv")
        os.system("python3 read1D.py Crank-Nicolson CN.csv")
    
    # Checking error for 1D
    elif args.Problem == 2:

        print("Compiling...")
        os.system("g++ -std=c++11 main.cpp Solver.cpp Solver2dim.cpp -o main -larmadillo -llapack -lblas -O3")
        print("Executing...")
        os.system("./main 2 2000 1000 0.001")
        print("Plotting...")
        os.system("python3 readError.py FE.csv BE.csv CN.csv anal.csv anal2.csv")

    # Running 2D
    elif args.Problem == 3:

        print("Compiling...")
        os.system("g++ -std=c++11 main.cpp Solver.cpp Solver2dim.cpp -o main -larmadillo -llapack -lblas -O3")
        print("Executing...")
        os.system("./main 3 200 1000000 0.00000000001")
        print("Plotting...")
        os.system("python3 read2D.py 1000 10000 50000 100000 2DEuler_t1.csv 2DEuler_t2.csv 2DEuler_t3.csv 2DEuler_t4.csv")

    # Check runtime of methods
    elif args.Problem == 4:

        print("Compiling...")
        os.system("g++ -std=c++11 main.cpp Solver.cpp Solver2dim.cpp -o main -larmadillo -llapack -lblas -O3")
        print("Executing...")
        os.system("./main 4 100000 100 0.001")
        #os.system("read2D.py 2DEuler_t1.csv 2DEuler_t2.csv 2DEuler_t3.csv 2DEuler_t4.csv")

    else:
        print("Please choose between 1, 2, 3 or 4. See help for more")

else:

    print("Choose n:")
    n = input()

    print("Choose timesteps:")
    t = input()

    print("Choose dt:")
    dt = input()

    if args.Problem == 1:

        print("Compiling...")
        os.system("g++ -std=c++11 main.cpp Solver.cpp Solver2dim.cpp -o main -larmadillo -llapack -lblas -O3")
        print("Executing...")
        os.system(f"./main 1 {n} {t} {dt}")
        print("Plotting...")
        os.system("python3 read1D.py ForwardEuler FE.csv")
        os.system("python3 read1D.py BackwardEuler BE.csv")
        os.system("python3 read1D.py Crank-Nicolson CN.csv")
    
    elif args.Problem == 2:

        print("Compiling...")
        os.system("g++ -std=c++11 main.cpp Solver.cpp Solver2dim.cpp -o main -larmadillo -llapack -lblas -O3")
        print("Executing...")
        os.system(f"./main 2 {n} {t} {dt}")
        print("Plotting...")
        os.system("python3 readError.py FE.csv BE.csv CN.csv anal.csv anal2.csv")

    elif args.Problem == 3:

        print("Compiling...")
        os.system("g++ -std=c++11 main.cpp Solver.cpp Solver2dim.cpp -o main -larmadillo -llapack -lblas -O3")
        print("Executing...")
        os.system(f"./main 3 {n} {t} {dt}")
        print("Plotting...")
        os.system("python3 read2D.py 1000 10000 50000 100000 2DEuler_t1.csv 2DEuler_t2.csv 2DEuler_t3.csv 2DEuler_t4.csv")

    elif args.Problem == 4:

        print("Compiling...")
        os.system("g++ -std=c++11 main.cpp Solver.cpp Solver2dim.cpp -o main -larmadillo -llapack -lblas -O3")
        print("Executing...")
        os.system(f"./main 4 {n} {t} {dt}")
        #os.system("read2D.py 2DEuler_t1.csv 2DEuler_t2.csv 2DEuler_t3.csv 2DEuler_t4.csv")

    else:
        print("Please choose between 1, 2, 3. See help for more")

