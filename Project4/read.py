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

mc = np.linspace(0, mcs, mcs)


plt.plot(mc, df.iloc[:,0])
plt.plot(mc, df.iloc[:,1])
plt.plot(mc, df.iloc[:,2])
plt.plot(mc, df.iloc[:,3])
plt.xscale("log")
plt.show()

"""

plt.plot(df.iloc[:,5], df.iloc[:,0])
plt.show()
"""