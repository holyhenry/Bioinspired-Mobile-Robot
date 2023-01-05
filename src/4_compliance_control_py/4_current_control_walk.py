import time
import numpy as np
import matplotlib.pyplot as plt
from odrive_function import od, gait

odrv1 = od.connect_odrive("206A33A5304B")
odrv2 = od.connect_odrive("335C315E3536")
m0  = odrv1.axis0
m1  = odrv1.axis1
m00 = odrv2.axis0
m11 = odrv2.axis1
od.SetParameter(odrv1)
od.SetParameter(odrv2)
print("Odrive Parameter Set!\n")

print('c--Calibrate all motors ','         l--Closed loop control mode     \n')
print('i--Idle mode            ','         a--Current control mode         \n')
print('p--Position control mode','         e--Check & Clear motor error    \n')
print('zero--Define motor zero position',' home--Define motor home position\n')

while True:
    command = input()

    if command == 'c':
        print("Calibrating motors...")
        od.Calibration(odrv1)
        od.Calibration(odrv2)

    if command == 'l':
        print("Closed loop control mode")
        od.ClosedLoopControlMode(odrv1)
        od.ClosedLoopControlMode(odrv2)

    if command == 'i':
        print("Idle mode")
        od.IdleMode(odrv1)
        od.IdleMode(odrv2)

    if command == 'a':
        print("Current control mode")
        od.ControllerCurrentControl(odrv1)
        od.ControllerCurrentControl(odrv2)

    if command == 'p':
        print("Position control mode (default)")
        od.ControllerPositionControl(odrv1)
        od.ControllerPositionControl(odrv2)

    if command == 'e':    
        print("Check & Clear motor error")
        print("Odrive1")
        od.CheckMotorError(odrv1)
        print("odrive2")
        od.CheckMotorError(odrv2)
        od.MotorClearError(odrv1)
        od.MotorClearError(odrv2)

    if command == 'zero':
        print("Define Odrv1 motor zero position in 3s\n")
        time.sleep(3)
        m0_zero_pos = od.SetMotorZeroPosition(m0, m1)[0]
        m1_zero_pos = od.SetMotorZeroPosition(m0, m1)[1]
        print("R: ",m0_zero_pos,"L: ",m1_zero_pos,"\n")

        print("Define Odrv2 motor zero position in 3s\n")
        time.sleep(3)
        m00_zero_pos = od.SetMotorZeroPosition(m00, m11)[0]
        m11_zero_pos = od.SetMotorZeroPosition(m00, m11)[1]
        print("R: ",m00_zero_pos,"L: ",m11_zero_pos,"\n")
        print("Zero position set!")

    if command == 'home':
        print("Define Odrv1 motor home position in 3s\n")
        time.sleep(3)
        m0_home_pos = od.SetMotorHomePosition(m0, m1, m0_zero_pos, m1_zero_pos)[0]
        m1_home_pos = od.SetMotorHomePosition(m0, m1, m0_zero_pos, m1_zero_pos)[1]
        print("R: ",m0_home_pos / (2 * np.pi) * 360,"L: ",m1_home_pos / (2 * np.pi) * 360,"\n")

        print("Define Odrv2 motor home position in 3s\n")
        time.sleep(3)
        m00_home_pos = od.SetMotorHomePosition(m00, m11, m00_zero_pos, m11_zero_pos)[0]
        m11_home_pos = od.SetMotorHomePosition(m00, m11, m00_zero_pos, m11_zero_pos)[1]
        print("R: ",m00_home_pos / (2 * np.pi) * 360,"L: ",m11_home_pos / (2 * np.pi) * 360,"\n")
        print("Home position set!")

    if command == "poswalk":
        print("Poition Control Walking Gait")
        gait.PoitionControlWalking(10, odrv1, odrv2, m0, m1, m00, m11, m0_zero_pos, m1_zero_pos, m00_zero_pos, m11_zero_pos)

    if command == "poswalkhome":
        print("going home <3")
        gait.PoitionControlWalkingBack(10, odrv1, odrv2, m0, m1, m00, m11, m0_zero_pos, m1_zero_pos, m00_zero_pos, m11_zero_pos)

    if command == "posstep":
        print("Position Control Stepping Gait")
        gait.PoitionControlStepping(50, odrv1, odrv2, m0, m1, m00, m11, m0_zero_pos, m1_zero_pos, m00_zero_pos, m11_zero_pos)

    if command == "currwalk":
        print("Current Control Walking Gait")
        gait.CurrentControlWalking(6, odrv1, odrv2, m0, m1, m00, m11, m0_zero_pos, m1_zero_pos, m00_zero_pos, m11_zero_pos)
        
    if command == "break":
        print("exit Odrive\n")
        break

