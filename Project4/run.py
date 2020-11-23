import os
import sys

"""
# Run assignment d
print("Compiling...")
os.system("g++ main_d.cpp isingmodel.cpp -o main -larmadillo -llapack -lblas")
print("Executing...")
os.system("./main 1000000 20")
os.system("python3 read.py MCvalues.csv 20 1000000")
"""

# Run assignment f
print("Compiling...")
os.system("g++ main_f.cpp isingmodel.cpp -o main -larmadillo -llapack -lblas -O3")
print("Executing...")
for i in range(40, 101, 20):
    os.system(f"./main 2 2.5 0.05 {i} 10000 tempV_{i}.csv")