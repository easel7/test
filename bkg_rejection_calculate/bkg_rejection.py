import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt

def E3Flux(E):
    return 1.43e-8 * np.power(E / 1000.0 , -2.7) * np.power(E, 3) # cm^-2 s^-1 sr^-1 GeV^-1 * GeV^3

def Electronflux(E):
    if E < 1000:
        return 1.37e-8 * np.power(E / 103.0, -3.17) * np.power(E, 3) # cm^-2 s^-1 sr^-1 GeV^-1 * GeV^3
    else:
        return 1.17e-11 * np.power(E / 1000.0, -3.9) * np.power(E, 3) # cm^-2 s^-1 sr^-1 GeV^-1 * GeV^3

Energy = np.logspace(1,6) # GeV
bkg_rej = np.logspace(-6, -2, 5) # 10^-6, 10^-5, 10^-4, 10^-3, 10^-2


fig = plt.figure(figsize=(8,6))
sub = fig.add_subplot(111)  # 1 row x 1 col, 1 subplot
# cmap = plt.get_cmap('viridis', np.size(life))

# for i in range(bkg_rej.size):
#     rejfactor = bkg_rej[i]
#     E3dNdE = rejfactor * np.array([E3Flux(x) for x in Energy])
#     sub.plot(Energy, E3dNdE, Lable = bkg_rej[i])

dN1 = bkg_rej[0] * np.array([E3Flux(x) for x in Energy])

dN2 = bkg_rej[1] * np.array([E3Flux(x) for x in Energy])

dN3 = bkg_rej[2] * np.array([E3Flux(x) for x in Energy])

dN4 = bkg_rej[3] * np.array([E3Flux(x) for x in Energy])

dN5 = bkg_rej[4] * np.array([E3Flux(x) for x in Energy])

dNE = np.array([Electronflux(x) for x in Energy])

sub.plot(Energy,dN1, label=r'$10^{-6}$')
sub.plot(Energy,dN2, label=r'$10^{-5}$')
sub.plot(Energy,dN3, label=r'$10^{-4}$')
sub.plot(Energy,dN4, label=r'$10^{-3}$')
sub.plot(Energy,dN5, label=r'$10^{-2}$')
sub.plot(Energy,dNE, label="CR-electron")

sub.legend()
sub.set_xlabel(r'$Energy(GeV)$')
sub.set_ylabel(r'$E^{3}\frac{dN_e}{dE_{CR}}(GeV^2/(cm^2s\ sr))$')
sub.set_xscale('symlog')
sub.set_yscale('log')
plt.title(r'$normalized\ f_{CR}(E) \times background\ rejection (\epsilon_{CR})$') 

plt.show()