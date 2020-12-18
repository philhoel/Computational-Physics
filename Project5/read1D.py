import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os
import sys

method = sys.argv[1]
filename = sys.argv[2]

PDE = pd.read_csv(filename)
xsize, tsize = PDE.shape
x = np.linspace(0,1,xsize)
t = np.linspace(0,tsize,tsize)
tt, xx = np.meshgrid(t,x)


plt.pcolormesh(xx, tt, PDE, cmap="hot")
plt.title(f"Colormesh for {method} Method")
plt.ylabel("Time")
plt.xlabel("Length of rod")
plt.colorbar()
plt.savefig("Burning1D.png")
plt.show()
