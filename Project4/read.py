import numpy as np
import matplotlib.pyplot as plt
import pandas
import sys
import os


f = sys.argv[1]
n = sys.argv[2]

df = pandas.read_csv(f)
print(df)
