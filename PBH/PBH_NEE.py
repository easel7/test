import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt

# x = np.linspace(0, 5, 100)
# N = 21
# cmap = plt.get_cmap('jet',N)

# fig = plt.figure(figsize=(8,6))
# ax1 = fig.add_axes([0.10,0.10,0.70,0.85])

# for i,n in enumerate(np.linspace(0,2,N)):
#     y = np.sin(x)*x**n
#     ax1.plot(x,y,c=cmap(i))

# plt.xlabel('x')
# plt.ylabel('y')

# norm = mpl.colors.Normalize(vmin=0,vmax=2)
# sm = plt.cm.ScalarMappable(cmap=cmap, norm=norm)
# sm.set_array([])
# plt.colorbar(sm, ticks=np.linspace(0,2,N), 
#              boundaries=np.arange(-0.05,2.1,.1))
# plt.show()

def dNdE(Energy, Temp):
    if Energy < Temp:
        return 9e35 * np.power(1/Temp,3/2) * np.power(1/Energy,3/2)
    else:
        return 9e35 * np.power(1/Energy,3)

# def Temp(life):
#     return 7.8e3 * np.power(1/life,1/3)

life = np.logspace(-3,3,num=61)
Energy = np.logspace(1,6)

fig = plt.figure(figsize=(8,6))
sub = fig.add_subplot(111)  # 1 row x 1 col, 1 subplot
cmap = plt.get_cmap('viridis', np.size(life))


for i in range(life.size):
    duration = life[i]
    temp = 7.8e3 * np.power(1/duration,1/3)
    # print(i)
    dN = np.array([dNdE(x,temp) for x in Energy])
    sub.plot(Energy, dN, label = i, c=cmap(i))

sub.set_xlabel(r'$Energy(GeV)$')
sub.set_ylabel(r'$\frac{dN}{dE_{\gamma}}(GeV^{-1})$')
sub.set_xscale('symlog')
sub.set_yscale('symlog')

sub.set_xticks(np.logspace(1,6,num=26), minor=True)
sub.grid(linestyle='--',which='both')

sub.tick_params(axis='both', which='both', direction='in')

norm = mpl.colors.LogNorm(vmin=life.min(),vmax=life.max())
sm = plt.cm.ScalarMappable(cmap=cmap, norm=norm)
sm.set_array([])
cbar = plt.colorbar(sm)
cbar.set_label(r'$\tau\ [s]$')

plt.show()