import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.axes_grid1 import make_axes_locatable
import pandas as pd
import os
import sys
from mpl_toolkits.mplot3d import Axes3D
import matplotlib as mpl

filenames = []
for i in range(1, len(sys.argv)):
    df = pd.read_csv(sys.argv[i])
    filenames.append(df)

for df in filenames:
    df = df.append(pd.Series(0, index=df.columns), ignore_index=True)
#print(filenames[0])
x1, y1 = filenames[0].shape
x, y = np.meshgrid(np.linspace(0,1,x1+1), np.linspace(0,1,y1))


fig = plt.figure(figsize=plt.figaspect(0.5))

ax = fig.add_subplot(2, 2, 1)
surf = ax.pcolormesh(x, y, filenames[0], cmap="hot", vmin=0, vmax=1)
#plt.title(f"Time = {t1}")
fig.colorbar(surf)

ax = fig.add_subplot(2, 2, 2)
surf = ax.pcolormesh(x, y, filenames[1], cmap="hot", vmin=0, vmax=1)
#plt.title(f"Time = {t2}")
fig.colorbar(surf)

ax = fig.add_subplot(2, 2, 3)
surf = ax.pcolormesh(x, y, filenames[2], cmap="hot", vmin=0, vmax=1)
#plt.title(f"Time = {t3}")
fig.colorbar(surf)

ax = fig.add_subplot(2, 2, 4)
surf = ax.pcolormesh(x, y, filenames[3], cmap="hot", vmin=0, vmax=1)
#plt.title(f"Time = {t4}")
fig.colorbar(surf)

plt.tight_layout()
plt.show()