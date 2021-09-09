#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri May 21 14:31:15 2021

@author: xpzhang
"""

import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt

def dNdE(Energy, Temp):
    if Energy < Temp:
        return 9e35 * np.power(1/Temp,3/2) * np.power(1/Energy,3/2)
    else:
        return 9e35 * np.power(1/Energy,3)

def Temp(life):
    return 7.8e3 * np.power(1/life,1/3)

Energy = np.logspace(1,6)

life1 = 0.01
temp1 = Temp(life1)

life2 = 0.1
temp2 = Temp(life2)

life3 = 1
temp3 = Temp(life3)

life4 = 10
temp4 = Temp(life4)

life5 = 100
temp5 = Temp(life5)

dN1 = np.array([dNdE(x,temp1) for x in Energy])

dN2 = np.array([dNdE(x,temp2) for x in Energy])

dN3 = np.array([dNdE(x,temp3) for x in Energy])

dN4 = np.array([dNdE(x,temp4) for x in Energy])

dN5 = np.array([dNdE(x,temp5) for x in Energy])

fig = plt.figure(figsize=(8,6))
sub = fig.add_subplot(111) # 1 row x 1 col, 1 subplot
sub.plot(Energy,dN1, label="0.01s")
sub.plot(Energy,dN2, label="0.1s")
sub.plot(Energy,dN3, label="1s")
sub.plot(Energy,dN4, label="10s")
sub.plot(Energy,dN5, label="100s")

sub.legend()
sub.set_xlabel(r'$Energy(GeV)$')
sub.set_ylabel(r'$\frac{dN}{dE_{\gamma}}(GeV^{-1})$')
sub.set_xscale('symlog')
sub.set_yscale('symlog')

sub.set_xticks(np.logspace(1,6,num=26), minor=True)
sub.grid(linestyle='--',which='both')

sub.tick_params(axis='both', which='both', direction='in')

# life = np.array([0.01,0.1,1,10,100])
# temps = 7.8e3 * np.power(1/life,1/3)

# fig, ax = plt.subplots(figsize=(10, 6))

# #for dN in [dN1,dN2,dN3,dN4,dN5]:
# for temp in temps:
#     dN = np.array([dNdE(x,temp) for x in Energy])
#     ax.plot(Energy, dN, label = temp)

# ax.legend()
# ax.set_xlabel(r'$Energy(GeV)$')
# ax.set_ylabel(r'$\frac{dN}{dE_{\gamma}}(GeV^{-1})$')
# ax.set_xscale('symlog')
# ax.set_yscale('symlog')

# ax.set_xticks(np.logspace(1,6,num=26), minor=True)
# ax.grid(linestyle='--',which='both')

# ax.tick_params(axis='both', which='both', direction='in')

plt.show()