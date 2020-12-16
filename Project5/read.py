import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.axes_grid1 import make_axes_locatable
import pandas as pd
import os
import sys

filename = sys.argv[1]



PDE = pd.read_csv(filename)
print(PDE.shape)
xsize, tsize = PDE.shape
x = np.linspace(0,1,xsize)
t = np.linspace(0,tsize,tsize)
tt, xx = np.meshgrid(t,x)

#print(PDE)

plt.plot(x, PDE.iloc[:,1])
plt.plot(x, PDE.iloc[:,6])
plt.show()

N = 10
#plt.contourf(xx, tt, PDE, N, cmap="hot")
plt.pcolormesh(xx, tt, PDE, cmap="hot")
plt.colorbar()
plt.show()