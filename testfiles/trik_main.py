__author__ = 'Rostislav Varzar'

import termios, fcntl, sys, os
import trik_protocol, trik_motor

# Defines for menu pages
motor_menu = 0x00
motor_enchanced_menu = 0x01

motnum = trik_motor.motor1
pwmper = 10000
pwmdut = 0


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
            """) % (motnum, pwmper, pwmdut)

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
            c = sys.stdin.read(1)
            if c == "1":
                motnum = motnum - 1
                if motnum <= trik_motor.motor1:
                    motnum = trik_motor.motor1
                pwmper = trik_protocol.get_reg_value(trik_motor.get_motor_period(motnum))
                pwmdut = trik_protocol.get_reg_value(trik_motor.get_motor_duty(motnum))
            if c == "2":
                motnum = motnum + 1
                if motnum >= trik_motor.motor4:
                    motnum = trik_motor.motor4
                pwmper = trik_protocol.get_reg_value(trik_motor.get_motor_period(motnum))
                pwmdut = trik_protocol.get_reg_value(trik_motor.get_motor_duty(motnum))
            if c == "3":
                if pwmper > pwmdut:
                    pwmper = pwmper - 100
                    if pwmper <= 0:
                        pwmper = 0
                else:
                    pwmper = pwmdut
                trik_motor.set_motor_period(motnum, pwmper)
            if c == "4":
                pwmper = pwmper + 100
                if pwmper >= 0xFFFF:
                    pwmper = 0xFFFF
                trik_motor.set_motor_period(motnum, pwmper)
            if c == "5":
                pwmdut = pwmdut - 100
                if pwmdut <= 0:
                    pwmdut = 0
                trik_motor.set_motor_duty(motnum, pwmdut)
            if c == "6":
                pwmdut = pwmdut + 100
                if pwmdut >= pwmper:
                    pwmdut = pwmper
                trik_motor.set_motor_duty(motnum, pwmdut)



            print_menu(menu_pg)



            if c == chr(0x1B):
                break
        except IOError: pass
finally:
    termios.tcsetattr(fd, termios.TCSAFLUSH, oldterm)
    fcntl.fcntl(fd, fcntl.F_SETFL, oldflags)
