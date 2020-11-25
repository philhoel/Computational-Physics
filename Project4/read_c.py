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
plt.plot(df.iloc[:,6], df.iloc[:,0], label="E")
plt.legend()
plt.axis([1,4, -1.5, -1.1])

plt.figure()
plt.plot(df.iloc[:,6], df.iloc[:,1], label="M")
plt.legend()

plt.figure()
plt.plot(df.iloc[:,6], df.iloc[:,2], label="E^2")
plt.legend()

plt.figure()
plt.plot(df.iloc[:,6], df.iloc[:,3], label="M^2")
plt.legend()

plt.figure()
plt.plot(df.iloc[:,6], df.iloc[:,4], label="CV")
plt.legend()

plt.figure()
plt.plot(df.iloc[:,6], df.iloc[:,4], label="X")




#plt.xscale("log")
plt.xlabel("MC cycles in logaritmic scale")
plt.ylabel("number of accpeted configurations")
plt.title("Accepted configurations")
plt.legend()
plt.show()