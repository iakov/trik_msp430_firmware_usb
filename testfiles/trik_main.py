__author__ = 'Rostislav Varzar'

import termios, fcntl, sys, os
import trik_protocol, trik_motor

# Defines for menu pages
motor_menu = 0x00

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
sty1 = "stty -F %s -echo -onlcr" % (trik_protocol.fname1)
os.system(sty1)


# Main cycle
try:
    while 1:
        try:
            c = ord(sys.stdin.read(1))
            print_menu(menu_pg)
            #read_16bit_reg(0x00, 0x00)
            #read_32bit_reg(0x00, 0x04)
            print trik_protocol.get_reg_value(":031101EB\n")



            if c == 0x1B:
                break
        except IOError: pass
finally:
    termios.tcsetattr(fd, termios.TCSAFLUSH, oldterm)
    fcntl.fcntl(fd, fcntl.F_SETFL, oldflags)
