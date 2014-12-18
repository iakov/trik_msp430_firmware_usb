__author__ = 'Rostislav Varzar'

import termios, fcntl, sys, os
import trik_protocol, trik_motor
import trik_stty, trik_power
import time

# Defines for menu pages
motor_menu = 0x00
motor_enchanced_menu = 0x01

motnum = trik_motor.motor1
pwmper = 0x0000
pwmdut = 0x0000


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

# Init Serial TTY device
trik_stty.init_stty()

# Init 12 V power in ARM controller
trik_power.init_power()

# Read data from motor1
pwmper = trik_protocol.get_reg_value(trik_motor.get_motor_period(motnum))
pwmdut = trik_protocol.get_reg_value(trik_motor.get_motor_duty(motnum))

# Print menu
menu_pg = motor_menu
print_menu(menu_pg)

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
            if c == "7":
                trik_motor.start_motor(motnum)
            if c == "8":
                trik_motor.reverse_motor(motnum)
            if c == "9":
                trik_motor.brake_motor(motnum)
            if c == "0":
                trik_motor.stop_motor(motnum)

            # Music
            """
            if c == "q":
                trik_motor.set_motor_period(motnum, 2500)
                trik_motor.set_motor_duty(motnum, 500)
            if c == "w":
                trik_motor.set_motor_period(motnum, 5000)
                trik_motor.set_motor_duty(motnum, 1000)
            if c == "e":
                trik_motor.set_motor_period(motnum, 7500)
                trik_motor.set_motor_duty(motnum, 1500)
            if c == "r":
                trik_motor.set_motor_period(motnum, 10000)
                trik_motor.set_motor_duty(motnum, 2000)
            if c == "t":
                trik_motor.set_motor_period(motnum, 12500)
                trik_motor.set_motor_duty(motnum, 2500)
            if c == "y":
                trik_motor.set_motor_period(motnum, 15000)
                trik_motor.set_motor_duty(motnum, 3000)
            if c == "u":
                trik_motor.set_motor_period(motnum, 17500)
                trik_motor.set_motor_duty(motnum, 3500)
            if c == "i":
                trik_motor.set_motor_period(motnum, 20000)
                trik_motor.set_motor_duty(motnum, 4000)
            if c == "o":
                trik_motor.set_motor_period(motnum, 22500)
                trik_motor.set_motor_duty(motnum, 4500)
            if c == "p":
                trik_motor.set_motor_period(motnum, 25000)
                trik_motor.set_motor_duty(motnum, 5000)
            if c == "a":
                trik_motor.set_motor_period(motnum, 27500)
                trik_motor.set_motor_duty(motnum, 5500)
            if c == "s":
                trik_motor.set_motor_period(motnum, 30000)
                trik_motor.set_motor_duty(motnum, 6000)
            if c == "d":
                trik_motor.set_motor_period(motnum, 32500)
                trik_motor.set_motor_duty(motnum, 6500)
            if c == "f":
                trik_motor.set_motor_period(motnum, 35000)
                trik_motor.set_motor_duty(motnum, 7000)
            if c == "g":
                trik_motor.set_motor_period(motnum, 37500)
                trik_motor.set_motor_duty(motnum, 7500)
            if c == "h":
                trik_motor.set_motor_period(motnum, 40000)
                trik_motor.set_motor_duty(motnum, 8000)
            if c == "j":
                trik_motor.set_motor_period(motnum, 42500)
                trik_motor.set_motor_duty(motnum, 8500)
            if c == "k":
                trik_motor.set_motor_period(motnum, 45000)
                trik_motor.set_motor_duty(motnum, 9000)
            if c == "l":
                trik_motor.set_motor_period(motnum, 47500)
                trik_motor.set_motor_duty(motnum, 9500)
            if c == "z":
                trik_motor.set_motor_period(motnum, 50000)
                trik_motor.set_motor_duty(motnum, 10000)
            if c == "x":
                trik_motor.set_motor_period(motnum, 52500)
                trik_motor.set_motor_duty(motnum, 10500)
            if c == "c":
                trik_motor.set_motor_period(motnum, 55000)
                trik_motor.set_motor_duty(motnum, 11000)
            if c == "v":
                trik_motor.set_motor_period(motnum, 57500)
                trik_motor.set_motor_duty(motnum, 11500)
            if c == "b":
                trik_motor.set_motor_period(motnum, 60000)
                trik_motor.set_motor_duty(motnum, 12000)
            if c == "n":
                trik_motor.set_motor_period(motnum, 62500)
                trik_motor.set_motor_duty(motnum, 12500)
            if c == "m":
                trik_motor.set_motor_period(motnum, 65000)
                trik_motor.set_motor_duty(motnum, 13000)
            if c <= "z" and c >= "a":
                trik_motor.start_motor(motnum)
                time.sleep(0.2)
                trik_motor.brake_motor(motnum)
            """








            print_menu(menu_pg)

            if c == chr(0x1B):
                break
        except IOError: pass
finally:
    termios.tcsetattr(fd, termios.TCSAFLUSH, oldterm)
    fcntl.fcntl(fd, fcntl.F_SETFL, oldflags)
