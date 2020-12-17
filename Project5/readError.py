import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os
import sys

file1 = sys.argv[1]
file2 = sys.argv[2]
file3 = sys.argv[3]


PDE1 = pd.read_csv(file1)
PDE2 = pd.read_csv(file2)
PDE3 = pd.read_csv(file3)

xsize, tsize = PDE.shape
x = np.linspace(0,1,xsize)

plt.plot(x, PDE1.iloc[:,1], label="FE, t = 1")
plt.plot(x, PDE1.iloc[:,6], label="FE, t = 6")

plt.plot(x, PDE2.iloc[:,1], label="BE, t = 1")
plt.plot(x, PDE2.iloc[:,6], label="BE, t = 6")

plt.plot(x, PDE3.iloc[:,1], label="CN, t = 1")
plt.plot(x, PDE3.iloc[:,6], label="CN, t = 6")
plt.show()