import time
import odrive
from odrive.enums import *
from scipy.optimize import minimize

class od(object):
    '''
    Basic settings & commands
    '''
    def connect_odrive(serial):
        odrv0 = odrive.find_any(serial_number = serial, timeout = 20)
        if odrv0 is not None:
            print('Connected!')
            print('Target serial {} \t Odrive serial {}'.format(serial, odrv0.serial_number))
            print('Motor 0 calibrated: {}'.format(odrv0.axis0.motor.is_calibrated))
            print('Motor 1 calibrated: {}'.format(odrv0.axis1.motor.is_calibrated))    
        else:
            print("ODrive ({}) not found".format(serial))
        return odrv0

    def SetParameter(odrv0):
        current_limit = 20
        odrv0.axis0.motor.config.current_lim    = current_limit #A
        odrv0.axis1.motor.config.current_lim    = current_limit #A
        odrv0.axis0.controller.config.vel_limit = 1000000
        odrv0.axis1.controller.config.vel_limit = 1000000
        odrv0.axis0.controller.config.pos_gain  = 50
        odrv0.axis1.controller.config.pos_gain  = 50
        odrv0.axis0.controller.config.vel_integrator_gain = 0
        odrv0.axis1.controller.config.vel_integrator_gain = 0
        return(current_limit)

    def CheckMotorError(odrv0):
        axis0error = odrv0.axis0.error 
        axis1error = odrv0.axis1.error 
        axis0motorerror = odrv0.axis0.motor.error 
        axis1motorerror = odrv0.axis1.motor.error 
        axis0controllererror = odrv0.axis0.controller.error 
        axis1controllererror = odrv0.axis0.controller.error 
        print("error:          ", axis0error, axis1error)
        print("motorerror:     ", axis0motorerror, axis1motorerror)
        print("controllererror:", axis0controllererror, axis1controllererror)
        return()

    def MotorClearError(odrv0):
        odrv0.axis0.error = 0
        odrv0.axis1.error = 0
        odrv0.axis0.motor.error = 0
        odrv0.axis1.motor.error = 0
        odrv0.axis0.controller.error = 0
        odrv0.axis1.controller.error = 0
        odrv0.axis0.encoder.error = 0
        odrv0.axis1.encoder.error = 0
        return()

    def Calibration(odrv0):
        odrv0.axis0.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE
        odrv0.axis1.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE
        time.sleep(12)
        print('Motor 0 calibrated: {}'.format(odrv0.axis0.motor.is_calibrated))
        print('Motor 1 calibrated: {}'.format(odrv0.axis1.motor.is_calibrated))   

    def ClosedLoopControlMode(odrv0):
        odrv0.axis0.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL
        odrv0.axis1.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL

    def IdleMode(odrv0):
        odrv0.axis0.requested_state = odrive.enums.AXIS_STATE_IDLE
        odrv0.axis1.requested_state = odrive.enums.AXIS_STATE_IDLE

    def ControllerPositionControl(odrv0): # default mode
        odrv0.axis0.controller.config.control_mode = CTRL_MODE_POSITION_CONTROL
        odrv0.axis1.controller.config.control_mode = CTRL_MODE_POSITION_CONTROL
        print("Control Mode :{}".format(odrv0.axis0.controller.config.control_mode))

    def ControllerCurrentControl(odrv0):
        odrv0.axis0.controller.config.control_mode = CTRL_MODE_CURRENT_CONTROL
        odrv0.axis1.controller.config.control_mode = CTRL_MODE_CURRENT_CONTROL
        print("Control Mode :{}".format(odrv0.axis0.controller.config.control_mode))

    def MaxCurrentProtection(current, current_limit = 20):
        current = min(np.abs(current), current_limit) * np.sign(current) 
        return current 

    '''
    Defining angles, run before test
    '''
    def SetMotorZeroPosition(m0, m1):
        m0_zero_pos = m0.encoder.pos_estimate
        m1_zero_pos = m1.encoder.pos_estimate
        theta_R_zero = -((m0_zero_pos) / 8192 * 2 * np.pi) + np.pi
        theta_L_zero = -((m1_zero_pos) / 8192 * 2 * np.pi)
        return m0_zero_pos, m1_zero_pos 

    def SetMotorHomePosition(m0, m1, m0_zero_pos, m1_zero_pos):
        m0_pos = m0.encoder.pos_estimate
        m1_pos = m1.encoder.pos_estimate
        m0_home_pos = - ((m0_pos - m0_zero_pos) / 8192 * 2 * np.pi) + np.pi
        m1_home_pos = - ((m1_pos - m1_zero_pos) / 8192 * 2 * np.pi)
        return m0_home_pos, m1_home_pos

import math
import numpy as np
import sympy as sp
from sympy.utilities.lambdify import lambdify
from kinematics_function import RobotKinematics, InvereseKinematics
from kinematics_function import move

