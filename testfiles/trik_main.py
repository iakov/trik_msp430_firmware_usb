__author__ = 'Rostislav Varzar'

import termios, fcntl, sys, os, struct
import trik_protocol, trik_motor, trik_encoder, trik_timer
import trik_stty, trik_power
import time

# Defines for menu pages
motor_menu = 0x00
encoder_menu = 0x01
sensor_menu = 0x02
timer_menu = 0x03
bsl_menu = 0x04
menu_pg = motor_menu

# Motor registers values
motnum = trik_motor.motor1
pwmper = 0x0000
pwmdut = 0x0000
motangle = 0x00000000
mottime = 0x00000000
moterr = 0x00000000
motfb = 0x00000000
encval = 0x00000000
motctl = 0x0000

# Encoder registers values
ectl1 = 0x0000
ectl2 = 0x0000
ectl3 = 0x0000
ectl4 = 0x0000
eval1 = 0x00000000
eval2 = 0x00000000
eval3 = 0x00000000
eval4 = 0x00000000
epul1 = 0
epul2 = 0
epul3 = 0
epul4 = 0
eedg1 = 0
eedg2 = 0
eedg3 = 0
eedg4 = 0
ewr1 = 0
ewr2 = 0
ewr3 = 0
ewr4 = 0
eper = 0x0000

# Async counter
acnt = 0
cnti = acnt

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
    if menu_page == motor_menu:
        print_there(0, 1, "MOTORs MENU")
        print_there(0, 2, "Select menu item:")
        print_there(0, 4, "<1/2> Select motor")
        print_there(0, 5, "<3/4> Set PWM period")
        print_there(0, 6, "<5/6> Set PWM duty")
        print_there(0, 7, "<7>   Start motor")
        print_there(0, 8, "<8>   Reverse motor")
        print_there(0, 9, "<9>   Brake motor")
        print_there(0, 10, "<0>   Stop motor")
        print_there(0, 11, "<Q/W> Set angle")
        print_there(0, 12, "<E/R> Set time")
        print_there(0, 13, "<A>   Rotate angle")
        print_there(0, 14, "<S>   Reverse angle")
        print_there(0, 15, "<T>   Rotate time")
        print_there(0, 16, "<Y>   Reverse time")
        print_there(0, 17, "<C>   Redraw screen")
        print_there(0, 18, "<TAB> Change device group")
        print_there(0, 19, "<ESC> Exit/Quit")
        print_there(0, 21, "Control register")
        print_there(0, 22, "Feed-back value")
        print_there(0, 23, "Encoder value")
        print_there(0, 24, "Overcurrent errors")
    elif menu_page == encoder_menu:
        print_there(0, 1, "ENCODERs MENU")
        print_there(0, 2, "Select menu item:")
        print_there(0, 4, "<1>   Encoder1 pullup on/off")
        print_there(0, 5, "<2>   Encoder2 pullup on/off")
        print_there(0, 6, "<3>   Encoder3 pullup on/off")
        print_there(0, 7, "<4>   Encoder4 pullup on/off")
        print_there(0, 8, "<5>   Encoder1 1wire/2wires")
        print_there(0, 9, "<6>   Encoder2 1wire/2wires")
        print_there(0, 10, "<7>   Encoder3 1wire/2wires")
        print_there(0, 11, "<8>   Encoder4 1wire/2wires")
        print_there(0, 12, "<A>   Encoder1 fall/rise edge")
        print_there(0, 13, "<S>   Encoder2 fall/rise edge")
        print_there(0, 14, "<D>   Encoder3 fall/rise edge")
        print_there(0, 15, "<F>   Encoder4 fall/rise edge")
        print_there(0, 16, "<C>   Redraw screen")
        print_there(0, 17, "<9/0> Reading interval")
        print_there(0, 18, "<R>   Enter async mode")
        print_there(0, 19, "<N/M> Set async counter")
        print_there(0, 20, "<TAB> Change device group")
        print_there(0, 21, "<ESC> Exit/Quit")
        print_there(0, 23, "Encoder1 control")
        print_there(0, 24, "Encoder2 control")
        print_there(0, 25, "Encoder3 control")
        print_there(0, 26, "Encoder4 control")
        print_there(0, 27, "Encoder1 value")
        print_there(0, 28, "Encoder2 value")
        print_there(0, 29, "Encoder3 value")
        print_there(0, 30, "Encoder4 value")
        print_there(0, 31, "Async counter")
    elif menu_page == sensor_menu:
        print_there(0, 1, "SENSORs MENU")
        print_there(0, 2, "Select menu item:")
        print_there(0, 18, "<TAB> Change device group")
        print_there(0, 19, "<ESC> Exit/Quit")
    elif menu_page == timer_menu:
        print_there(0, 1, "TIMER MENU")
        print_there(0, 2, "Select menu item:")
        print_there(0, 18, "<TAB> Change device group")
        print_there(0, 19, "<ESC> Exit/Quit")
    elif menu_page == bsl_menu:
        print_there(0, 1, "BSL MENU")
        print_there(0, 2, "Select menu item:")
        print_there(0, 18, "<TAB> Change device group")
        print_there(0, 19, "<ESC> Exit/Quit")

