__author__ = 'Rostislav Varzar'

import time, os
import trik_protocol, trik_stty, trik_power
import random
import pickle
import thread


# Init Serial TTY device
trik_stty.init_stty()

# Init 12 V power in ARM controller
trik_power.enable_power()

# Clear screen
os.system("clear")

fn1 = "/dev/ttyACM0"
fn2 = "000.txt"
fflg = 0x01

# Thread to read and print registers
def thread1_read_device():
    global fn1
    global fn2
    global fflg
    ff1 = open(fn1, "r")
    while fflg:
        if fflg == 0x01:
            stmp = ff1.readline()
            ff2 = open(fn2, "a")
            ff2.writelines(stmp)
            ff2.close()
            print stmp
    ff1.close()
    thread.exit_thread()

thread.start_new_thread(thread1_read_device, ())

time.sleep(3)

ff1 = open(fn1, "w")
ff1.write("Privet! \n")
ff1.close()

ff1 = open(fn1, "w")
ff1.write("Privet! \n")
ff1.close()

ff1 = open(fn1, "w")
ff1.write(":Privet! \n")
ff1.close()

ff1 = open(fn1, "w")
ff1.write(":Pret! \n")
ff1.close()


time.sleep(1)

fflg = 0x00












