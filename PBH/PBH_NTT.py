import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt

def dNdt(Q, Energy):
    if Energy < Q:
        return 6.24e23 * (1/8* np.power(Q/Energy, 3/2) - 3/4* np.power(Q/Energy, 1/2) - 3/8 * np.power(Energy/Q, 1/2) + 1) # GeV^(-1) *sec^(-1)
    else:
        return 10e21 * np.power(Q/Energy, 4) # GeV^(-1) *sec^(-1)

duration = np.logspace(1,-3,num=40) # sec
Q = 4e4 * np.power(duration,-1/3) # GeV

print(duration)

print(Q)

fig = plt.figure(figsize=(8,6))
sub = fig.add_subplot(111) # 1 row x 1 col, 1 subplot
sub.plot(duration, Q, label="the peak of quark flux")

plt.show()