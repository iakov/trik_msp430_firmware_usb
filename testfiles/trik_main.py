__author__ = 'Rostislav Varzar'

import termios, fcntl, sys, os, struct
import trik_protocol, trik_motor, trik_encoder, trik_timer, trik_sensor
import trik_stty, trik_power
import time

# Defines for menu pages
motor_menu = 0x00
encoder_menu = 0x01
sensor_menu = 0x02
timer_menu = 0x03
touch_menu = 0x04
bsl_menu = 0x05
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

# Sensor registers values
sval1 = 0x00000000
sval2 = 0x00000000
sval3 = 0x00000000
sval4 = 0x00000000
sval5 = 0x00000000
sval6 = 0x00000000
sval7 = 0x00000000
sval8 = 0x00000000
sval9 = 0x00000000
sval10 = 0x00000000
sval11 = 0x00000000
sval12 = 0x00000000
sval13 = 0x00000000
sval14 = 0x00000000
sval15 = 0x00000000
sval16 = 0x00000000
sval17 = 0x00000000
sval18 = 0x00000000
sidx1 = 0x0000
sidx2 = 0x0000
sidx3 = 0x0000
sidx4 = 0x0000
sidx5 = 0x0000
sidx6 = 0x0000
sidx7 = 0x0000
sidx8 = 0x0000
sidx9 = 0x0000
sidx10 = 0x0000
sidx11 = 0x0000
sidx12 = 0x0000
sidx13 = 0x0000
sidx14 = 0x0000
sctl1 = 0x0000
sctl2 = 0x0000
sctl3 = 0x0000
sctl4 = 0x0000
sctl5 = 0x0000
sctl6 = 0x0000
sctl7 = 0x0000
sctl8 = 0x0000
sctl9 = 0x0000
sctl10 = 0x0000
sctl11 = 0x0000
sctl12 = 0x0000
sctl13 = 0x0000
sctl14 = 0x0000
spul1 = 0
spul2 = 0
spul3 = 0
spul4 = 0
spul5 = 0
spul6 = 0
spul7 = 0
spul8 = 0
spul9 = 0
spul10 = 0
spul11 = 0
spul12 = 0
spul13 = 0
spul14 = 0

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
        print_there(0, 18, "Control register")
        print_there(0, 19, "Feed-back value")
        print_there(0, 20, "Encoder value")
        print_there(0, 21, "Overcurrent errors")
        print_there(0, 23, "<C>   Redraw screen")
        print_there(0, 24, "<TAB> Change device group")
        print_there(0, 25, "<ESC> Exit/Quit")
    elif menu_page == encoder_menu:
        print_there(0, 1, "ENCODERs MENU")
        print_there(0, 2, "Select menu item:")
        print_there(0, 4, "<1>   Encoder1 pullup off/on")
        print_there(0, 5, "<2>   Encoder2 pullup off/on")
        print_there(0, 6, "<3>   Encoder3 pullup off/on")
        print_there(0, 7, "<4>   Encoder4 pullup off/on")
        print_there(0, 8, "<5>   Encoder1 1wire/2wires")
        print_there(0, 9, "<6>   Encoder2 1wire/2wires")
        print_there(0, 10, "<7>   Encoder3 1wire/2wires")
        print_there(0, 11, "<8>   Encoder4 1wire/2wires")
        print_there(0, 12, "<A>   Encoder1 rise/fall edge")
        print_there(0, 13, "<S>   Encoder2 rise/fall edge")
        print_there(0, 14, "<D>   Encoder3 rise/fall edge")
        print_there(0, 15, "<F>   Encoder4 rise/fall edge")
        print_there(0, 17, "<9/0> Timer interval")
        print_there(0, 18, "<N/M> Set async counter")
        print_there(0, 19, "<R>   Enter async mode")
        print_there(0, 20, "Read cycles remain")
        print_there(0, 22, "Encoder1 control")
        print_there(0, 23, "Encoder2 control")
        print_there(0, 24, "Encoder3 control")
        print_there(0, 25, "Encoder4 control")
        print_there(0, 26, "Encoder1 value")
        print_there(0, 27, "Encoder2 value")
        print_there(0, 28, "Encoder3 value")
        print_there(0, 29, "Encoder4 value")
        print_there(0, 31, "<C>   Redraw screen")
        print_there(0, 32, "<TAB> Change device group")
        print_there(0, 33, "<ESC> Exit/Quit")
    elif menu_page == sensor_menu:
        print_there(0, 1, "SENSORs MENU")
        print_there(0, 2, "Select menu item:")
        print_there(0, 4, "<1>    Sensor1  pullup    <J>    Sensor1 type    VALUE = ")
        print_there(0, 5, "<2>    Sensor2  pullup    <K>    Sensor2 type    VALUE = ")
        print_there(0, 6, "<3>    Sensor3  pullup    <L>    Sensor3 type    VALUE = ")
        print_there(0, 7, "<4>    Sensor4  pullup    <Z>    Sensor4 type    VALUE = ")
        print_there(0, 8, "<5>    Sensor5  pullup    <X>    Sensor5 type    VALUE = ")
        print_there(0, 9, "<6>    Sensor6  pullup    <V>    Sensor6 type    VALUE = ")
        print_there(0, 10, "<7>    Sensor7  pullup    <B>    Sensor7 type    VALUE = ")
        print_there(0, 11, "<8>    Sensor8  pullup    <Q>    Sensor8 type    VALUE = ")
        print_there(0, 12, "<A>    Sensor9  pullup    <W>    Sensor9 type    VALUE = ")
        print_there(0, 13, "<S>   Sensor10  pullup    <E>   Sensor10 type    VALUE = ")
        print_there(0, 14, "<D>   Sensor11  pullup    <T>   Sensor11 type    VALUE = ")
        print_there(0, 15, "<F>   Sensor12  pullup    <Y>   Sensor12 type    VALUE = ")
        print_there(0, 16, "<G>   Sensor13  pullup    <U>   Sensor13 type    VALUE = ")
        print_there(0, 17, "<H>   Sensor14  pullup    <I>   Sensor14 type    VALUE = ")
        print_there(0, 19, "Temperature sensor   VALUE = ")
        print_there(0, 20, "Motor current        VALUE = ")
        print_there(0, 21, "Motor voltage        VALUE = ")
        print_there(0, 22, "Battery voltage      VALUE = ")
        print_there(0, 24, "<9/0> Timer interval")
        print_there(0, 25, "<N/M> Set async counter")
        print_there(0, 26, "<R>   Enter async mode")
        print_there(0, 27, "Read cycles remain")
        print_there(0, 29, "<C>   Redraw screen")
        print_there(0, 30, "<TAB> Change device group")
        print_there(0, 31, "<ESC> Exit/Quit")
    elif menu_page == timer_menu:
        print_there(0, 1, "TIMER MENU")
        print_there(0, 2, "Select menu item:")
        print_there(0, 4, "<1/2> Set timer period")
        print_there(0, 5, "<3/4> Stop/start timer")
        print_there(0, 6, "<C>   Redraw screen")
        print_there(0, 7, "<TAB> Change device group")
        print_there(0, 8, "<ESC> Exit/Quit")
        print_there(0, 10, "Timer control")
        print_there(0, 11, "Timer counter")
    elif menu_page == touch_menu:
        print_there(0, 1, "TOUCH SCREEN MENU")
        print_there(0, 2, "Select menu item:")
        print_there(0, 4, "<1>   Enter calibration mode")
        print_there(0, 5, "<0>   Exit calibration mode")
        print_there(0, 6, "<C>   Redraw screen")
        print_there(0, 7, "<TAB> Change device group")
        print_there(0, 8, "<ESC> Exit/Quit")
        print_there(0, 10, "MIN X  = ")
        print_there(0, 11, "MAX X  = ")
        print_there(0, 12, "MIN Y  = ")
        print_there(0, 13, "MAX Y  = ")
        print_there(0, 14, "SCR X  = ")
        print_there(0, 15, "SCR Y  = ")
        print_there(0, 16, "POS X  = ")
        print_there(0, 17, "POS Y  = ")
    elif menu_page == bsl_menu:
        print_there(0, 1, "BSL MENU")
        print_there(0, 2, "Select menu item:")
        print_there(0, 4, "<1>   Set firmware file: ")
        print_there(0, 5, "<3>   Enter BSL mode")
        print_there(0, 6, "<5>   Write firmware")
        print_there(0, 7, "<0>   Hard reset")
        print_there(0, 8, "<C>   Redraw screen")
        print_there(0, 9, "<TAB> Change device group")
        print_there(0, 10, "<ESC> Exit/Quit")

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
    global sval1
    global sval2
    global sval3
    global sval4
    global sval5
    global sval6
    global sval7
    global sval8
    global sval9
    global sval10
    global sval11
    global sval12
    global sval13
    global sval14
    global sval15
    global sval16
    global sval17
    global sval18
    global sctl1
    global sctl2
    global sctl3
    global sctl4
    global sctl5
    global sctl6
    global sctl7
    global sctl8
    global sctl9
    global sctl10
    global sctl11
    global sctl12
    global sctl13
    global sctl14
    global sidx1
    global sidx2
    global sidx3
    global sidx4
    global sidx5
    global sidx6
    global sidx7
    global sidx8
    global sidx9
    global sidx10
    global sidx11
    global sidx12
    global sidx13
    global sidx14
    global spul1
    global spul2
    global spul3
    global spul4
    global spul5
    global spul6
    global spul7
    global spul8
    global spul9
    global spul10
    global spul11
    global spul12
    global spul13
    global spul14
    if menu_page == motor_menu:
        print_there(25, 4, "0x%02X " % motnum)
        print_there(25, 5, "%05u " % pwmper)
        print_there(25, 6, "%05u " % pwmdut)
        print_there(25, 11, "%010u " % motangle)
        print_there(25, 12, "%010u " % mottime)
        print_there(25, 18, "0x%04X " % motctl)
        print_there(25, 19, "%010u " % motfb)
        print_there(25, 20, "%010u " % encval)
        print_there(25, 21, "%010u " % moterr)
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
        print_there(30, 18, "%010u " % acnt)
        print_there(30, 20, "%010u " % cnti)
        print_there(30, 22, "0x%04X " % ectl1)
        print_there(30, 23, "0x%04X " % ectl2)
        print_there(30, 24, "0x%04X " % ectl3)
        print_there(30, 25, "0x%04X " % ectl4)
        print_there(30, 26, "%010u " % eval1)
        print_there(30, 27, "%010u " % eval2)
        print_there(30, 28, "%010u " % eval3)
        print_there(30, 29, "%010u " % eval4)
    elif menu_page == sensor_menu:
        print_there(23, 4, "%01u " % spul1)
        print_there(23, 5, "%01u " % spul2)
        print_there(23, 6, "%01u " % spul3)
        print_there(23, 7, "%01u " % spul4)
        print_there(23, 8, "%01u " % spul5)
        print_there(23, 9, "%01u " % spul6)
        print_there(23, 10, "%01u " % spul7)
        print_there(23, 11, "%01u " % spul8)
        print_there(23, 12, "%01u " % spul9)
        print_there(23, 13, "%01u " % spul10)
        print_there(23, 14, "%01u " % spul11)
        print_there(23, 15, "%01u " % spul12)
        print_there(23, 16, "%01u " % spul13)
        print_there(23, 17, "%01u " % spul14)
        print_there(46, 4, "%01u " % sidx1)
        print_there(46, 5, "%01u " % sidx2)
        print_there(46, 6, "%01u " % sidx3)
        print_there(46, 7, "%01u " % sidx4)
        print_there(46, 8, "%01u " % sidx5)
        print_there(46, 9, "%01u " % sidx6)
        print_there(46, 10, "%01u " % sidx7)
        print_there(46, 11, "%01u " % sidx8)
        print_there(46, 12, "%01u " % sidx9)
        print_there(46, 13, "%01u " % sidx10)
        print_there(46, 14, "%01u " % sidx11)
        print_there(46, 15, "%01u " % sidx12)
        print_there(46, 16, "%01u " % sidx13)
        print_there(46, 17, "%01u " % sidx14)
        print_there(57, 4, "%010u " % sval1)
        print_there(57, 5, "%010u " % sval2)
        print_there(57, 6, "%010u " % sval3)
        print_there(57, 7, "%010u " % sval4)
        print_there(57, 8, "%010u " % sval5)
        print_there(57, 9, "%010u " % sval6)
        print_there(57, 10, "%010u " % sval7)
        print_there(57, 11, "%010u " % sval8)
        print_there(57, 12, "%010u " % sval9)
        print_there(57, 13, "%010u " % sval10)
        print_there(57, 14, "%010u " % sval11)
        print_there(57, 15, "%010u " % sval12)
        print_there(57, 16, "%010u " % sval13)
        print_there(57, 17, "%010u " % sval14)
        print_there(29, 19, "%010u " % sval15)
        print_there(29, 20, "%010u " % sval16)
        print_there(29, 21, "%010u " % sval17)
        print_there(29, 22, "%010u " % sval18)

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
    global sval1
    global sval2
    global sval3
    global sval4
    global sval5
    global sval6
    global sval7
    global sval8
    global sval9
    global sval10
    global sval11
    global sval12
    global sval13
    global sval14
    global sval15
    global sval16
    global sval17
    global sval18
    global sctl1
    global sctl2
    global sctl3
    global sctl4
    global sctl5
    global sctl6
    global sctl7
    global sctl8
    global sctl9
    global sctl10
    global sctl11
    global sctl12
    global sctl13
    global sctl14
    global sidx1
    global sidx2
    global sidx3
    global sidx4
    global sidx5
    global sidx6
    global sidx7
    global sidx8
    global sidx9
    global sidx10
    global sidx11
    global sidx12
    global sidx13
    global sidx14
    global spul1
    global spul2
    global spul3
    global spul4
    global spul5
    global spul6
    global spul7
    global spul8
    global spul9
    global spul10
    global spul11
    global spul12
    global spul13
    global spul14
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
        if ectl1 & 0x2000:
            ewr1 = 1
        else:
            ewr1 = 0
        if ectl2 & 0x2000:
            ewr2 = 1
        else:
            ewr2 = 0
        if ectl3 & 0x2000:
            ewr3 = 1
        else:
            ewr3 = 0
        if ectl4 & 0x2000:
            ewr4 = 1
        else:
            ewr4 = 0
        if ectl1 & 0x1000:
            epul1 = 1
        else:
            epul1 = 0
        if ectl2 & 0x1000:
            epul2 = 1
        else:
            epul2 = 0
        if ectl3 & 0x1000:
            epul3 = 1
        else:
            epul3 = 0
        if ectl4 & 0x1000:
            epul4 = 1
        else:
            epul4 = 0
        if ectl1 & 0x0800:
            eedg1 = 1
        else:
            eedg1 = 0
        if ectl2 & 0x0800:
            eedg2 = 1
        else:
            eedg2 = 0
        if ectl3 & 0x0800:
            eedg3 = 1
        else:
            eedg3 = 0
        if ectl4 & 0x0800:
            eedg4 = 1
        else:
            eedg4 = 0
    elif menu_page == sensor_menu:
        sctl1, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_control(trik_sensor.sensor1))
        sctl2, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_control(trik_sensor.sensor2))
        sctl3, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_control(trik_sensor.sensor3))
        sctl4, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_control(trik_sensor.sensor4))
        sctl5, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_control(trik_sensor.sensor5))
        sctl6, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_control(trik_sensor.sensor6))
        sctl7, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_control(trik_sensor.sensor7))
        sctl8, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_control(trik_sensor.sensor8))
        sctl9, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_control(trik_sensor.sensor9))
        sctl10, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_control(trik_sensor.sensor10))
        sctl11, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_control(trik_sensor.sensor11))
        sctl12, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_control(trik_sensor.sensor12))
        sctl13, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_control(trik_sensor.sensor13))
        sctl14, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_control(trik_sensor.sensor14))
        sidx1, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_type(trik_sensor.sensor1))
        sidx2, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_type(trik_sensor.sensor2))
        sidx3, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_type(trik_sensor.sensor3))
        sidx4, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_type(trik_sensor.sensor4))
        sidx5, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_type(trik_sensor.sensor5))
        sidx6, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_type(trik_sensor.sensor6))
        sidx7, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_type(trik_sensor.sensor7))
        sidx8, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_type(trik_sensor.sensor8))
        sidx9, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_type(trik_sensor.sensor9))
        sidx10, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_type(trik_sensor.sensor10))
        sidx11, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_type(trik_sensor.sensor11))
        sidx12, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_type(trik_sensor.sensor12))
        sidx13, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_type(trik_sensor.sensor13))
        sidx14, daddr = trik_protocol.get_reg_value(trik_sensor.get_sensor_type(trik_sensor.sensor14))
        sval1, daddr = trik_protocol.get_reg_value(trik_sensor.read_sensor(trik_sensor.sensor1))
        sval2, daddr = trik_protocol.get_reg_value(trik_sensor.read_sensor(trik_sensor.sensor2))
        sval3, daddr = trik_protocol.get_reg_value(trik_sensor.read_sensor(trik_sensor.sensor3))
        sval4, daddr = trik_protocol.get_reg_value(trik_sensor.read_sensor(trik_sensor.sensor4))
        sval5, daddr = trik_protocol.get_reg_value(trik_sensor.read_sensor(trik_sensor.sensor5))
        sval6, daddr = trik_protocol.get_reg_value(trik_sensor.read_sensor(trik_sensor.sensor6))
        sval7, daddr = trik_protocol.get_reg_value(trik_sensor.read_sensor(trik_sensor.sensor7))
        sval8, daddr = trik_protocol.get_reg_value(trik_sensor.read_sensor(trik_sensor.sensor8))
        sval9, daddr = trik_protocol.get_reg_value(trik_sensor.read_sensor(trik_sensor.sensor9))
        sval10, daddr = trik_protocol.get_reg_value(trik_sensor.read_sensor(trik_sensor.sensor10))
        sval11, daddr = trik_protocol.get_reg_value(trik_sensor.read_sensor(trik_sensor.sensor11))
        sval12, daddr = trik_protocol.get_reg_value(trik_sensor.read_sensor(trik_sensor.sensor12))
        sval13, daddr = trik_protocol.get_reg_value(trik_sensor.read_sensor(trik_sensor.sensor13))
        sval14, daddr = trik_protocol.get_reg_value(trik_sensor.read_sensor(trik_sensor.sensor14))
        sval15, daddr = trik_protocol.get_reg_value(trik_sensor.read_sensor(trik_sensor.sensor15))
        sval16, daddr = trik_protocol.get_reg_value(trik_sensor.read_sensor(trik_sensor.sensor16))
        sval17, daddr = trik_protocol.get_reg_value(trik_sensor.read_sensor(trik_sensor.sensor17))
        sval18, daddr = trik_protocol.get_reg_value(trik_sensor.read_sensor(trik_sensor.sensor18))
        if sctl1 & trik_sensor.sens_pull:
            spul1 = 1
        else:
            spul1 = 0
        if sctl2 & trik_sensor.sens_pull:
            spul2 = 1
        else:
            spul2 = 0
        if sctl3 & trik_sensor.sens_pull:
            spul3 = 1
        else:
            spul3 = 0
        if sctl4 & trik_sensor.sens_pull:
            spul4 = 1
        else:
            spul4 = 0
        if sctl5 & trik_sensor.sens_pull:
            spul5 = 1
        else:
            spul5 = 0
        if sctl6 & trik_sensor.sens_pull:
            spul6 = 1
        else:
            spul6 = 0
        if sctl7 & trik_sensor.sens_pull:
            spul7 = 1
        else:
            spul7 = 0
        if sctl8 & trik_sensor.sens_pull:
            spul8 = 1
        else:
            spul8 = 0
        if sctl9 & trik_sensor.sens_pull:
            spul9 = 1
        else:
            spul9 = 0
        if sctl10 & trik_sensor.sens_pull:
            spul10 = 1
        else:
            spul10 = 0
        if sctl11 & trik_sensor.sens_pull:
            spul11 = 1
        else:
            spul11 = 0
        if sctl12 & trik_sensor.sens_pull:
            spul12 = 1
        else:
            spul12 = 0
        if sctl13 & trik_sensor.sens_pull:
            spul13 = 1
        else:
            spul13 = 0
        if sctl14 & trik_sensor.sens_pull:
            spul14 = 1
        else:
            spul14 = 0

