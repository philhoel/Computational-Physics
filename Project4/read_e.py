import numpy as np
import matplotlib.pyplot as plt
import pandas
import sys
import os


f = sys.argv[1]
n = int(sys.argv[2])
mcs = int(sys.argv[3])

df = pandas.read_csv(f)
df = df.fillna(0)
print(df)

#print(df.iloc[:,0])

mc = np.linspace(1, mcs, mcs)

plt.figure()
#plt.hist(df.iloc[:,0], 50, density=True, facecolor='g', edgecolor="black", alpha=0.75, label=df.columns.values[0], log=True, xlim=(-2, -0.6))
#plt.hist(df.iloc[:,1], 50, density=True, facecolor='r', edgecolor="black", alpha=0.75, label=df.columns.values[1], log=True, xlim=(-2, -0.6))
df.iloc[:,0].plot.hist(bins=50, density=True, xlim=(-2, -0.6), log=True)
df.iloc[:,1].plot.hist(bins=50, density=True, xlim=(-2, -0.6), log=True)



#plt.yscale("log")
plt.xlabel("E[J]")
plt.ylabel("Probability")
plt.title("Probability plot")
plt.savefig("problem_e.png")
plt.legend()
plt.show()