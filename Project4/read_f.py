import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import sys
import os

df_40 = pd.read_csv("tempV_40.csv")
df_60 = pd.read_csv("tempV_60.csv")
df_80 = pd.read_csv("tempV_80.csv")
df_100 = pd.read_csv("tempV_100.csv")

plt.figure()
plt.plot(df_40.iloc[:,5], df_40.iloc[:,0], ".", label="L=40")
plt.plot(df_60.iloc[:,5], df_60.iloc[:,0], ".", label="L=60")
plt.plot(df_80.iloc[:,5], df_80.iloc[:,0], ".", label="L=80")
plt.plot(df_100.iloc[:,5], df_100.iloc[:,0], ".", label="L=100")
plt.legend()
plt.xlabel(r"Temparature [T][$J/k_B$]")
plt.ylabel(r"Mean Energy $\langle E \rangle$")
plt.savefig("average_E_f.png")


plt.figure()
plt.plot(df_40.iloc[:,5], df_40.iloc[:,2], label="L=40")
plt.plot(df_60.iloc[:,5], df_60.iloc[:,2], label="L=60")
plt.plot(df_80.iloc[:,5], df_80.iloc[:,2], label="L=80")
plt.plot(df_100.iloc[:,5], df_100.iloc[:,2], label="L=100")
plt.legend()
plt.xlabel(r"Temparature [T][$J/k_B$]")
plt.ylabel(r"Mean Magnetization $\langle |M| \rangle$")
plt.savefig("average_M_f.png")


plt.figure()
plt.plot(df_40.iloc[:,5], df_40.iloc[:,3], label="L=40")
plt.plot(df_60.iloc[:,5], df_60.iloc[:,3], label="L=60")
plt.plot(df_80.iloc[:,5], df_80.iloc[:,3], label="L=80")
plt.plot(df_100.iloc[:,5], df_100.iloc[:,3], label="L=100")
plt.legend()
plt.xlabel(r"Temparature [T][$J/k_B$]")
plt.ylabel(r"Specific heat $C_V$")
plt.savefig("Cv_f.png")

plt.figure()
plt.plot(df_40.iloc[:,5], df_40.iloc[:,4], label="L=40")
plt.plot(df_60.iloc[:,5], df_60.iloc[:,4], label="L=60")
plt.plot(df_80.iloc[:,5], df_80.iloc[:,4], label="L=80")
plt.plot(df_100.iloc[:,5], df_100.iloc[:,4], label="L=100")
plt.legend()
plt.xlabel(r"Temparature [T][$J/k_B$]")
plt.ylabel(r"Suceptability \chi")
plt.savefig("X_f.png")
plt.show()