# Print register values
def print_registers(menu_page):
    global pwmper
    global pwmdut
    global motangle
    global mottime
    global motctl
    global motfb
    global encval
    global moterr
    global ectl1
    global ectl2
    global ectl3
    global ectl4
    global eval1
    global eval2
    global eval3
    global eval4
    global epul1
    global epul2
    global epul3
    global epul4
    global eedg1
    global eedg2
    global eedg3
    global eedg4
    global ewr1
    global ewr2
    global ewr3
    global ewr4
    global eper
    if menu_page == motor_menu:
        print_there(25, 4, "0x%02X " % motnum)
        print_there(25, 5, "%05u " % pwmper)
        print_there(25, 6, "%05u " % pwmdut)
        print_there(25, 11, "%010u " % motangle)
        print_there(25, 12, "%010u " % mottime)
        print_there(25, 21, "0x%04X " % motctl)
        print_there(25, 22, "%010u " % motfb)
        print_there(25, 23, "%010u " % encval)
        print_there(25, 24, "%010u " % moterr)
    elif menu_page == encoder_menu:
        print_there(30, 4, "%01u " % epul1)
        print_there(30, 5, "%01u " % epul2)
        print_there(30, 6, "%01u " % epul3)
        print_there(30, 7, "%01u " % epul4)
        print_there(30, 8, "%01u " % ewr1)
        print_there(30, 9, "%01u " % ewr2)
        print_there(30, 10, "%01u " % ewr3)
        print_there(30, 11, "%01u " % ewr4)
        print_there(30, 12, "%01u " % eedg1)
        print_there(30, 13, "%01u " % eedg2)
        print_there(30, 14, "%01u " % eedg3)
        print_there(30, 15, "%01u " % eedg4)
        print_there(30, 17, "%05u " % eper)
        print_there(30, 19, "%010u " % acnt)
        print_there(30, 23, "0x%04X " % ectl1)
        print_there(30, 24, "0x%04X " % ectl2)
        print_there(30, 25, "0x%04X " % ectl3)
        print_there(30, 26, "0x%04X " % ectl4)
        print_there(30, 27, "%010u " % eval1)
        print_there(30, 28, "%010u " % eval2)
        print_there(30, 29, "%010u " % eval3)
        print_there(30, 30, "%010u " % eval4)
        print_there(30, 31, "%010u " % cnti)

# Print text in certain coordinates
def print_there(x, y, text):
     sys.stdout.write("\x1b7\x1b[%d;%df%s\x1b8" % (y + 1, x + 1, text))
     sys.stdout.flush()

# Init async key press
init_key_press()

# Init Serial TTY device
trik_stty.init_stty()

# Init 12 V power in ARM controller
trik_power.init_power()

