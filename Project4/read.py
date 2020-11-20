import numpy as np
import matplotlib.pyplot as plt
import pandas
import sys
import os


f = sys.argv[1]
n = sys.argv[2]

df = pandas.read_csv(f)
print(df)

#print(df.iloc[:,0])

#plt.plot(df.iloc[:,5], df.iloc[:,0]/n**2)
#plt.show()
