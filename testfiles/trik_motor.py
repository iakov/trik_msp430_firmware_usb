__author__ = 'Rostislav Varzar'

import trik_protocol

# Motor addresses
motor1 = 0x00
motor2 = 0x01
motor3 = 0x02
motor4 = 0x03

# Motor registers
mctl = 0x00
mdut = 0x01
mper = 0x02
mang = 0x03
mtmr = 0x04
mval = 0x05
merr = 0x06

# Set PWM period for motor
def set_motor_period(motnum, pwmper):
    trik_protocol.write_16bit_reg(motnum, mper, pwmper)

# Set PWM duty for motor
def set_motor_duty(motnum, pwmdut):
    trik_protocol.write_16bit_reg(motnum, mdut, pwmdut)
