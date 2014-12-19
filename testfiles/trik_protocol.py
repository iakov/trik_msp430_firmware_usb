__author__ = 'Rostislav Varzar'

# Output devices
# fname1 = "000.txt"
fname1 = "/dev/ttyACM0"
fname2 = "/dev/ttyACM1"

# Function to recognize response packets
def get_reg_value(stmp):
    devaddr = 0x00
    if len(stmp) == 8:
        devaddr = int(("0x" + stmp[1] + stmp[2]), 16)
        respcode = int(("0x" + stmp[3] + stmp[4]), 16)
        crc1 = int(("0x" + stmp[5] + stmp[6]), 16)
        crc2 = (0xFF - (devaddr + respcode) + 1) & 0xFF
        if crc1 != crc2:
            rval = -1
        else:
            rval = respcode
    elif len(stmp) == 14:
        devaddr = int(("0x" + stmp[1] + stmp[2]), 16)
        respcode = int(("0x" + stmp[3] + stmp[4]), 16)
        regaddr = int(("0x" + stmp[5] + stmp[6]), 16)
        regval = int(("0x" + stmp[7] + stmp[8] + stmp[9] + stmp[10]), 16)
        crc1 = int(("0x" + stmp[11] + stmp[12]), 16)
        crc2 = (0xFF - (devaddr + respcode + regaddr + (regval & 0xFF) + ((regval >> 8) & 0xFF)) + 1) & 0xFF
        if crc1 != crc2:
            rval = -2
        else:
            rval = regval
    elif len(stmp) == 18:
        devaddr = int(("0x" + stmp[1] + stmp[2]), 16)
        respcode = int(("0x" + stmp[3] + stmp[4]), 16)
        regaddr = int(("0x" + stmp[5] + stmp[6]), 16)
        regval = int(("0x" + stmp[7] + stmp[8] + stmp[9] + stmp[10] + stmp[11] + stmp[12] + stmp[13] + stmp[14]), 16)
        crc1 = int(("0x" + stmp[15] + stmp[16]), 16)
        crc2 = (0xFF - (devaddr + respcode + regaddr + (regval & 0xFF) + ((regval >> 8) & 0xFF) + ((regval >> 16) & 0xFF) + ((regval >> 24) & 0xFF)) + 1) & 0xFF
        if crc1 != crc2:
            rval = -3
        else:
            rval = regval
    elif len(stmp) == 10:
        devaddr = int(("0x" + stmp[1] + stmp[2]), 16)
        funccode = int(("0x" + stmp[3] + stmp[4]), 16)
        errcode = int(("0x" + stmp[5] + stmp[6]), 16)
        crc1 = int(("0x" + stmp[7] + stmp[8]), 16)
        crc2 = (0xFF - (devaddr + funccode + errcode) + 1) & 0xFF
        if crc1 != crc2:
            rval = -4
        else:
            rval = errcode
    else:
        rval = -5
    return rval, devaddr

# Write single 16bit register
def write_16bit_reg(devaddr, regaddr, regval):
    f2 = open(fname1, "r")
    funcnum = 0x03
    crc = (0xFF - (devaddr + funcnum + regaddr + (regval & 0xFF) + ((regval >> 8) & 0xFF)) + 1) & 0xFF
    stmp = ":%02X%02X%02X%04X%02X\n" % (devaddr, funcnum, regaddr, regval, crc)
    f1 = open(fname1, "wb")
    f1.write(stmp)
    f1.close()
    stmp = f2.readline()
    f2.close()
    return stmp

# Write single 32bit register
def write_32bit_reg(devaddr, regaddr, regval):
    f2 = open(fname1, "r")
    funcnum = 0x04
    crc = (0xFF - (devaddr + funcnum + regaddr + (regval & 0xFF) + ((regval >> 8) & 0xFF) + ((regval >> 16) & 0xFF) + ((regval >> 24) & 0xFF)) + 1) & 0xFF
    stmp = ":%02X%02X%02X%08X%02X\n" % (devaddr, funcnum, regaddr, regval, crc)
    f1 = open(fname1, "wb")
    f1.write(stmp)
    f1.close()
    stmp = f2.readline()
    f2.close()
    return stmp

# Read single 16 bit register
def read_16bit_reg(devaddr, regaddr):
    f2 = open(fname1, "r")
    funcnum = 0x05
    crc = (0xFF - (devaddr + funcnum + regaddr) + 1) & 0xFF
    stmp = ":%02X%02X%02X%02X\n" % (devaddr, funcnum, regaddr, crc)
    f1 = open(fname1, "wb")
    f1.write(stmp)
    f1.close()
    stmp = f2.readline()
    f2.close()
    return stmp

# Read single 32 bit register
def read_32bit_reg(devaddr, regaddr):
    f2 = open(fname1, "r")
    funcnum = 0x06
    crc = (0xFF - (devaddr + funcnum + regaddr) + 1) & 0xFF
    stmp = ":%02X%02X%02X%02X\n" % (devaddr, funcnum, regaddr, crc)
    f1 = open(fname1, "wb")
    f1.write(stmp)
    f1.close()
    stmp = f2.readline()
    f2.close()
    return stmp

# Read single register from async port
# Use this function only when async mode is active!!!!!
def read_async_reg():
    f2 = open(fname2, "r")
    stmp = f2.readline()
    f2.close()
    return stmp

