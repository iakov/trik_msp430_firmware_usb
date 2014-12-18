__author__ = 'Rostislav Varzar'

import os
import trik_protocol

# Init Serial TTY device
def init_stty():
    sty1 = "stty -F %s -echo -onlcr" % (trik_protocol.fname1)
    os.system(sty1)
