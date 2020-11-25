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

plt.figure()
plt.plot(mc, df.iloc[:,0], label="T = 1, Ordered")
plt.plot(mc, df.iloc[:,1], label="T = 2.4, Ordered")
plt.plot(mc, df.iloc[:,2], label="T = 1, Unoredred")
plt.plot(mc, df.iloc[:,3], label="T = 2.4, Unordered")

plt.xscale("log")
plt.xlabel("MC cycles in logaritmic scale")
plt.ylabel(r"$\langle E \rangle$")
plt.title("Mean energy plot")
plt.legend()

plt.figure()
plt.plot(mc, df.iloc[:,4], label="EO_low")
plt.plot(mc, df.iloc[:,5], label="EO_high")
plt.plot(mc, df.iloc[:,6], label="EU_low")
plt.plot(mc, df.iloc[:,7], label="EU_high")

plt.xscale("log")
plt.xlabel("MC cycles in logaritmic scale")
plt.ylabel(r"$\langle M \rangle$")
plt.title("Mean magnetization plot")
plt.legend()

plt.figure()
plt.plot(mc, df.iloc[:,8], label="EO_low")
plt.plot(mc, df.iloc[:,9], label="EO_high")
plt.plot(mc, df.iloc[:,10], label="EU_low")
plt.plot(mc, df.iloc[:,11], label="EU_high")

plt.xscale("log")
plt.xlabel("MC cycles in logaritmic scale")
plt.ylabel("number of accpeted configurations")
plt.title("Accepted configurations")
plt.legend()
plt.show()
"""

plt.plot(df.iloc[:,5], df.iloc[:,0])
plt.show()
"""