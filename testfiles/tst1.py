# Output device
fname1 = "000.txt"
# fname1 = "/dev/ttyACM0"

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


write_32bit_reg(0x00,0x04,0x03,0x8662)



