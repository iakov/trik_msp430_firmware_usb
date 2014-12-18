import termios, fcntl, sys, os

# Defines for menu pages
motor_menu = 0x00

# Output device
# fname1 = "000.txt"
fname1 = "/dev/ttyACM0"

# Motor addresses
motor1 = 0x00
motor2 = 0x01
motor3 = 0x02
motor4 = 0x03

# Function to recognize response packets
def get_reg_value(stmp):
    if len(stmp) == 8:
        devaddr = int(("0x" + stmp[1] + stmp[2]), 16)
        respcode = int(("0x" + stmp[3] + stmp[4]), 16)
        crc1 = int(("0x" + stmp[5] + stmp[6]), 16)
        crc2 = (0xFF - (devaddr + respcode) + 1) & 0xFF
        if crc1 != crc2:
            rval = -1
        else:
            rval = respcode
    elif len(stmp) == 14:
        devaddr = int(("0x" + stmp[1] + stmp[2]), 16)
        respcode = int(("0x" + stmp[3] + stmp[4]), 16)
        regaddr = int(("0x" + stmp[5] + stmp[6]), 16)
        regval = int(("0x" + stmp[7] + stmp[8] + stmp[9] + stmp[10]), 16)
        crc1 = int(("0x" + stmp[11] + stmp[12]), 16)
        crc2 = (0xFF - (devaddr + respcode + regaddr + (regval & 0xFF) + ((regval >> 8) & 0xFF)) + 1) & 0xFF
        if crc1 != crc2:
            rval = -2
        else:
            rval = regval
    elif len(stmp) == 18:
        devaddr = int(("0x" + stmp[1] + stmp[2]), 16)
        respcode = int(("0x" + stmp[3] + stmp[4]), 16)
        regaddr = int(("0x" + stmp[5] + stmp[6]), 16)
        regval = int(("0x" + stmp[7] + stmp[8] + stmp[9] + stmp[10]), 16)
        crc1 = int(("0x" + stmp[11] + stmp[12]), 16)
        crc2 = (0xFF - (devaddr + respcode + regaddr + (regval & 0xFF) + ((regval >> 8) & 0xFF) + ((regval >> 16) & 0xFF) + ((regval >> 24) & 0xFF)) + 1) & 0xFF
        if crc1 != crc2:
            rval = -3
        else:
            rval = regval
    elif len(stmp) == 10:
        devaddr = int(("0x" + stmp[1] + stmp[2]), 16)
        funccode = int(("0x" + stmp[3] + stmp[4]), 16)
        errcode = int(("0x" + stmp[5] + stmp[6]), 16)
        crc1 = int(("0x" + stmp[7] + stmp[8]), 16)
        crc2 = (0xFF - (devaddr + funccode + errcode) + 1) & 0xFF
        if crc1 != crc2:
            rval = -4
        else:
            rval = errcode
    else:
        rval = -5
    return rval

# Write single 16bit register
def write_16bit_reg(devaddr, regaddr, regval):
    f2 = open(fname1, "r")
    funcnum = 0x03
    crc = (0xFF - (devaddr + funcnum + regaddr + (regval & 0xFF) + ((regval >> 8) & 0xFF)) + 1) & 0xFF
    stmp = ":%02X%02X%02X%04X%02X\n" % (devaddr, funcnum, regaddr, regval, crc)
    f1 = open(fname1, "wb")
    f1.write(stmp)
    f1.close()
    stmp = f2.readline()
    f2.close()
    print(stmp)

# Write single 32bit register
def write_32bit_reg(devaddr, regaddr, regval):
    f2 = open(fname1, "r")
    funcnum = 0x04
    crc = (0xFF - (devaddr + funcnum + regaddr + (regval & 0xFF) + ((regval >> 8) & 0xFF) + ((regval >> 16) & 0xFF) + ((regval >> 24) & 0xFF)) + 1) & 0xFF
    stmp = ":%02X%02X%02X%08X%02X\n" % (devaddr, funcnum, regaddr, regval, crc)
    f1 = open(fname1, "wb")
    f1.write(stmp)
    f1.close()
    stmp = f2.readline()
    f2.close()
    print(stmp)

# Read single 16 bit register
def read_16bit_reg(devaddr, regaddr):
    f2 = open(fname1, "r")
    funcnum = 0x05
    crc = (0xFF - (devaddr + funcnum + regaddr) + 1) & 0xFF
    stmp = ":%02X%02X%02X%02X\n" % (devaddr, funcnum, regaddr, crc)
    f1 = open(fname1, "wb")
    f1.write(stmp)
    f1.close()
    stmp = f2.readline()
    f2.close()
    print(stmp)

# Read single 32 bit register
def read_32bit_reg(devaddr, regaddr):
    f2 = open(fname1, "r")
    funcnum = 0x06
    crc = (0xFF - (devaddr + funcnum + regaddr) + 1) & 0xFF
    stmp = ":%02X%02X%02X%02X\n" % (devaddr, funcnum, regaddr, crc)
    f1 = open(fname1, "wb")
    f1.write(stmp)
    f1.close()
    stmp = f2.readline()
    f2.close()
    print(stmp)






# Set PWM period for motor
def set_motor_period(motnum, pwmper):
    write_16bit_reg(motnum, 0x02, pwmper)

# Set PWM duty for motor
def set_motor_duty(motnum, pwmdut):
    write_16bit_reg(motnum, 0x01, pwmdut)




# Init async key press input without press <ENTER>
def init_key_press():
    global fd
    global oldterm
    global oldflags
    fd = sys.stdin.fileno()
    oldterm = termios.tcgetattr(fd)
    newattr = termios.tcgetattr(fd)
    newattr[3] = newattr[3] & ~termios.ICANON & ~termios.ECHO
    termios.tcsetattr(fd, termios.TCSANOW, newattr)
    oldflags = fcntl.fcntl(fd, fcntl.F_GETFL)
    fcntl.fcntl(fd, fcntl.F_SETFL, oldflags | os.O_NONBLOCK)

# Print text of menu
def print_menu(menu_page):
    os.system("clear")
    if menu_page == 0x00:
        print ("""
Select menu item:

<1/2> Select motor    %u
<3/4> Set PWM period  %u
<5/6> Set PWM duty    %u
<7>   Start motor
<8>   Reverse motor
<9>   Brake motor
<0>   Stop motor
<ESC> Exit/Quit
            """) % (0, 0, 0)

# Init async key press
init_key_press()

# Print menu
menu_pg = motor_menu
print_menu(menu_pg)

# Init tty device
sty1 = "stty -F %s -echo -onlcr" % (fname1)
os.system(sty1)


# Main cycle
try:
    while 1:
        try:
            c = ord(sys.stdin.read(1))
            print_menu(menu_pg)
            #read_16bit_reg(0x00, 0x00)
            #read_32bit_reg(0x00, 0x04)
            print get_reg_value(":031101EB\n")



            if c == 0x1B:
                break
        except IOError: pass
finally:
    termios.tcsetattr(fd, termios.TCSAFLUSH, oldterm)
    fcntl.fcntl(fd, fcntl.F_SETFL, oldflags)
