import numpy as np 
from sympy import Symbol
from sympy.solvers import solve
import matplotlib.pyplot as plt
from labellines import labelLine, labelLines

theta = np.arange(90) * (2*np.pi)/360 
mu_sym = Symbol('mu_sym')
mu_iso = np.zeros(len(theta))

for i in range(len(theta)):

    f = (1 - mu_sym)/(1 + mu_sym) - np.tan(theta[i])
    mu_iso[i] = float(solve(f, mu_sym)[0])

mu = 1 / np.tan(theta)

plt.plot(mu_iso, theta*360/2/np.pi, label='r=1')
plt.plot(mu, theta*360/2/np.pi, label='r=∞')
plt.xlabel('friction coeff (mu)')
plt.ylabel('collision angle (dgree)')
# plt.xlim(-1,1)
plt.ylim(0,90)
plt.legend(['iso','aniso'])
plt.grid()
plt.show()