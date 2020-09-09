import numpy as np
import matplotlib.pyplot as plt
import sys

first = sys.argv[1]
second = sys.argv[2]
third = sys.argv[3]

def read_file(filename):
    
    y = []

    with open(filename, "r") as my_file:
        n = my_file.readline()
        n = int(n)
        h = 1/(n-2)
        for line in my_file:
            y.append(float(line))

    return y, h, n

y_first, h, n = read_file(first)
x = np.linspace(h, 1 - h, n)

y_second, h, n = read_file(second)

y_third, h, n = read_file(third)



plt.plot(x, y_first, label="General")
plt.plot(x, y_second, label="Special")
plt.plot(x, y_third, label="Analytic")
plt.legend()
plt.title(f"Numerical and analytic plot for n = {n}")
plt.xlabel("x")
plt.ylabel("u(x)")
plt.savefig(f"plot_n_{n}.jpg")
plt.show()
