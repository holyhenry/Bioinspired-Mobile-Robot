import time
import math
import numpy as np
import sympy as sp
from sympy.utilities.lambdify import lambdify
from scipy.optimize import minimize

'''
--------------------------PARAMETERS---------------------------
l1  : primary link               l2  : secondary link
w   : distance between motors    L   : length between knee joint
θ_L : left motor angle           θ_R : right motor angle 
θ_3 : knee joints bending angle (with respect to horizontal line)
(x_r, y_r) : right knee joint position
(x_l, y_l) : left knee joint position
---------------------------------------------------------------
'''
l1 = 0.09
l2 = 0.16
w  = 0.07

(thetaL_sym, thetaR_sym) = sp.symbols("""thetaL_sym thetaR_sym """, real = True)

def T(theta, x, y):
    return sp.Matrix([[sp.cos(theta), -sp.sin(theta), x], 
                      [sp.sin(theta), sp.cos(theta), y],
                      [0, 0, 1]])

def RobotKinematics(l1 = l1, l2 = l2, w = w):

    x_r = -w/2 + l1*sp.cos(thetaR_sym)
    x_l = w/2 + l1*sp.cos(thetaL_sym)
    y_r = l1*sp.sin(thetaR_sym)
    y_l = l1*sp.sin(thetaL_sym)
    theta3_sym = sp.atan2(y_l - y_r, x_l - x_r)
    L = sp.sqrt((x_l - x_r)**2 + (y_l - y_r)**2)

    FK = T(thetaL_sym, w/2, 0)@T((sp.pi - thetaL_sym + theta3_sym), l1, 0)@sp.Matrix([L/2, -sp.sqrt(l2**2 - (L/2)**2), 1])
    FK = FK[:2,:]
    J = FK.jacobian([thetaR_sym, thetaL_sym]).evalf()

    return FK, J
    
def InvereseKinematics(x, y, l1 = l1, l2 = l2, w = w):

    def leg_wide(var):
        return np.linalg.norm([var[0], var[1] - np.pi]) 

    def x_constraint_equation(var):
    # should be equal to zero when the 
        return l1**2 - l2**2 + (x - w/2)**2 + y**2 - 2*l1*(y*np.sin(var[0]) + (x - w/2)*np.cos(var[0]))

    def y_constraint_equation(var):
        return l1**2 - l2**2 + (x + w/2)**2 + y**2 - 2*l1*(y*np.sin(var[1]) + (x + w/2)*np.cos(var[1]))

    res = minimize(leg_wide, (0.1, 9*np.pi/10), method="SLSQP", constraints= ({"type": "eq", "fun": x_constraint_equation}, 
                                                                              {"type": "eq", "fun": y_constraint_equation}))
    return (res.x[0], res.x[1])

FK = RobotKinematics()[0]
FK_fast = lambdify((thetaR_sym, thetaL_sym), FK) # (x,y) = FK_fast(thetaR,thetaL)
J = RobotKinematics()[1]
J_fast = lambdify((thetaR_sym, thetaL_sym), J) # J_fast(thetaR,thetaL)

'''
Legs Trajectory ( Default offset = 0.02m for imporving friction )
'''
DownAMP = 0.01
UpperAMP = 0.07
StanceHeight = 0.185
StepLength = 0.18

