__author__ = 'Rostislav Varzar'

import termios, fcntl, sys, os, thread, time
import trik_protocol, trik_motor, trik_encoder, trik_timer, trik_sensor, trik_touch, trik_bsl
import trik_stty, trik_power
import random
import datetime

freport = "trik_report1.txt"

# Test register values
testregvals = [0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D,
               0x0E, 0x0F, 0x10,
               0xFE, 0xFF, 0x100,
               0xFFE, 0xFFF, 0x1000,
               0xFFFE, 0xFFFF, 0x10000,
               0xFFFFE, 0xFFFFF, 0x100000,
               0xFFFFFE, 0xFFFFFF, 0x1000000,
               0xFFFFFFE, 0xFFFFFFF, 0x10000000,
               0xFFFFFFFE, 0xFFFFFFFF]

# Errors descriptions
testerrors = ["No error",
              "Illegal Function Code",
              "Illegal Register Address",
              "Illegal Register Value",
              "Slave Device Failure",
              "Undefined",
              "Slave Device Busy",
              "Undefined",
              "Undefined",
              "Undefined",
              "Undefined",
              "Undefined",
              "Undefined",
              "Undefined",
              "Undefined",
              "Undefined",
              "Undefined",
              "Illegal Device Address",
              "CRC Error",
              "Start condition error",
              "Incorrect packet length",
              "Inconsistency of Multiple Registers"]

# Init Serial TTY device
trik_stty.init_stty()

# Init 12 V power in ARM controller
trik_power.enable_power()

# Start thread to read response data from device
thread.start_new_thread(trik_protocol.thread1_read_device, ())
time.sleep(5)

# Clear screen
os.system("clear")

# Test all device addresses and all register addresses and some registers values (writing mode)
def stress_test_writing():
    global testregvals
    devaddr = 0x00
    while devaddr <= 0xFF:
        f = open(freport, "a")
        regaddr = 0x00
        while regaddr <= 0xFF:
            stmp1 = "\n----------" + datetime.datetime.now().isoformat() + "----------\n"
            f.write(stmp1)
            stmp1 = "----------Device address: 0x%02X---------------- \n" % (devaddr)
            f.write(stmp1)
            stmp1 = "----------Register address: 0x%02X-------------- \n" % (regaddr)
            f.write(stmp1)
            ridx = 0x00
            while ridx < len(testregvals):
                regval = testregvals[ridx]
                stmp1 = "\n Writing... \n"
                f.write(stmp1)
                stmp1 = "Register value: 0x%08X \n" % (regval)
                f.write(stmp1)
                stmp1 = trik_protocol.write_reg(devaddr, regaddr, regval)
                rval, daddr, rcode, ecode = trik_protocol.get_reg_value(stmp1)
                if rcode < 0x80:
                    stmp1 = "No error \n"
                else:
                    stmp1 = "Error flag set \n"
                f.write(stmp1)
                if rval <= 0x15:
                    stmp1 = "Error code: 0x%08X, %s \n" % (rval, testerrors[rval])
                else:
                    stmp1 = "Error code: 0x%08X, %s \n" % (rval, "Undefined")
                f.write(stmp1)
                stmp1 = "DEV=0x%02X REG=0x%02X SEND=0x%08X RECV=0x%08X" % (devaddr, regaddr, regval, rval)
                print stmp1
                ridx = ridx + 1
            regaddr = regaddr + 1
        f.close()
        devaddr = devaddr + 1

stress_test_writing()

