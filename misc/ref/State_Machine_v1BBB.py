#!/usr/bin/python

import smbus, time, math, random, subprocess, traceback
from subprocess import Popen, PIPE
import pty
import os


# ============================================================================
# State Machine, v1 8/8/14,  E J Rouse, J F Duval
# Modified for BBB from original versino on RPi
# See Rouse et al. 2014, IJRR, Clutchable series-elastic actuator: implications for prosthetic knee design
# ============================================================================

from DataLogger import dataLogger

data = []


# ============================================================================
# Initializations

master, slave = pty.openpty()

cproc = Popen(["./planm"], stdin=subprocess.PIPE, stdout=slave)
stdin_handle = cproc.stdin
stdout_handle = os.fdopen(master)

# Setup data output filename -- Data are saved on state machine exit
trial_num = int(raw_input('Trial Number? '))
filename = 'Test%i_080814' % trial_num
dl = dataLogger(filename + '.txt')
print 'starting...'
t0 = time.time()

i = 0.0

# ============================================================================
# State variable definitions
# See manuscript for detailed explanation of state machine control laws and math
# Rouse et al. 2014, IJRR, Clutchable series-elastic actuator: implications for prosthetic knee design


# State 1
t_brkdly = 0.0              # Delay time until brake turns on
vL_frac = 0.9               # Voltage threshold fraction from max to exit stance
t_brk1 = 0.4                # B: 0.5, Time to wait before allowing out of stance phase
comp_thresh1 = 10           # Degrees of compression permitted before transition to State 2

# State 2
thetadot_thresh2 = -5.0     # Threshold to switch from State 2 to State 3 (swing flexion to swing extension)
theta_thresh2 = -20         # Angle must be less than this to switch from State 2 to State 3 (swing flexion to extension)
Q_const2 = 0.1              # Quadratic coefficient for State 2 (swing flexion)
KD_S2 = 0                   # Constant damping during State 2 (swing flexion)

# State 3
theta_thresh3 = -30.0       # Threshold when damping function changes to quadratic; State 3 to State 4
KD_S3 = 0                   # Constant damping during State 3 (early swing extension) 

# State 4
vL_thresh4 = 1.6            # Voltage to indicate extension moment (heel contact), State 4 to State 1
Q_const4 = 0.2              #L:1.8, B: 1.9, Quadratic coefficient for State 4 (late swing extension)
thetadot_thresh4 = -5       # Threshold to switch from State 4 to State 1 (swing extension to stance)
theta_thresh4 = -5          #B: -5, Threshold that permits State 4 to State 1 (Swing extension to flexion)


thetak_thresh = -35.0       # Some agreegment between CPOS and this variable is necessary
theta_ramp_len = 7.0        # FLOAT Ramp length for stiffness value.  Stiffness begins at 0 and ramps to full in this length
vL_thresh_stance = 4.1      # Threshold to return to stance, ie weightbearing
KP = 50                    # Stiffness during spring floating window 

##########################################################################################
# Setting equilibrium angle and control type / gains
#
stdin_handle.write("execute_1 set_control 4\n")                               # Resetting control mode so impedance values are zero                 # Calling read function to drive
trash = stdout_handle.readline()                                            # Reading trash
stdin_handle.write("execute_1 set_current_gains 7 20 0\n")                  # Setting inner current loop PID gains                 
trash = stdout_handle.readline()                                            # Reading trash

equilibrium_angle = 35.0                                                    # Equilibrium angle
converted_angle = int((equilibrium_angle * 143 / (360.0/500.0)) + 3250.0)   # Converted by encoder, transmission and offsets
sendout = "execute_1 trapeze %d %d %d %d\n" % (converted_angle, converted_angle, 1, 1)
stdin_handle.write(sendout)                                                 # Calling read function to drive
trash = stdout_handle.readline()                                            # Receiving trash
sendout = ""

# Pretty hacky way to output the above var definitions - Saved for future reference
#params = ['vL_thresh1', 't_brk1', 'comp_thresh1', 'thetadot_thresh2', 'theta_thresh2', 'Q_const2', 'KD_S2', 'theta_thresh3', 'KD_S3', 'vL_thresh4', 'Q_const4', 'thetadot_thresh4', 'theta_thresh4', 'thetak_thresh', 'theta_ramp_len', 'vL_thresh_stance', 'KP']
#f = open(filename + '_params.txt', 'w')
#for param in params:
#    f.write('%s: %s\n' % (param, eval(param)))
#f.close()


# Parameter Initializations
KDP = 0
KPP = 0  
theta_prev = 0.0
thetadot_prev = 0.0
thetadot_prev2 = 0.0
t_theta_prev = 0.0
state = 2
ts = time.time()
vL_max = 0.0 
vL_frac = 0.9
brake = 0
state_trans_flag = 1

