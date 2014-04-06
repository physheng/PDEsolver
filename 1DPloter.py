import numpy as np
import matplotlib.pylab as plt

#fname = "./output/snapshots/IC_Snapshot.txt"
#r,Phi = np.loadtxt(fname, comments='#', unpack=True)
#plt.plot(r,Phi,label='IC')

for i in range(1,5):
  fname = "./output/snapshots/%i_Snapshot.txt"%i
  r,Phi = np.loadtxt(fname, comments='#', unpack=True)
  plt.plot(r,Phi,label='T%i'%i)
  fname = "./output/snapshots/%i_Ex_Snapshot.txt"%i
  r,Phi = np.loadtxt(fname, comments='#', unpack=True)
  plt.plot(r[::4],Phi[::4],'.',label='T%i'%i)
  #plt.plot(r+np.pi*2,Phi,label='T%i'%i)


plt.xlim([0.0,6.0])
plt.legend(loc=1)
plt.show()
