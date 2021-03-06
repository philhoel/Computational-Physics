import numpy as np
import matplotlib.pyplot as plt
import sys
import os

first = sys.argv[1]
a = sys.argv[2]
b = sys.argv[3]
c = sys.argv[4]
rho_max = int(sys.argv[5])

def read_file(filename):

    eigen = list()

    with open(filename, "r") as my_file:

        for line in my_file.readlines():

            eigen.append(float(line.strip()))

    return eigen

eigen1 = read_file(first)
eigen2 = read_file(a)
eigen3 = read_file(b)
eigen4 = read_file(c)
x = np.linspace(0, rho_max, 300)


plt.plot(x, eigen1, label="omega=0.01")
plt.plot(x, eigen2, label="omega=0.5")
plt.plot(x, eigen3, label="omega=1")
plt.plot(x, eigen4, label="omega=5")
plt.xlabel(r"$\rho$")
plt.ylabel(r"$u(\rho)$")
plt.savefig("project2_omega.png")
plt.legend()
plt.show()
