import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import sys
import os

df_40 = pd.read_csv("tempV_40.csv")
df_60 = pd.read_csv("tempV_60.csv")
df_80 = pd.read_csv("tempV_80.csv")
df_100 = pd.read_csv("tempV_100.csv")

plt.plot(df_40.iloc[:,5], df_40.iloc[:,0], label="L=40")
plt.plot(df_60.iloc[:,5], df_60.iloc[:,0], label="L=60")
plt.plot(df_80.iloc[:,5], df_80.iloc[:,0], label="L=80")
plt.plot(df_100.iloc[:,5], df_100.iloc[:,0], label="L=100")
plt.legend()
plt.show()