import numpy as np
import matplotlib.pyplot as plt
import sys
import os

first = sys.argv[1]

rho_max = int(sys.argv[5])

def read_file(filename):

    eigen = list()

    with open(filename, "r") as my_file:

        for line in my_file.readlines():

            eigen.append(float(line.strip()))

    return eigen

eigen1 = read_file(first)
x = np.linspace(0, rho_max, 300)


plt.plot(x, eigen1)
plt.xlabel(r"$\rho$")
plt.ylabel(r"$u(\rho)$")
plt.savefig(f"project2_rho{rho_max}.png")
plt.legend()
plt.show()