# Read all registers of motor
def read_all_data(menu_page):
    global pwmper
    global pwmdut
    global motangle
    global mottime
    global motctl
    global motfb
    global encval
    global moterr
    global ectl1
    global ectl2
    global ectl3
    global ectl4
    global eval1
    global eval2
    global eval3
    global eval4
    global epul1
    global epul2
    global epul3
    global epul4
    global eedg1
    global eedg2
    global eedg3
    global eedg4
    global ewr1
    global ewr2
    global ewr3
    global ewr4
    global eper
    if menu_page == motor_menu:
        pwmper, daddr = trik_protocol.get_reg_value(trik_motor.get_motor_period(motnum))
        pwmdut, daddr = trik_protocol.get_reg_value(trik_motor.get_motor_duty(motnum))
        motangle, daddr = trik_protocol.get_reg_value(trik_motor.get_motor_angle(motnum))
        mottime, daddr = trik_protocol.get_reg_value(trik_motor.get_motor_time(motnum))
        motctl, daddr = trik_protocol.get_reg_value(trik_motor.get_motor_control(motnum))
        moterr, daddr = trik_protocol.get_reg_value(trik_motor.get_motor_overcurrent(motnum))
        motfb, daddr = trik_protocol.get_reg_value(trik_motor.get_motor_feedback(motnum))
        encval, daddr = trik_protocol.get_reg_value(trik_encoder.read_encoder(motnum + trik_encoder.encoder1))
    elif menu_page == encoder_menu:
        ectl1, daddr = trik_protocol.get_reg_value(trik_encoder.get_encoder_control(trik_encoder.encoder1))
        ectl2, daddr = trik_protocol.get_reg_value(trik_encoder.get_encoder_control(trik_encoder.encoder2))
        ectl3, daddr = trik_protocol.get_reg_value(trik_encoder.get_encoder_control(trik_encoder.encoder3))
        ectl4, daddr = trik_protocol.get_reg_value(trik_encoder.get_encoder_control(trik_encoder.encoder4))
        eval1, daddr = trik_protocol.get_reg_value(trik_encoder.read_encoder(trik_encoder.encoder1))
        eval2, daddr = trik_protocol.get_reg_value(trik_encoder.read_encoder(trik_encoder.encoder2))
        eval3, daddr = trik_protocol.get_reg_value(trik_encoder.read_encoder(trik_encoder.encoder3))
        eval4, daddr = trik_protocol.get_reg_value(trik_encoder.read_encoder(trik_encoder.encoder4))

# Read all registers of motor
read_all_data(menu_pg)

# Clear screen
os.system("clear")

# Print menu
print_menu(menu_pg)
print_registers(menu_pg)