# Read all registers
read_all_data(motor_menu)
read_all_data(encoder_menu)
read_all_data(sensor_menu)
read_all_data(timer_menu)
read_all_data(touch_menu)
read_all_data(bsl_menu)

# Init devices
trik_encoder.enable_encoder(trik_encoder.encoder1, ewr1, epul1, eedg1)
trik_encoder.enable_encoder(trik_encoder.encoder2, ewr2, epul2, eedg2)
trik_encoder.enable_encoder(trik_encoder.encoder3, ewr3, epul3, eedg3)
trik_encoder.enable_encoder(trik_encoder.encoder4, ewr4, epul4, eedg4)
trik_sensor.enable_sensor(trik_sensor.sensor1, spul1)
trik_sensor.enable_sensor(trik_sensor.sensor2, spul2)
trik_sensor.enable_sensor(trik_sensor.sensor3, spul3)
trik_sensor.enable_sensor(trik_sensor.sensor4, spul4)
trik_sensor.enable_sensor(trik_sensor.sensor5, spul5)
trik_sensor.enable_sensor(trik_sensor.sensor6, spul6)
trik_sensor.enable_sensor(trik_sensor.sensor7, spul7)
trik_sensor.enable_sensor(trik_sensor.sensor8, spul8)
trik_sensor.enable_sensor(trik_sensor.sensor9, spul9)
trik_sensor.enable_sensor(trik_sensor.sensor10, spul10)
trik_sensor.enable_sensor(trik_sensor.sensor11, spul11)
trik_sensor.enable_sensor(trik_sensor.sensor12, spul12)
trik_sensor.enable_sensor(trik_sensor.sensor13, spul13)
trik_sensor.enable_sensor(trik_sensor.sensor14, spul14)
trik_sensor.enable_sensor(trik_sensor.sensor15, 0x00)
trik_sensor.enable_sensor(trik_sensor.sensor16, 0x00)
trik_sensor.enable_sensor(trik_sensor.sensor17, 0x00)
trik_sensor.enable_sensor(trik_sensor.sensor18, 0x00)
trik_sensor.set_sensor_type(trik_sensor.sensor1, sidx1)
trik_sensor.set_sensor_type(trik_sensor.sensor2, sidx2)
trik_sensor.set_sensor_type(trik_sensor.sensor3, sidx3)
trik_sensor.set_sensor_type(trik_sensor.sensor4, sidx4)
trik_sensor.set_sensor_type(trik_sensor.sensor5, sidx5)
trik_sensor.set_sensor_type(trik_sensor.sensor6, sidx6)
trik_sensor.set_sensor_type(trik_sensor.sensor7, sidx7)
trik_sensor.set_sensor_type(trik_sensor.sensor8, sidx8)
trik_sensor.set_sensor_type(trik_sensor.sensor9, sidx9)
trik_sensor.set_sensor_type(trik_sensor.sensor10, sidx10)
trik_sensor.set_sensor_type(trik_sensor.sensor11, sidx11)
trik_sensor.set_sensor_type(trik_sensor.sensor12, sidx12)
trik_sensor.set_sensor_type(trik_sensor.sensor13, sidx13)
trik_sensor.set_sensor_type(trik_sensor.sensor14, sidx14)

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
            elif menu_pg == sensor_menu:
                if c == "1":
                    spul1 = 1 - spul1
                    trik_sensor.enable_sensor(trik_sensor.sensor1, spul1)
                if c == "2":
                    spul2 = 1 - spul2
                    trik_sensor.enable_sensor(trik_sensor.sensor2, spul2)
                if c == "3":
                    spul3 = 1 - spul3
                    trik_sensor.enable_sensor(trik_sensor.sensor3, spul3)
                if c == "4":
                    spul4 = 1 - spul4
                    trik_sensor.enable_sensor(trik_sensor.sensor4, spul4)
                if c == "5":
                    spul5 = 1 - spul5
                    trik_sensor.enable_sensor(trik_sensor.sensor5, spul5)
                if c == "6":
                    spul6 = 1 - spul6
                    trik_sensor.enable_sensor(trik_sensor.sensor6, spul6)
                if c == "7":
                    spul7 = 1 - spul7
                    trik_sensor.enable_sensor(trik_sensor.sensor7, spul7)
                if c == "8":
                    spul8 = 1 - spul8
                    trik_sensor.enable_sensor(trik_sensor.sensor8, spul8)
                if c.upper() == "A":
                    spul9 = 1 - spul9
                    trik_sensor.enable_sensor(trik_sensor.sensor9, spul9)
                if c.upper() == "S":
                    spul10 = 1 - spul10
                    trik_sensor.enable_sensor(trik_sensor.sensor10, spul10)
                if c.upper() == "D":
                    spul11 = 1 - spul11
                    trik_sensor.enable_sensor(trik_sensor.sensor11, spul11)
                if c.upper() == "F":
                    spul12 = 1 - spul12
                    trik_sensor.enable_sensor(trik_sensor.sensor12, spul12)
                if c.upper() == "G":
                    spul13 = 1 - spul13
                    trik_sensor.enable_sensor(trik_sensor.sensor13, spul13)
                if c.upper() == "H":
                    spul14 = 1 - spul14
                    trik_sensor.enable_sensor(trik_sensor.sensor14, spul14)
                if c.upper() == "J":
                    sidx1 = 1 - sidx1
                    trik_sensor.set_sensor_type(trik_sensor.sensor1, sidx1)
                if c.upper() == "K":
                    sidx2 = 1 - sidx2
                    trik_sensor.set_sensor_type(trik_sensor.sensor2, sidx2)
                if c.upper() == "L":
                    sidx3 = 1 - sidx3
                    trik_sensor.set_sensor_type(trik_sensor.sensor3, sidx3)
                if c.upper() == "Z":
                    sidx4 = 1 - sidx4
                    trik_sensor.set_sensor_type(trik_sensor.sensor4, sidx4)
                if c.upper() == "X":
                    sidx5 = 1 - sidx5
                    trik_sensor.set_sensor_type(trik_sensor.sensor5, sidx5)
                if c.upper() == "V":
                    sidx6 = 1 - sidx6
                    trik_sensor.set_sensor_type(trik_sensor.sensor6, sidx6)
                if c.upper() == "B":
                    sidx7 = 1 - sidx7
                    trik_sensor.set_sensor_type(trik_sensor.sensor7, sidx7)
                if c.upper() == "Q":
                    sidx8 = 1 - sidx8
                    trik_sensor.set_sensor_type(trik_sensor.sensor8, sidx8)
                if c.upper() == "W":
                    sidx9 = 1 - sidx9
                    trik_sensor.set_sensor_type(trik_sensor.sensor9, sidx9)
                if c.upper() == "E":
                    sidx10 = 1 - sidx10
                    trik_sensor.set_sensor_type(trik_sensor.sensor10, sidx10)
                if c.upper() == "T":
                    sidx11 = 1 - sidx11
                    trik_sensor.set_sensor_type(trik_sensor.sensor11, sidx11)
                if c.upper() == "Y":
                    sidx12 = 1 - sidx12
                    trik_sensor.set_sensor_type(trik_sensor.sensor12, sidx12)
                if c.upper() == "U":
                    sidx13 = 1 - sidx13
                    trik_sensor.set_sensor_type(trik_sensor.sensor13, sidx13)
                if c.upper() == "I":
                    sidx14 = 1 - sidx14
                    trik_sensor.set_sensor_type(trik_sensor.sensor14, sidx14)

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
