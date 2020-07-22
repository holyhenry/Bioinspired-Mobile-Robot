import numpy as np 
from sympy import Symbol
from sympy.solvers import solve
import matplotlib.pyplot as plt
from labellines import labelLine, labelLines

theta = np.arange(1,90) * (2*np.pi)/360 
mu_sym = Symbol('mu_sym')
r = np.array([0, 0.25, 0.5, 1])
mu = np.zeros((len(r),len(theta)))

for j in range(len(r)):

    for i in range(len(theta)):
        print(r[j], theta[i]*360/2/np.pi)
        f = (1 - mu_sym * r[j])/(r[j] + mu_sym) - np.tan(theta[i])
        mu[j,i] = float(solve(f, mu_sym)[0])

    # plt.subplot(211)
    plt.plot(mu[j,:], theta*360/2/np.pi)
    # plt.subplot(212)
    # plt.plot(mu[j,:], theta*360/2/np.pi)

# plt.subplot(211)
plt.legend(['r=0','r=0.25','r=0.5','r=1 (iso)'])
plt.xlim(0,1)
plt.ylim(0,90)
plt.grid()
plt.xlabel('friction coeff µ')
plt.ylabel('tilted angle θ (dgree)')

# plt.subplot(212)
# plt.legend(['r=0','r=0.25','r=0.5','r=1 (iso)'])
# plt.xscale('log')
# plt.xlim(0,1)
# plt.ylim(0,90)
# plt.grid()
# plt.xlabel('log scale friction coeff (mu)')
# plt.ylabel('collision angle (dgree)')

# plt.title('Maximum angle to move the block upward')
plt.show()
