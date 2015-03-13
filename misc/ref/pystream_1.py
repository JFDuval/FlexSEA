#!/usr/bin/python

import smbus, time, math, random, subprocess, traceback
from subprocess import Popen, PIPE
import pty
import os

# ============================================================================
# Based on:
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

		#delay
        time.sleep(0.1)

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
trash = stdout_handle.readline()
#Set motor impedance to desired value
stdin_handle.write("execute_1 set_control 0\n")                 # Set impedance values to drive
trash = stdout_handle.readline()
stdin_handle.write("quit\n")
trash = stdout_handle.readline()

# Save data
#dl.writeOut()

