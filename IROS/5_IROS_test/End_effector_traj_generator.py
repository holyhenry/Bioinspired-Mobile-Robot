import numpy as np
import time
import matplotlib.pyplot as plt

def SwingTrajectory(t_clock, UpperAMP = 0.04, StanceHeight = 0.185, StepLength = 0.18):
    
    period = 2
    percent = t_clock / period

    if (percent <= 1): # Swing
        x = -(StepLength / 2) + percent * StepLength
        y = -UpperAMP * np.sin(np.pi * percent) + StanceHeight  
        
    else: # Stay and do nothing
        x = StepLength / 2
        y = StanceHeight

    return np.array([[x], [y]])

def GoHomeTrajactory(t_clock, StanceHeight = 0.185, StepLength = 0.18, LiftHeight = 0.09):

    period = 4   
    percent = t_clock / period

    if percent >= 0 and percent < 0.25:
        x = StepLength / 2
        y = -(percent / 0.25) * LiftHeight + StanceHeight
        
    elif percent >= 0.25 and percent < 0.75:
        x = StepLength / 2 - ((percent - 0.25) / 0.5) * StepLength
        y = -LiftHeight + StanceHeight
        
    elif percent >= 0.75 and percent <= 1:
        x = -StepLength / 2
        y = -LiftHeight + StanceHeight + ((percent - 0.75) / 0.25) * LiftHeight 
        
    else:
        x = -StepLength / 2
        y = StanceHeight

    return np.array([[x], [y]])

x = []
y = []
duration1 = 2
duration2 = 4

t_start1 = time.time()

while time.time() - t_start1 < duration1:

    t_clock = time.time() - t_start1
    x.append(SwingTrajectory(t_clock)[0])
    y.append(SwingTrajectory(t_clock)[1])

t_start2 = time.time()

while time.time() - t_start2 < duration2:

    t_clock = time.time() - t_start2
    x.append(GoHomeTrajactory(t_clock)[0])
    y.append(GoHomeTrajactory(t_clock)[1])

x_start = -0.09
y_start = 0.185
plt.plot(x,y,x_start,y_start,'*')
plt.title('End-effector Trajectory')
# plt.text(-0.04,0.14,'swing duration=[0.5, 1, 2s]')
# plt.text(-0.04,0.10,'<----- moving backward (4s)')
# plt.text(0.08,0.14,'lifting (2s) ----->',rotation=90)
# plt.text(-0.085,0.14,'settling (2s) ----->',rotation=270)
plt.xlim(-0.1, 0.1)
plt.ylim(0.19, 0.09)
plt.xlabel('x(m)')
plt.ylabel('y(m)')
# plt.grid()
plt.show()