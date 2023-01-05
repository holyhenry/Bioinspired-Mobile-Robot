import time
import numpy as np
import matplotlib.pyplot as plt

DownAMP = 0.01
UpperAMP = 0.07
StanceHeight = 0.185
StepLength = 0.18

def SwingTrajectory(offset, DownAMP =DownAMP, UpperAMP = UpperAMP, StanceHeight = StanceHeight, StepLength = StepLength):
        
        StancePercent = 0.5
        SwingPercent = 1 - StancePercent
        t_iteration = 4
        t_real = time.process_time()
        t_cycle = t_real % 4
        CurrentPercent = t_cycle / t_iteration
    
        if (CurrentPercent <= StancePercent):   # stance phase
            x = -(StepLength / 2) + (CurrentPercent / StancePercent) * StepLength + offset
            y = -UpperAMP * np.sin(np.pi * CurrentPercent / StancePercent) + StanceHeight
            
        else:   # swing phase  
            x = (StepLength / 2) - ((CurrentPercent - StancePercent) / SwingPercent) * StepLength + offset
            y = -UpperAMP * np.sin(np.pi * (CurrentPercent - StancePercent) / SwingPercent) + StanceHeight

        return np.array([[x], [y]])

def StanceTrajectory(offset, DownAMP =DownAMP, UpperAMP = UpperAMP, StanceHeight = StanceHeight, StepLength = StepLength):
        
        StancePercent = 0.5
        SwingPercent = 1 - StancePercent
        t_iteration = 4
        t_real = time.process_time()
        t_cycle = t_real % 4
        CurrentPercent = t_cycle / t_iteration
    
        if (CurrentPercent <= StancePercent):   # stance phase
            x = -(StepLength / 2) + (CurrentPercent / StancePercent) * StepLength + offset
            y = DownAMP * np.sin(np.pi * CurrentPercent / StancePercent) + StanceHeight
            
        else:   # swing phase  
            x = (StepLength / 2) - ((CurrentPercent - StancePercent) / SwingPercent) * StepLength + offset
            y = DownAMP * np.sin(np.pi * (CurrentPercent - StancePercent) / SwingPercent) + StanceHeight

        return np.array([[x], [y]])

x = []
y = []

t_start = time.time()
count = 0
duration = 4

while (time.time() - t_start < duration):

    x.append(SwingTrajectory(0)[0])
    y.append(SwingTrajectory(0)[1])
    count+=1
    print(time.process_time())

plt.plot(x, y)
plt.show()
