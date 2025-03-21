import matplotlib.pyplot as plt
import pandas as pd
from mpl_toolkits.mplot3d import Axes3D

# read data from the terrain csv file

data = pd.read_csv('csvs/terrain.csv')

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

x = data['x']
y = data['y']
z = data['z']

ax.plot_trisurf(x, y, z, cmap='terrain', edgecolor='none')

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()
