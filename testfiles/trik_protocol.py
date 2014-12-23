__author__ = 'Rostislav Varzar'

# Output devices
# fname1 = "000.txt"
fname1 = "/dev/ttyACM0"
fname2 = "/dev/ttyACM1"

# Function to recognize response packets
def get_reg_value(stmp):
    regval = 0x00000000
    devaddr = 0x00
    if len(stmp) == 18:
        devaddr = int(("0x" + stmp[1] + stmp[2]), 16)
        respcode = int(("0x" + stmp[3] + stmp[4]), 16)
        regaddr = int(("0x" + stmp[5] + stmp[6]), 16)
        regval = int(("0x" + stmp[7] + stmp[8] + stmp[9] + stmp[10] + stmp[11] + stmp[12] + stmp[13] + stmp[14]), 16)
        crc1 = int(("0x" + stmp[15] + stmp[16]), 16)
        crc2 = (0xFF - (devaddr + respcode + regaddr + (regval & 0xFF) + ((regval >> 8) & 0xFF) + ((regval >> 16) & 0xFF) + ((regval >> 24) & 0xFF)) + 1) & 0xFF
        if crc1 != crc2:
            errcode = 100
        else:
            errcode = 0
    else:
        errcode = 200
    return regval, devaddr, respcode, errcode

# Write single register
def write_reg(devaddr, regaddr, regval):
    f2 = open(fname1, "r")
    funcnum = 0x03
    crc = (0xFF - (devaddr + funcnum + regaddr + (regval & 0xFF) + ((regval >> 8) & 0xFF) + ((regval >> 16) & 0xFF) + ((regval >> 24) & 0xFF)) + 1) & 0xFF
    stmp = ":%02X%02X%02X%08X%02X\n" % (devaddr, funcnum, regaddr, regval, crc)
    f1 = open(fname1, "wb")
    f1.write(stmp)
    f1.close()
    stmp = f2.readline()
    f2.close()
    return stmp

# Read single register
def read_reg(devaddr, regaddr):
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

# Read single register from async port
# Use this function only when async mode is active!!!!!
def read_async_reg():
    f2 = open(fname2, "r")
    stmp = f2.readline()
    f2.close()
    return stmp