(thetaL_sym, thetaR_sym) = sp.symbols("""thetaL_sym thetaR_sym """, real = True)

FK = RobotKinematics()[0]
FK_fast = lambdify((thetaR_sym, thetaL_sym), FK) # (x,y) = FK_fast(thetaR,thetaL)
J = RobotKinematics()[1]
J_fast = lambdify((thetaR_sym, thetaL_sym), J) # J_fast(thetaR,thetaL)

class gait(object):
    
    def PoitionControlWalking(duration, odrvR, odrvL, m0, m1, m00, m11, m0_zero_pos, m1_zero_pos, m00_zero_pos, m11_zero_pos):
        od.ClosedLoopControlMode(odrvR)
        od.ClosedLoopControlMode(odrvL)

        print("pos_gain: {}".format(odrvR.axis0.controller.config.pos_gain))
        t_start = time.time()
        count = 0

        while (time.time() - t_start < duration):
        
            odrv1_theta_R = InvereseKinematics(move.RightTrajectory(0)[0],move.RightTrajectory(0)[1])[1]
            odrv1_theta_L = InvereseKinematics(move.RightTrajectory(0)[0],move.RightTrajectory(0)[1])[0]
            odrv2_theta_R = InvereseKinematics(move.LeftTrajectory(0)[0],move.LeftTrajectory(0)[1])[1]
            odrv2_theta_L = InvereseKinematics(move.LeftTrajectory(0)[0],move.LeftTrajectory(0)[1])[0]

            m0_pos  = -(odrv1_theta_R - np.pi)/(2*np.pi)*8192 + m0_zero_pos
            m1_pos  = -odrv1_theta_L/(2*np.pi)*8192 + m1_zero_pos
            m00_pos = -(odrv2_theta_R - np.pi)/(2*np.pi)*8192 + m00_zero_pos
            m11_pos = -odrv2_theta_L/(2*np.pi)*8192 + m11_zero_pos
            
            m0.controller.set_pos_setpoint(m0_pos,0,0)
            m1.controller.set_pos_setpoint(m1_pos,0,0)
            m00.controller.set_pos_setpoint(m00_pos,0,0)
            m11.controller.set_pos_setpoint(m11_pos,0,0)
        
            count += 1

        print(count,'iterations in', duration, 'second')
        print("Frequency:", count/duration, 'Hz')
            
    def PoitionControlWalkingBack(duration, odrvR, odrvL, m0, m1, m00, m11, m0_zero_pos, m1_zero_pos, m00_zero_pos, m11_zero_pos):
        od.ClosedLoopControlMode(odrvR)
        od.ClosedLoopControlMode(odrvL)

        t_start = time.time()
        count = 0

        while (time.time() - t_start < duration):
        
            odrv2_theta_R = InvereseKinematics(move.RightTrajectory(0.02)[0],move.RightTrajectory(0.02)[1])[1]
            odrv2_theta_L = InvereseKinematics(move.RightTrajectory(0.02)[0],move.RightTrajectory(0.02)[1])[0]
            odrv1_theta_R = InvereseKinematics(move.LeftTrajectory(0.02)[0],move.LeftTrajectory(0.02)[1])[1]
            odrv1_theta_L = InvereseKinematics(move.LeftTrajectory(0.02)[0],move.LeftTrajectory(0.02)[1])[0]
            
            m0_pos  = -(odrv1_theta_R - np.pi) / (2*np.pi) * 8192 + m0_zero_pos
            m1_pos  = -odrv1_theta_L / (2*np.pi) * 8192 + m1_zero_pos
            m00_pos = -(odrv2_theta_R - np.pi) / (2*np.pi) * 8192 + m00_zero_pos
            m11_pos = -odrv2_theta_L / (2*np.pi) * 8192 + m11_zero_pos
            
            m0.controller.set_pos_setpoint(m0_pos,0,0)
            m1.controller.set_pos_setpoint(m1_pos,0,0)
            m00.controller.set_pos_setpoint(m00_pos,0,0)
            m11.controller.set_pos_setpoint(m11_pos,0,0)
        
            count += 1

        print(count,'iterations in', duration, 'second')
        print("Frequency:", count/duration, 'Hz')

    def PoitionControlStepping(duration, odrvR, odrvL, m0, m1, m00, m11, m0_zero_pos, m1_zero_pos, m00_zero_pos, m11_zero_pos):
            od.ClosedLoopControlMode(odrvR)
            od.ClosedLoopControlMode(odrvL)

            print("pos_gain: {}".format(odrvR.axis0.controller.config.pos_gain))
            t_start = time.time()
            count = 0

            while (time.time() - t_start < duration):
            
                odrv1_theta_R = InvereseKinematics(move.StanceTrajectory(0)[0],move.StanceTrajectory(0)[1])[1]
                odrv1_theta_L = InvereseKinematics(move.StanceTrajectory(0)[0],move.StanceTrajectory(0)[1])[0]
                odrv2_theta_R = InvereseKinematics(move.SwingTrajectory(0)[0],move.SwingTrajectory(0)[1])[1]
                odrv2_theta_L = InvereseKinematics(move.SwingTrajectory(0)[0],move.SwingTrajectory(0)[1])[0]

                m0_pos  = -(odrv1_theta_R - np.pi)/(2*np.pi)*8192 + m0_zero_pos
                m1_pos  = -odrv1_theta_L/(2*np.pi)*8192 + m1_zero_pos
                m00_pos = -(odrv2_theta_R - np.pi)/(2*np.pi)*8192 + m00_zero_pos
                m11_pos = -odrv2_theta_L/(2*np.pi)*8192 + m11_zero_pos
                
                m0.controller.set_pos_setpoint(m0_pos,0,0)
                m1.controller.set_pos_setpoint(m1_pos,0,0)
                m00.controller.set_pos_setpoint(m00_pos,0,0)
                m11.controller.set_pos_setpoint(m11_pos,0,0)
            
                count += 1

            print(count,'iterations in', duration, 'second')
            print("Frequency:", count/duration, 'Hz')

    def CurrentControlWalking(duration, odrvR, odrvL, m0, m1, m00, m11, m0_zero_pos, m1_zero_pos, m00_zero_pos, m11_zero_pos):
        od.ClosedLoopControlMode(odrvR)
        od.ClosedLoopControlMode(odrvL)

        t_start = time.time()
        count = 0

        while (time.time() - t_start < duration):
            
            #current angle(rad) & velocity(rad/s)
            odrv1_theta_R = - ((m0.encoder.pos_estimate - m0_zero_pos) / 8192 * 2 * np.pi) + np.pi
            odrv1_theta_L = - ((m1.encoder.pos_estimate - m1_zero_pos) / 8192 * 2 * np.pi)
            odrv2_theta_R = - ((m00.encoder.pos_estimate - m00_zero_pos) / 8192 * 2 * np.pi) + np.pi
            odrv2_theta_L = - ((m11.encoder.pos_estimate - m11_zero_pos) / 8192 * 2 * np.pi)
            
            odrv1_vel_R = - ((m0.encoder.vel_estimate) / 8192 * 2 * np.pi)
            odrv1_vel_L = - ((m1.encoder.vel_estimate) / 8192 * 2 * np.pi)
            odrv2_vel_R = - ((m00.encoder.vel_estimate) / 8192 * 2 * np.pi)
            odrv2_vel_L = - ((m11.encoder.vel_estimate) / 8192 * 2 * np.pi)
            
            #get current
            joint_damping_R = 0.6
            joint_damping_L = 0.6
            
            odrv1_current = move.cartesian_compliance_RightTrajectory(odrv1_theta_R, odrv1_theta_L, odrv1_vel_R, odrv1_vel_L)
            odrv1_current_R = odrv1_current[0] - np.array(joint_damping_R * odrv1_vel_R)
            odrv1_current_L = odrv1_current[1] - np.array(joint_damping_L * odrv1_vel_L)
            
            odrv2_current = move.cartesian_compliance_LeftTrajectory(odrv2_theta_R, odrv2_theta_L, odrv2_vel_R, odrv2_vel_L)
            odrv2_current_R = odrv2_current[0] - np.array(joint_damping_R * odrv2_vel_R)
            odrv2_current_L = odrv2_current[1] - np.array(joint_damping_L * odrv2_vel_L)

            #make sure the current is not exceeds the limit
            odrv1_current_R = od.MaxCurrentProtection(odrv1_current_R)
            odrv1_current_L = od.MaxCurrentProtection(odrv1_current_L)
            odrv2_current_R = od.MaxCurrentProtection(odrv2_current_R)
            odrv2_current_L = od.MaxCurrentProtection(odrv2_current_L)
                
            #control the motors
            m0.controller.set_current_setpoint(-odrv1_current_R)
            m1.controller.set_current_setpoint(-odrv1_current_L)
            m00.controller.set_current_setpoint(-odrv2_current_R)
            m11.controller.set_current_setpoint(-odrv2_current_L)
            
            count += 1

        print(count,'iterations in', duration, 'second')
        print("Frequency:", count/duration, 'Hz')

        m0.controller.set_current_setpoint(0)
        m1.controller.set_current_setpoint(0)
        m00.controller.set_current_setpoint(0)
        m11.controller.set_current_setpoint(0)

        od.ControllerPositionControl(odrvR)
        od.ControllerPositionControl(odrvL)
        od.ClosedLoopControlMode(odrvR)
        od.ClosedLoopControlMode(odrvL)