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

