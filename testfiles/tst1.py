import termios, fcntl, sys, os

# Defines for menu pages
motor_menu = 0x00

# Output device
fname1 = "000.txt"
# fname1 = "/dev/ttyACM0"

# Motor addresses
motor1 = 0x00
motor2 = 0x01
motor3 = 0x02
motor4 = 0x03

# Write single 16bit register
def write_16bit_reg(devaddr, funcnum, regaddr, regval):
    crc = 0xFF - (devaddr + funcnum + regaddr + (regval & 0xFF) + ((regval >> 8) & 0xFF)) + 1
    stmp = ":%02X%02X%02X%04X%02X\n" % (devaddr, funcnum, regaddr, regval, crc)
    f1 = open(fname1, "wb")
    f1.write(stmp)
    f1.close()
    print(stmp)

# Write single 32bit register
def write_32bit_reg(devaddr, funcnum, regaddr, regval):
    crc = 0xFF - (devaddr + funcnum + regaddr + (regval & 0xFF) + ((regval >> 8) & 0xFF) + ((regval >> 16) & 0xFF) + ((regval >> 24) & 0xFF)) + 1
    stmp = ":%02X%02X%02X%08X%02X\n" % (devaddr, funcnum, regaddr, regval, crc)
    f1 = open(fname1, "wb")
    f1.write(stmp)
    f1.close()
    print(stmp)

# Set PWM period for motor
def set_motor_period(motnum, pwmper):
    write_16bit_reg(motnum, 0x03, 0x02, pwmper)

# Set PWM duty for motor
def set_motor_duty(motnum, pwmdut):
    write_16bit_reg(motnum, 0x03, 0x01, pwmdut)

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
    os.system('clear')
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



init_key_press()

menu_pg = motor_menu

print_menu(menu_pg)

try:
    while 1:
        try:
            c = ord(sys.stdin.read(1))
            print_menu(menu_pg)
            if c == 0x1B:
                break
        except IOError: pass
finally:
    termios.tcsetattr(fd, termios.TCSAFLUSH, oldterm)
    fcntl.fcntl(fd, fcntl.F_SETFL, oldflags)