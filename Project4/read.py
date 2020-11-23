import numpy as np
import matplotlib.pyplot as plt
import pandas
import sys
import os


f = sys.argv[1]
n = int(sys.argv[2])
mcs = int(sys.argv[3])

df = pandas.read_csv(f)
print(df)

#print(df.iloc[:,0])

mc = np.linspace(1, mcs, mcs)


plt.plot(mc, df.iloc[:,0], label="T = 1, Ordered")
plt.plot(mc, df.iloc[:,1], label="T = 2.4, Ordered")
plt.plot(mc, df.iloc[:,2], label="T = 1, Unoredred")
plt.plot(mc, df.iloc[:,3], label="T = 2.4, Unordered")
plt.xscale("log")
plt.xlabel("MC cycles in logaritmic scale")
plt.ylabel(r"$\langle E \rangle$")
plt.title("Mean energy plot")
plt.legend()
plt.show()
"""

plt.plot(df.iloc[:,5], df.iloc[:,0])
plt.show()
"""