# Main cycle
try:
    while 1:
        try:
            c = sys.stdin.read(1)
            if menu_pg == motor_menu:
                if c == "1":
                    motnum = motnum - 1
                    if motnum <= trik_motor.motor1:
                        motnum = trik_motor.motor1
                if c == "2":
                    motnum = motnum + 1
                    if motnum >= trik_motor.motor4:
                        motnum = trik_motor.motor4
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
                if c.upper() == "Q":
                    motangle = motangle - 10
                    if motangle <= 0x00000000:
                        motangle = 0x00000000
                    trik_motor.set_motor_angle(motnum, motangle)
                if c.upper() == "W":
                    motangle = motangle + 10
                    if motangle >= 0xFFFFFFFF:
                        motangle = 0xFFFFFFFF
                    trik_motor.set_motor_angle(motnum, motangle)
                if c.upper() == "E":
                    mottime = mottime - 10
                    if mottime <= 0x00000000:
                        mottime = 0x00000000
                    trik_motor.set_motor_time(motnum, mottime)
                if c.upper() == "R":
                    mottime = mottime + 10
                    if mottime >= 0xFFFFFFFF:
                        mottime = 0xFFFFFFFF
                    trik_motor.set_motor_time(motnum, mottime)
                if c.upper() == "A":
                    trik_encoder.enable_encoder(motnum + trik_encoder.encoder1, 1, 1, 0)
                    trik_motor.rotate_motor_angle(motnum)
                if c.upper() == "S":
                    trik_encoder.enable_encoder(motnum + trik_encoder.encoder1, 1, 1, 0)
                    trik_motor.reverse_motor_angle(motnum)
                if c.upper() == "T":
                    trik_timer.timer_enable()
                    trik_motor.rotate_motor_time(motnum)
                if c.upper() == "Y":
                    trik_timer.timer_enable()
                    trik_motor.reverse_motor_time(motnum)
            elif menu_pg == encoder_menu:
                if c == "1":
                    epul1 = 1 - epul1
                    trik_encoder.enable_encoder(trik_encoder.encoder1, ewr1, epul1, eedg1)
                if c == "2":
                    epul2 = 1 - epul2
                    trik_encoder.enable_encoder(trik_encoder.encoder2, ewr2, epul2, eedg2)
                if c == "3":
                    epul3 = 1 - epul3
                    trik_encoder.enable_encoder(trik_encoder.encoder3, ewr3, epul3, eedg3)
                if c == "4":
                    epul4 = 1 - epul4
                    trik_encoder.enable_encoder(trik_encoder.encoder4, ewr4, epul4, eedg4)
                if c == "5":
                    ewr1 = 1 - ewr1
                    trik_encoder.enable_encoder(trik_encoder.encoder1, ewr1, epul1, eedg1)
                if c == "6":
                    ewr2 = 1 - ewr2
                    trik_encoder.enable_encoder(trik_encoder.encoder2, ewr2, epul2, eedg2)
                if c == "7":
                    ewr3 = 1 - ewr3
                    trik_encoder.enable_encoder(trik_encoder.encoder3, ewr3, epul3, eedg3)
                if c == "8":
                    ewr4 = 1 - ewr4
                    trik_encoder.enable_encoder(trik_encoder.encoder4, ewr4, epul4, eedg4)
                if c.upper() == "A":
                    eedg1 = 1 - eedg1
                    trik_encoder.enable_encoder(trik_encoder.encoder1, ewr1, epul1, eedg1)
                if c.upper() == "S":
                    eedg2 = 1 - eedg2
                    trik_encoder.enable_encoder(trik_encoder.encoder2, ewr2, epul2, eedg2)
                if c.upper() == "D":
                    eedg3 = 1 - eedg3
                    trik_encoder.enable_encoder(trik_encoder.encoder3, ewr3, epul3, eedg3)
                if c.upper() == "F":
                    eedg4 = 1 - eedg4
                    trik_encoder.enable_encoder(trik_encoder.encoder4, ewr4, epul4, eedg4)
                if c == "9":
                    eper = eper - 1
                    if eper <= 0:
                        eper = 0
                if c == "0":
                    eper = eper + 1
                    if eper >= 0xFFFF:
                        eper = 0xFFFF
                if c.upper() == "N":
                    acnt = acnt - 100
                    if acnt <= 0:
                        acnt = 0
                if c.upper() == "M":
                    acnt = acnt + 100
                    if acnt >= 0xFFFFFFFF:
                        acnt = 0xFFFFFFFF
                if c.upper() == "R":
                    trik_timer.set_timer_period(eper)
                    trik_timer.timer_enable()
                    trik_encoder.enable_encoder_in_async(trik_encoder.encoder1, ewr1, epul1, eedg1)
                    trik_encoder.enable_encoder_in_async(trik_encoder.encoder2, ewr2, epul2, eedg2)
                    trik_encoder.enable_encoder_in_async(trik_encoder.encoder3, ewr3, epul3, eedg3)
                    trik_encoder.enable_encoder_in_async(trik_encoder.encoder4, ewr4, epul4, eedg4)
                    cnti = acnt
                    while cnti > 0:
                        rval, daddr = trik_protocol.get_reg_value(trik_protocol.read_async_reg())
                        if daddr == trik_encoder.encoder1:
                            eval1 = rval
                        if daddr == trik_encoder.encoder2:
                            eval2 = rval
                        if daddr == trik_encoder.encoder3:
                            eval3 = rval
                        if daddr == trik_encoder.encoder4:
                            eval4 = rval
                        print_registers(menu_pg)
                        cnti = cnti - 1
            if c.upper() == "C":
                os.system("clear")
                print_menu(menu_pg)
            if c == chr(0x09):
                menu_pg = menu_pg + 1
                if menu_pg > bsl_menu:
                    menu_pg = motor_menu
                os.system("clear")
                print_menu(menu_pg)
            if c == chr(0x1B):
                break

            read_all_data(menu_pg)
            print_registers(menu_pg)
        except IOError: pass
finally:
    termios.tcsetattr(fd, termios.TCSAFLUSH, oldterm)
    fcntl.fcntl(fd, fcntl.F_SETFL, oldflags)
