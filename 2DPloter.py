import numpy as np
import matplotlib.pylab as plt

fname = "./output/snapshots/IC_Snapshot.txt"
img = np.loadtxt(fname, skiprows=1)
plt.imshow(img)
plt.show()

for i in range(30,100,1):
  fname = "./output/snapshots/%i_Snapshot.txt"%i
  img = np.loadtxt(fname, skiprows=1)
  plt.imshow(img)
  plt.show()

