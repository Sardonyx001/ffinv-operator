from matplotlib import pyplot as plt 
import pandas as pd 


df = pd.read_csv('output/data.csv')
print(df)
plt.scatter(df['x'],df['y'],s=0.5)
plt.show()