class move(object):

    def RightTrajectory(offset, DownAMP =DownAMP, UpperAMP = UpperAMP, StanceHeight = StanceHeight, StepLength = StepLength):
        
        StancePercent = 0.5
        SwingPercent = 1 - StancePercent
        t_iteration = 4
        t_real = time.clock()
        t_cycle = t_real % 4
        CurrentPercent = t_cycle / t_iteration
    
        if (CurrentPercent <= StancePercent):   # stance phase
            x = -(StepLength / 2) + (CurrentPercent / StancePercent) * StepLength + offset
            y =  DownAMP * np.sin(np.pi * CurrentPercent / StancePercent) + StanceHeight
            
        else:   # swing phase  
            x = (StepLength / 2) - ((CurrentPercent - StancePercent) / SwingPercent) * StepLength + offset
            y = -UpperAMP * np.sin(np.pi * (CurrentPercent - StancePercent) / SwingPercent) + StanceHeight

        return np.array([[x], [y]])

    def LeftTrajectory(offset, DownAMP =DownAMP, UpperAMP = UpperAMP, StanceHeight = StanceHeight, StepLength = StepLength):
        
        StancePercent = 0.5
        SwingPercent = 1 - StancePercent
        t_iteration = 4
        t_real = time.clock()
        t_cycle = t_real % 4
        CurrentPercent = t_cycle / t_iteration
        
        if (CurrentPercent <= StancePercent):   # swing phase 
            x = (StepLength / 2)- (CurrentPercent / StancePercent) * StepLength + offset
            y = -UpperAMP * np.sin(np.pi * (CurrentPercent / StancePercent)) + StanceHeight
                                       
        else:   # stance phase
            x = -(StepLength / 2) + ((CurrentPercent - StancePercent) / SwingPercent) * StepLength + offset
            y =  DownAMP * np.sin(np.pi * ((CurrentPercent - StancePercent) / SwingPercent)) + StanceHeight
            
        return np.array([[-x], [y]])

    def SwingTrajectory(offset, DownAMP =DownAMP, UpperAMP = UpperAMP, StanceHeight = StanceHeight, StepLength = StepLength):
        
        StancePercent = 0.5
        SwingPercent = 1 - StancePercent
        t_iteration = 4
        t_real = time.clock()
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
        t_real = time.clock()
        t_cycle = t_real % 4
        CurrentPercent = t_cycle / t_iteration
    
        if (CurrentPercent <= StancePercent):   # stance phase
            x = -(StepLength / 2) + (CurrentPercent / StancePercent) * StepLength + offset
            y = DownAMP * np.sin(np.pi * CurrentPercent / StancePercent) + StanceHeight
            
        else:   # swing phase  
            x = (StepLength / 2) - ((CurrentPercent - StancePercent) / SwingPercent) * StepLength + offset
            y = DownAMP * np.sin(np.pi * (CurrentPercent - StancePercent) / SwingPercent) + StanceHeight

        return np.array([[x], [y]])

    '''
        Virtual compliance claculation
        k  = np.array([[kx,0],[0,ky]])
        c  = np.array([[cx,0],[0,cy]])
    '''
    def cartesian_compliance_homePosition(theta_R, theta_L, vel_R, vel_L):

        k  = np.array([[110,0],[0,110]])
        c  = np.array([[0.5,0],[0,0.5]])
        Kt = 0.0285
        J_trans  = -np.transpose(J_fast(theta_R, theta_L))  
        disp     = FK_fast(theta_R, theta_L) - FK_fast(theta_R_eq, theta_L_eq) 
        vel      = J_fast(theta_R, theta_L) @ np.array([[vel_R], [vel_L]])
        currents = J_trans @ ( k @ disp + c @ vel )*(1/Kt)
        return currents

    def cartesian_compliance_RightTrajectory(theta_R, theta_L, vel_R, vel_L):

        J_trans = -np.transpose(J_fast(theta_R, theta_L))
        disp    = FK_fast(theta_R, theta_L) - move.RightTrajectory(0.02)   
        vel     = J_fast(theta_R, theta_L) @ np.array([[vel_R], [vel_L]])
        Kt = 0.0285
        if move.RightTrajectory(0.02)[1] < 0.185:
            k = np.array([[50 ,0],[0,50 ]])
            c = np.array([[0.5,0],[0,0.5]])
            a = 1
        else:
            k = np.array([[50 ,0],[0,50 ]])
            c = np.array([[0.5,0],[0,0.5]])
            a = 0
        currents = J_trans @ ( k @ disp + c @ vel )*(1/Kt)
        return currents

    def cartesian_compliance_LeftTrajectory(theta_R, theta_L, vel_R, vel_L):

        J_trans = -np.transpose(J_fast(theta_R, theta_L))
        disp    = FK_fast(theta_R, theta_L) - move.LeftTrajectory(0.02)
        vel     = J_fast(theta_R, theta_L) @ np.array([[vel_R], [vel_L]])
        Kt = 0.0285
        if move.LeftTrajectory(0.02)[1] < 0.185:
            k = np.array([[50 ,0],[0,50 ]])
            c = np.array([[0.5,0],[0,0.5]])
            a = 1
        else:
            k = np.array([[50 ,0],[0,50 ]])
            c = np.array([[0.5,0],[0,0.5]])
            a = 0
        currents = J_trans @ ( k @ disp + c @ vel )*(1/Kt)
        return currents