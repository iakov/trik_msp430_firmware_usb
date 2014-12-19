__author__ = 'Rostislav Varzar'

import trik_protocol

# Encoder addresses
encoder1 = 0x16
encoder2 = 0x17
encoder3 = 0x18
encoder4 = 0x19

# Encoder registers
ectl = 0x00
eval = 0x01

# ECTL bits
enc_enable = 0x8000
enc_async = 0x4000
enc_2wires = 0x2000
enc_pupen = 0x1000
enc_fall = 0x0800

# Enable encoder
def enable_encoder(encnum, numwires, pullup, edge):
    encctl = enc_enable
    if numwires:
        encctl = encctl + enc_2wires
    if pullup:
        encctl = encctl + enc_pupen
    if edge:
        encctl = encctl + enc_fall
    trik_protocol.write_16bit_reg(encnum, ectl, encctl)

# Read encoder value
def read_encoder(encnum):
    return trik_protocol.read_32bit_reg(encnum, eval)

