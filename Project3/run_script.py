import os
import sys


def main():

    go = True
    planets = ["", "", "", "", "", "", "", ""]

    print("Choose number of iterations: ")
    n = input()

    print("Choose number of years: ")
    t = input()

    print("Choose method: ")
    method = input()

    print("Choose which of the assignments to plot (both lower or upper case")
    print("The Sun will always be plotted")
    print("a = Sun and Earth")
    print("b = Sun, Earth and Jupiter")
    print("c = all")
    bokstav = input()


    print("Add mass of Jupiter:(no input=9.54e-4)")
    mass = input()
    if mass == "":
        mass = 9.54e-4
    else:
        mass = float(mass)

    print("choose beta:(no input=3.0)")
    beta = input()
    if beta == "":
        beta = 3.0
    else:
        beta = float(beta)

    os.system("echo Compiling...")
    os.system("g++ -std=c++11 main.cpp solarsystem.cpp -o main -larmadillo -llapack -lblas")
    os.system("g++ -std=c++11 testing.cpp solarsystem.cpp -o tests -larmadillo -llapack -lblas")

    os.system("echo Executing...")
    os.system("./tests")
    os.system(f"./main {plott} {n} {t} {method} {mass} {beta} {bokstav}")
    os.system(f"python3 python_plot.py {plott}")




default = sys.argv[1]
plott = sys.argv[2]
method = sys.argv[3]

default = default.lower()
method = method.lower()

if default == "no" and (plott == "2d" or plott == "3d") and (method == "euler" or method == "verlet"):
    main()

elif default == "yes" and (plott == "2d" or plott == "3d")and (method == "euler" or method == "verlet"):
    print("Please choose mass of Jupiter:(no input=9.54e-4)")
    mass = input()
    if mass == "":
        mass = 9.54e-4
    else:
        mass = float(mass)
    os.system("echo Compiling...")
    os.system("g++ -std=c++11 main.cpp solarsystem.cpp -o main -larmadillo -llapack -lblas")
    os.system("g++ -std=c++11 testing.cpp solarsystem.cpp -o tests -larmadillo -llapack -lblas")

    os.system("echo Executing...")
    os.system("./tests")
    os.system(f"./main {plott} 10000 50 {method} {mass} 3.0 b")
    os.system(f"python3 python_plot.py {plott}")

else:
    print("Please choose between 'yes' or 'no' for default")
    print("Please choose between '2d' or '3d' for plott")
    sys.exit()
