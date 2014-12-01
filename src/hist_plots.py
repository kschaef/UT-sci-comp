import numpy as np
import matplotlib.pyplot as plt
from pylab import savefig

with open('bin/num_pairs.dat') as f0:
  tmp = f0.readlines()
nPairs = [float(x.rstrip()) for x in tmp]

with open('bin/num_odd.dat') as f1:
  tmp = f1.readlines()
nOdd = [float(x.rstrip()) for x in tmp]

with open('bin/prop_pairs.dat') as f2:
  tmp = f2.readlines()
propPairs = [float(x.rstrip()) for x in tmp]

with open('bin/num_socks.dat') as f3:
  tmp = f3.readlines()
nSocks = [float(x.rstrip()) for x in tmp]

# Start histograms

plt.subplots_adjust(wspace=.5, hspace=.5)


plt.subplot(221)
plt.xlabel('Number of socks in pairs')
plt.ylabel('Probability')
plt.title('Posterior on Pairs of Socks')
plt.grid(True)
plt.hist(np.array(nPairs), 20, normed=1, facecolor='g', alpha=0.75)

plt.subplot(222)
plt.xlabel('Number of odd socks')
plt.ylabel('Probability')
plt.title('Posterior on Odd Socks')
plt.grid(True)
plt.hist(np.array(nOdd), 20, normed=1, facecolor='y', alpha = 0.75)

plt.subplot(223)
plt.xlabel('Total number of socks')
plt.ylabel('Probability')
plt.title('Posterior on Total Socks')
plt.grid(True)
plt.hist(np.array(nSocks), 20, normed=1, facecolor='r', alpha = 0.75)

plt.subplot(224)
plt.xlabel('Proportion of socks in pairs')
plt.ylabel('Probability')
plt.title('Posterior on Proportion Paired')
plt.grid(True)
plt.hist(np.array(propPairs), 20, normed=1, facecolor='b', alpha = 0.75)

plt.savefig("bin/sock_posteriors.png", dpi = 120)

