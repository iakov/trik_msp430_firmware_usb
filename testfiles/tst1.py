def write_16bit_reg(devaddr, funcnum, regaddr, regval):
    crc = 0xFF - (devaddr + funcnum + regaddr + (regval & 0xFF) + ((regval >> 8) & 0xFF)) + 1
    stmp = ":%02X%02X%02X%04X%02X\n" % (devaddr, funcnum, regaddr, regval, crc)
    print(stmp)

write_16bit_reg(0x2E,0x03,0x01,0x0064)



