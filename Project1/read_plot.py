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
x_first = np.linspace(h, 1 - h, n)
y_second, h, n = read_file(second)
x_second = np.linspace(h, 1 - h, n)
y_third, h, n = read_file(third)
x_third = np.linspace(h, 1 - h, n)


plt.plot(x_first, y_first)
plt.show()
plt.plot(x_second, y_second)
plt.show()
plt.plot(x_third, y_third)
plt.show()