#while (time.time() - t0) < 300:   
while True:
    try:
    # =====================================================================================
        # Data acquisition and manipuation
        i = i + 1
        t1 = time.time() - t0
        stdin_handle.write("execute_1 read 0\n")                        # Calling read function to drive
        #print "reading..."
        cout = stdout_handle.readline()                                 # Receiving values
        #print "done!"
        time.sleep(0.01)
        cout = cout.replace("[", "")                                    # Remove brackets for parsing data
        cout = cout.replace("]", "")
        vals = cout.split(',')                                          # Split up comma separated values from C code
        thetak = (float(vals[0])-2808.0)*(109.2/(2808.0-592.0))         # 2808 is counts (bits) at full extension, 592 is bits at full flexion over 109.2 degrees, verified from Solidworks file (8/8/14)
        thetadot = (thetak - theta_prev)/(time.time() - t_theta_prev)            # Angular velocity calculated by finite difference.  This should be refined and checked....
        vL = float(vals[1])*(5.0/4096.0)                                # Voltage of FSR load sensor converted from bits
        thetam = ((float(vals[2])-3250.0)*(360.0/500.0)) / 143.0      # Motor position, in knee angle reference (N = 143)
        spring_comp = thetam - thetak                                   # Postive value means energy in flexion spring
        t_theta_prev = time.time()                                      # dt for derivative calculation
        # ======================================================================================
        # State Machine

        # Sliding K window state, implemented in State 3 and 4 only
        if thetak < thetak_thresh and (state == 3 or state == 4):
            if (thetak - theta_startk) < theta_ramp_len:
                KPP = int((math.fabs(thetak - theta_startk)/theta_ramp_len)*KP)
            else:
                KPP = KP
        else:
            theta_startk = thetak
            KPP = 0

        # Stance, State 1
        if state == 1:
            if state_trans_flag == 1:
                state_trans_flag = 0
                stdin_handle.write("execute_1 set_leds 0 0 255 0\n") # Turn on LED, Green
                trash = stdout_handle.readline()
                time.sleep(0.003)
            if ((time.time() - ts) > t_brkdly) & brake == 0:
                brake = 1
                stdin_handle.write("execute_1 set_clutch 2\n") # Set clutch ON
                trash = stdout_handle.readline()
                time.sleep(0.003)
            if vL > vL_max:
                vL_max = vL
            if (vL < (vL_frac * vL_max)) & ((time.time() - ts) > t_brk1):
                state_trans_flag = 1
                state = 2


        # Swing Flexion, State 2
        elif state == 2:
            stdin_handle.write("execute_1 set_clutch 0\n") # Set clutch OFF
            trash = stdout_handle.readline()
            time.sleep(0.002)
            brake = 0
            if state_trans_flag == 1:
                state_trans_flag = 0
                stdin_handle.write("execute_1 set_leds 0 0 0 255\n") # Turn on LED, Blue
                trash = stdout_handle.readline()
            KDP = int(((thetak - 0)**2)*Q_const2 + KD_S2)
            if thetak > thetak_thresh:
                KPP = 100
            if (thetadot > thetadot_thresh2) and (thetak < theta_thresh2): 
                state_trans_flag = 1
                state = 3

        # Swing Extension-pre damping profile, State 3
        elif state == 3:
            stdin_handle.write("execute_1 set_clutch 0\n") # Set clutch OFF
            trash = stdout_handle.readline()
            time.sleep(0.002)
            brake = 0
            if state_trans_flag == 1:
                state_trans_flag = 0
                stdin_handle.write("execute_1 set_leds 0 255 0 0\n") # Turn on LED, Red
                trash = stdout_handle.readline()
            KDP = KD_S3
            if thetak > theta_thresh3:
                state_trans_flag = 1
                state = 4

        # Swing Extension-damping profile, State 4
        elif state == 4:
            brake = 0
            stdin_handle.write("execute_1 set_clutch 0\n") # Set clutch OFF
            trash = stdout_handle.readline()
            time.sleep(0.002)
            if state_trans_flag == 1:
                state_trans_flag = 0
                stdin_handle.write("execute_1 set_leds 0 255 255 255\n") # Turn on LED, White
                trash = stdout_handle.readline()
            KDP = int(((thetak - theta_thresh3)**2)*Q_const4 + KD_S3)
            if ((thetadot < thetadot_thresh4) and (thetak > theta_thresh4)):# or vL < vL_thresh4:
                ts = time.time()
                state_trans_flag = 1
                state = 1

        # Set motor impedance values

        sendout = "execute_1 set_z_gains %d %d 0\n" % (KPP, KDP)
        stdin_handle.write(sendout)                 # Set impedance values to drive
        trash = stdout_handle.readline()

        thetadot_prev2 = thetadot_prev
        thetadot_prev = thetadot
        theta_prev = thetak

        # Data matrix for storage -- needs to have motor current and voltage added
        #data = [i] + [t1] + [brake+0.0] + [thetak] + [thetadot] + [vL]   + [thetam]  + [state + 0.0] + [KPP + 0.0] + [KDP + 0.0] + [t2]
        #        1      2         3          4            5          6         7              8             9              10         11   
        #dl.appendData(data)

        # Print some values for status...
        if i%10 == 0: 
            #pass
            #print thetak, state, brake, thetadot#, vL, i, sendout
            print sendout
        time.sleep(0.001)

    except KeyboardInterrupt:
        print 'State machine stopped by user'
        break
    except Exception as e:
        print 'Unexpected exception...'
        print traceback.format_exc()
        print 'Unhandled exception in main loop:', e

time.sleep(.1)
print "Iterations: %.2f " % (i)
print "Elapsed Time: %.2f " % (time.time()-t0)
stdin_handle.write("execute_1 set_leds 0 0 0 0\n") # Turn OFF LED
trash = stdout_handle.readline()
#Set motor impedance to desired value
stdin_handle.write("execute_1 set_control 0\n")                 # Set impedance values to drive
trash = stdout_handle.readline()
stdin_handle.write("quit\n")
trash = stdout_handle.readline()

# Save data
#dl.writeOut()

