#!/usr/bin/python

import time, math, random, subprocess, traceback
from subprocess import Popen, PIPE
import pty
import os

# ============================================================================
# Based on:
# State Machine, v1 8/8/14,  E J Rouse, J F Duval
# Modified for BBB from original versino on RPi
# See Rouse et al. 2014, IJRR, Clutchable series-elastic actuator: implications for prosthetic knee design
# ============================================================================

#from DataLogger import dataLogger

data = []


# ============================================================================
# Initializations

master, slave = pty.openpty()

cproc = Popen(["./planm"], stdin=subprocess.PIPE, stdout=slave)
stdin_handle = cproc.stdin
stdout_handle = os.fdopen(master)

# Setup data output filename -- Data are saved on state machine exit
trial_num = int(raw_input('Trial Number? '))
filename = 'Test%i_03132015' % trial_num
#dl = dataLogger(filename + '.txt')
print 'starting...'
t0 = time.time()

i = 0.0

while True:
    try:
    # =====================================================================================
        # Data acquisition and manipuation
        i = i + 1
        t1 = time.time() - t0
        stdin_handle.write("execute_1 special1 0 0 0 0 0 0\n")
        cout = stdout_handle.readline()                                 # Receiving values
        print cout

	#Delay
        time.sleep(0.1)

    except KeyboardInterrupt:
        print 'State machine stopped by user.'
        break
    except Exception as e:
        print 'Unexpected exception...'
        print traceback.format_exc()
        print 'Unhandled exception in main loop:', e

time.sleep(.1)
print "Iterations: %.2f " % (i)
print "Elapsed Time: %.2f " % (time.time()-t0)
stdin_handle.write("quit\n")

# Save data
#dl.writeOut()

