/*
 * trik_sensctrl.c
 *
 *  Created on: Fabruary 11, 2015
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include <msp430f5510.h>
#include "trik_devices.h"
#include "trik_sensctrl.h"

void SPCTL_handler()
{
    //Enable / disable
    if (SPCTL & SPCTL_ENABLE)
        ;//PWM_enable(PWM_NUMBER);
    else
        ;//PWM_disable(PWM_NUMBER);

    SPSTA = SPCTL_NO_ERROR;
}

