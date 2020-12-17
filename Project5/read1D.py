import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.axes_grid1 import make_axes_locatable
import pandas as pd
import os
import sys

filename = sys.argv[1]

PDE = pd.read_csv(filename)
xsize, tsize = PDE.shape
x = np.linspace(0,1,xsize)
t = np.linspace(0,tsize,tsize)
tt, xx = np.meshgrid(t,x)


plt.pcolormesh(xx, tt, PDE, cmap="hot")
plt.colorbar()
plt.show()
