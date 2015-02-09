/*
 * Trik_ProtocolHandler.c
 *
 *  Created on: October 21, 2014
 *      Author: Rostislav Varzar
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <msp430f5510.h>
#include <stdint.h>
#include "Trik_Devices/trik_protocolhandler.h"
#include "Trik_Devices/trik_motor.h"
#include "Trik_Devices/trik_sensor.h"
#include "Trik_Devices/trik_encoder.h"
#include "Trik_Devices/trik_bsl.h"
#include "Trik_Devices/trik_devices.h"
#include "Trik_Devices/trik_async.h"
#include "Trik_Devices/trik_touch.h"
#include "Trik_Devices/trik_pwm.h"
#include "Trik_Devices/trik_port.h"
#include "Trik_Devices/trik_softi2c.h"

uint8_t TO_HEX(uint8_t i)
{
    return (i <= 9 ? '0' + i : 'A' - 10 + i);
}

void char2hex(char *string, uint8_t number)
{
    string[0] = TO_HEX((number & 0x00F0) >> 4);
    string[1] = TO_HEX(number & 0x000F);
    string[2] = '\0';
}

uint32_t hex2num(char *string, uint16_t pos, uint16_t numsize)
{
    uint32_t resnum = 0;
    uint32_t tmpnum = 0;
    char c = 0;
    for (uint16_t i = 0; i < numsize; i++)
    {
        c = toupper(string[pos+i]);
        tmpnum = c > '9' ? c - 'A' + 10 : c - '0';
        resnum |= (tmpnum << ((numsize - i - 1) * 4));
    }
    return resnum;
}

//Read register response
void PROTOCOL_recvResponse(char *r_str, uint8_t dev_addr, uint8_t resp_code, uint8_t reg_addr, uint32_t reg_val)
{
    char stmp1[MAX_STRING_LENGTH]; //Temp string
    uint8_t t11,t12,t13,t14; //Temp vars
    uint8_t crc; //Checksum

    t11 = (uint8_t)((reg_val & 0xFF000000) >> 24);
    t12 = (uint8_t)((reg_val & 0x00FF0000) >> 16);
    t13 = (uint8_t)((reg_val & 0x0000FF00) >> 8);
    t14 = (uint8_t)(reg_val & 0x000000FF);

    r_str[0] = ':';
    r_str[1] = '\0';

    char2hex(stmp1,dev_addr);
    strcat(r_str,stmp1);

    char2hex(stmp1,resp_code);
    strcat(r_str,stmp1);

    char2hex(stmp1,reg_addr);
    strcat(r_str,stmp1);

    char2hex(stmp1,t11);
    strcat(r_str,stmp1);
    char2hex(stmp1,t12);
    strcat(r_str,stmp1);
    char2hex(stmp1,t13);
    strcat(r_str,stmp1);
    char2hex(stmp1,t14);
    strcat(r_str,stmp1);

    crc = 0 - (dev_addr + resp_code + reg_addr + t11 + t12 + t13 + t14);
    char2hex(stmp1,crc);
    strcat(r_str,stmp1);

    strcat(r_str,"\n\0");
}

/*
 * ======== retInString ========
 */
// This function returns true if there's an 0x0D character in the string; and if
// so, it trims the 0x0D and anything that had followed it.
uint8_t retInString (char* string)
{
    uint8_t retPos = 0,i,len;
    char tempStr[MAX_STRING_LENGTH] = "";

    strncpy(tempStr,string,strlen(string));  // Make a copy of the string
    len = strlen(tempStr);

    // Find 0x0D; if not found, retPos ends up at len
    while ((tempStr[retPos] != 0x0A) && (tempStr[retPos] != 0x0D) &&
           (retPos++ < len)) ;

    // If 0x0A was actually found...
    if ((retPos < len) && (tempStr[retPos] == 0x0A)){

        // Empty the buffer
        for (i = 0; i < MAX_STRING_LENGTH; i++){
            string[i] = 0x00;
        }

        //...trim the input string to just before 0x0D
        strncpy(string,tempStr,retPos);

        //...and tell the calling function that we did so
        return (True) ;

    } else if (tempStr[retPos] == 0x0A) {

        // Empty the buffer
        for (i = 0; i < MAX_STRING_LENGTH; i++){
            string[i] = 0x00;
        }

        //...trim the input string to just before 0x0D
        strncpy(string,tempStr,retPos);

        //...and tell the calling function that we did so
        return (True) ;
    } else if (retPos < len){
        // Empty the buffer
        for (i = 0; i < MAX_STRING_LENGTH; i++){
            string[i] = 0x00;
        }

        //...trim the input string to just before 0x0D
        strncpy(string,tempStr,retPos);

        //...and tell the calling function that we did so
        return (True) ;
    }

    return (False) ; // Otherwise, it wasn't found
}

//Protocol handler
uint8_t PROTOCOL_handler(char *in_str, char *out_str)
{
	uint8_t devaddr1 = 0; //Device address
	uint8_t func1 = 0; //Function number
	uint8_t regaddr1 = 0; //Register address
	uint32_t regval1 = 0; //Register value
	uint8_t crc1 = 0; //Cheksum
	uint8_t crc2 = 0; //Calculated checksum

	//Start condition error
	if (in_str[0]!=':')
	{
        PROTOCOL_recvResponse(out_str,0x00,0x80,0x00,START_ERROR);
		return START_ERROR;
	}

	//Incorrect packet length
	if ((strlen(in_str)!=9) && (strlen(in_str)!=17))
	{
		PROTOCOL_recvResponse(out_str,0x00,0x80,0x00,LENGTH_ERROR);
		return LENGTH_ERROR;
	}

	//Get device address
	devaddr1 = hex2num(in_str, 1, NUM_BYTE);

	//Get function
	func1 = hex2num(in_str, 3, NUM_BYTE);

	//Get register address
	regaddr1 = hex2num(in_str, 5, NUM_BYTE);

	//Get register value
    regval1 = hex2num(in_str, 7, NUM_DWORD);

    //Mutation #1
    if ((devaddr1==ENCODER3) && ((regaddr1==0x37) || (regaddr1==0xA4)))
    {
        PROTOCOL_recvResponse(out_str,devaddr1,func1+0x80,regaddr1,0x55);
        return 0x55;
    }

    //Mutation #2
    if ((devaddr1==MOTOR1) && ((regaddr1==0x25) || (regaddr1==0xEF)))
    {
        PROTOCOL_recvResponse(out_str,devaddr1,func1+0x80,regaddr1,0xAA);
        return 0xAA;
    }

    //Mutation #3
    if (((regaddr1==0x35) || (regaddr1==0x45)) && ((regval1==0x0FFFFFF) || (regval1==0x8000000)))
    {
        PROTOCOL_recvResponse(out_str,devaddr1,func1+0x80,regaddr1,0x33);
        return 0x33;
    }

    //Device addresses range
	if ((devaddr1>MAX_DEVICES) && (devaddr1!=BSL))
	{
	    PROTOCOL_recvResponse(out_str,devaddr1,func1+0x80,regaddr1,DEV_ADDR_ERROR);
		return DEV_ADDR_ERROR;
	}

	//Motor registers addresses range
	//if (((devaddr1>=MOTOR1) && (devaddr1<=MOTOR4)) && (regaddr1>0x06))
	if (((devaddr1<=MOTOR4)) && (regaddr1>0x06))
	{
	    PROTOCOL_recvResponse(out_str,devaddr1,func1+0x80,regaddr1,REG_ADDR_ERROR);
		return REG_ADDR_ERROR;
	}

	//Sensor registers addresses range
	if (((devaddr1>=SENSOR1) && (devaddr1<=SENSOR18)) && (regaddr1>0x02))
	{
	    PROTOCOL_recvResponse(out_str,devaddr1,func1+0x80,regaddr1,REG_ADDR_ERROR);
		return REG_ADDR_ERROR;
	}

	//Encoder registers addresses range
	if (((devaddr1>=ENCODER1) && (devaddr1<=ENCODER4)) && (regaddr1>0x01))
	{
	    PROTOCOL_recvResponse(out_str,devaddr1,func1+0x80,regaddr1,REG_ADDR_ERROR);
	    return REG_ADDR_ERROR;
	}

    //Port registers addresses range
    if (((devaddr1>=PORT1) && (devaddr1<=PORTJ)) && (regaddr1>0x08))
    {
        PROTOCOL_recvResponse(out_str,devaddr1,func1+0x80,regaddr1,REG_ADDR_ERROR);
        return REG_ADDR_ERROR;
    }

    //PWM registers addresses range
    if (((devaddr1>=PWM1) && (devaddr1<=PWM5)) && (regaddr1>0x02))
    {
        PROTOCOL_recvResponse(out_str,devaddr1,func1+0x80,regaddr1,REG_ADDR_ERROR);
        return REG_ADDR_ERROR;
    }

    //I2C registers addresses range
    if (((devaddr1>=I2C1) && (devaddr1<=I2C7)) && (regaddr1>0x07))
    {
        PROTOCOL_recvResponse(out_str,devaddr1,func1+0x80,regaddr1,REG_ADDR_ERROR);
        return REG_ADDR_ERROR;
    }

    //Timer registers addresses range
    if ((devaddr1==ASYNCTIMER) && (regaddr1>0x02))
    {
        PROTOCOL_recvResponse(out_str,devaddr1,func1+0x80,regaddr1,REG_ADDR_ERROR);
        return REG_ADDR_ERROR;
    }

    //Touch controller registers addresses range
    if ((devaddr1==TOUCHDEVICE) && (regaddr1>0x08))
    {
        PROTOCOL_recvResponse(out_str,devaddr1,func1+0x80,regaddr1,REG_ADDR_ERROR);
        return REG_ADDR_ERROR;
    }

	//Function number check
	if ((func1!=FUNCx03) && (func1!=FUNCx05))
	{
	    PROTOCOL_recvResponse(out_str,devaddr1,func1+0x80,regaddr1,FUNC_CODE_ERROR);
		return FUNC_CODE_ERROR;
	}

	//CRC check
	switch (func1)
	{
        case FUNCx03:
            crc1 = hex2num(in_str, 15, NUM_BYTE);
            break;
        case FUNCx05:
            crc1 = hex2num(in_str, 7, NUM_BYTE);
            break;
        default:
            break;
	}

    //Mutation #4
    if ((crc1>20) && (crc1<100) && (regaddr1==0x30))
    {
        PROTOCOL_recvResponse(out_str,devaddr1,func1+0x80,regaddr1,0xCC);
        return 0xCC;
    }

	if ((func1==FUNCx03))
	    crc2=0-(devaddr1+func1+regaddr1+
	            (uint8_t)(regval1 & 0x000000FF)+(uint8_t)((regval1 & 0x0000FF00) >> 8)+
	            (uint8_t)((regval1 & 0x00FF0000) >> 16)+(uint8_t)((regval1 & 0xFF000000) >> 24));
	if ((func1==FUNCx05))
	    crc2=0-(devaddr1+func1+regaddr1);
	if (crc1!=crc2)
	{
	    PROTOCOL_recvResponse(out_str,devaddr1,func1+0x80,regaddr1,CRC_ERROR);
	    return CRC_ERROR;
	}

	//Hadle of function 0x03 - write single register
	if ((func1==FUNCx03) && (strlen(in_str)==17))
	{
	    //Motors
	    //if ((devaddr1>=MOTOR1) && (devaddr1<=MOTOR4))
	    if ((devaddr1<=MOTOR4))
	    {
	        if (regaddr1==MMDUT)
	            MOT[devaddr1].MDUT = regval1;
	        if (regaddr1==MMPER)
	            MOT[devaddr1].MPER = regval1;
	        if (regaddr1==MMANG)
	            MOT[devaddr1].MANG = regval1;
	        if (regaddr1==MMTMR)
	            MOT[devaddr1].MTMR = regval1;
	        if (regaddr1==MMVAL)
	            MOT[devaddr1].MVAL = regval1;
            if (regaddr1==MMERR)
                MOT[devaddr1].MERR = regval1;
	        if (regaddr1==MMCTL)
	            MOT[devaddr1].MCTL = regval1;
            //Error register values
            if ((MOT[devaddr1].MPER==0) || (MOT[devaddr1].MDUT>MOT[devaddr1].MPER))
            {
                PROTOCOL_recvResponse(out_str,devaddr1,func1+0x80,regaddr1,REG_INC_ERROR);
                return REG_INC_ERROR;
            }
            MOTOR_handler(devaddr1);
            PROTOCOL_recvResponse(out_str,devaddr1,func1,regaddr1,MOT[devaddr1].MSTA);
            return NO_ERROR;
	    }

	    //Encoders
        if ((devaddr1>=ENCODER1) && (devaddr1<=ENCODER4))
        {
            if (regaddr1==EEVAL)
                ENC[devaddr1-ENCODER1].EVAL = regval1;
            if (regaddr1==EECTL)
            {
                ENC[devaddr1-ENCODER1].ECTL = regval1;
                ENCODER_handler(devaddr1);
            }
            PROTOCOL_recvResponse(out_str,devaddr1,func1,regaddr1,ENC[devaddr1-ENCODER1].ESTA);
            return NO_ERROR;
        }

        //Sensors
        if ((devaddr1>=SENSOR1) && (devaddr1<=SENSOR18))
        {
            if (regaddr1==SSIDX)
                SENS[devaddr1-SENSOR1].SIDX = regval1;
            if (regaddr1==SSCTL)
            {
                SENS[devaddr1-SENSOR1].SCTL = regval1;
                SENSOR_handler(devaddr1);
            }
            PROTOCOL_recvResponse(out_str,devaddr1,func1,regaddr1,SENS[devaddr1-SENSOR1].SSTA);
            return NO_ERROR;
        }

        //Ports
        if ((devaddr1>=PORT1) && (devaddr1<=PORTJ))
        {
            PORT_write(devaddr1, regaddr1, regval1);
            PROTOCOL_recvResponse(out_str,devaddr1,func1,regaddr1,NO_ERROR);
            return NO_ERROR;
        }

        //PWMs
        if ((devaddr1>=PWM1) && (devaddr1<=PWM5))
        {
            if (regaddr1==PPDUT)
                PWM[devaddr1-PWM1].PDUT = regval1;
            if (regaddr1==PPPER)
                PWM[devaddr1-PWM1].PPER = regval1;
            if (regaddr1==PPCTL)
            {
                PWM[devaddr1-PWM1].PCTL = regval1;
                PWM_handler(devaddr1);
            }
            PROTOCOL_recvResponse(out_str,devaddr1,func1,regaddr1,NO_ERROR);
            return NO_ERROR;
        }

        //I2Cs
        if ((devaddr1>=I2C1) && (devaddr1<=I2C7))
        {
            if (regaddr1==IIDEV)
                I2C[devaddr1-I2C1].IDEV = regval1;
            if (regaddr1==IIREG)
                I2C[devaddr1-I2C1].IREG = regval1;
            if (regaddr1==IIDAT)
                I2C[devaddr1-I2C1].IDAT = regval1;
            if (regaddr1==IIERR)
                I2C[devaddr1-I2C1].IERR = regval1;
            if (regaddr1==IIIDX)
                I2C[devaddr1-I2C1].IIDX = regval1;
            if (regaddr1==IIVAL)
                I2C[devaddr1-I2C1].IVAL = regval1;
            if (regaddr1==IIDEL)
                Idelay = regval1;
            if (regaddr1==IICTL)
            {
                I2C[devaddr1-I2C1].ICTL = regval1;
                I2C_handler(devaddr1);
            }
            PROTOCOL_recvResponse(out_str,devaddr1,func1,regaddr1,NO_ERROR);
            return NO_ERROR;
        }

        //Async timer
        if ((devaddr1==ASYNCTIMER))
        {
            if (regaddr1==AATPER)
                ASYNCTMR.ATPER = regval1 + MAX_DEVICES;
            if (regaddr1==AATVAL)
                ASYNCTMR.ATVAL = regval1;
            if (regaddr1==AATCTL)
            {
                ASYNCTMR.ATCTL=regval1;
                ASYNCTIMER_handler();
            }
            PROTOCOL_recvResponse(out_str,devaddr1,func1,regaddr1,NO_ERROR);
            return NO_ERROR;
        }

        //Touch controller
        if ((devaddr1==TOUCHDEVICE))
        {
            if (regaddr1==TTMOD)
            {
                TOUCH.TMOD = regval1;
                if (regval1) resetTouch();
            }
            if (regaddr1==TMINX)
                TOUCH.MINX = regval1;
            if (regaddr1==TMAXX)
                TOUCH.MAXX = regval1;
            if (regaddr1==TMINY)
                TOUCH.MINY = regval1;
            if (regaddr1==TMAXY)
                TOUCH.MAXY = regval1;
            if (regaddr1==TSCRX)
                TOUCH.SCRX = regval1;
            if (regaddr1==TSCRY)
                TOUCH.SCRY = regval1;
            if (regaddr1==TCURX)
                TOUCH.CURX = regval1;
            if (regaddr1==TCURY)
                TOUCH.CURY = regval1;
            PROTOCOL_recvResponse(out_str,devaddr1,func1,regaddr1,NO_ERROR);
            return NO_ERROR;
        }

	    //BSL
	    if ((devaddr1==BSL) && (regaddr1==0x00))
	    {
	        PROTOCOL_recvResponse(out_str,devaddr1,func1,regaddr1,BSL_enterBSL(regval1));
	        return NO_ERROR;
	    }

	    //If not found any devices
	    PROTOCOL_recvResponse(out_str,devaddr1,func1+0x80,regaddr1,DEV_ADDR_ERROR);
	    return DEV_ADDR_ERROR;
	}

	//Function 0x05 - read single register
    if ((func1==FUNCx05) && (strlen(in_str)==9))
    {

        //Motors
        //if ((devaddr1>=MOTOR1) && (devaddr1<=MOTOR4))
        if ((devaddr1<=MOTOR4))
        {
            if (regaddr1==MMCTL)
                PROTOCOL_recvResponse(out_str,devaddr1,MOT[devaddr1].MSTA,regaddr1,MOT[devaddr1].MCTL);
            if (regaddr1==MMDUT)
                PROTOCOL_recvResponse(out_str,devaddr1,MOT[devaddr1].MSTA,regaddr1,MOT[devaddr1].MDUT);
            if (regaddr1==MMPER)
                PROTOCOL_recvResponse(out_str,devaddr1,MOT[devaddr1].MSTA,regaddr1,MOT[devaddr1].MPER);
            if (regaddr1==MMANG)
                PROTOCOL_recvResponse(out_str,devaddr1,MOT[devaddr1].MSTA,regaddr1,MOT[devaddr1].MANG);
            if (regaddr1==MMTMR)
                PROTOCOL_recvResponse(out_str,devaddr1,MOT[devaddr1].MSTA,regaddr1,MOT[devaddr1].MTMR);
            if (regaddr1==MMVAL)
                PROTOCOL_recvResponse(out_str,devaddr1,MOT[devaddr1].MSTA,regaddr1,MOT[devaddr1].MVAL);
            if (regaddr1==MMERR)
                PROTOCOL_recvResponse(out_str,devaddr1,MOT[devaddr1].MSTA,regaddr1,MOT[devaddr1].MERR);
            return NO_ERROR;
        }

        //Encoders
        if ((devaddr1>=ENCODER1) && (devaddr1<=ENCODER4))
        {
            if (regaddr1==EECTL)
                PROTOCOL_recvResponse(out_str,devaddr1,ENC[devaddr1-ENCODER1].ESTA,regaddr1,ENC[devaddr1-ENCODER1].ECTL);
            if (regaddr1==EEVAL)
                PROTOCOL_recvResponse(out_str,devaddr1,ENC[devaddr1-ENCODER1].ESTA,regaddr1,ENC[devaddr1-ENCODER1].EVAL);
            return NO_ERROR;
        }

        //Sensors
        if ((devaddr1>=SENSOR1) && (devaddr1<=SENSOR18))
        {
            SENSOR_handler(devaddr1);
            if (regaddr1==SSCTL)
                PROTOCOL_recvResponse(out_str,devaddr1,SENS[devaddr1-SENSOR1].SSTA,regaddr1,SENS[devaddr1-SENSOR1].SCTL);
            if (regaddr1==SSIDX)
                PROTOCOL_recvResponse(out_str,devaddr1,SENS[devaddr1-SENSOR1].SSTA,regaddr1,SENS[devaddr1-SENSOR1].SIDX);
            if (regaddr1==SSVAL)
                PROTOCOL_recvResponse(out_str,devaddr1,SENS[devaddr1-SENSOR1].SSTA,regaddr1,SENS[devaddr1-SENSOR1].SVAL);
            return NO_ERROR;
        }

        //PWMs
        if ((devaddr1>=PWM1) && (devaddr1<=PWM5))
        {
            if (regaddr1==PPCTL)
                PROTOCOL_recvResponse(out_str,devaddr1,PWM[devaddr1-PWM1].PSTA,regaddr1,PWM[devaddr1-PWM1].PCTL);
            if (regaddr1==PPDUT)
                PROTOCOL_recvResponse(out_str,devaddr1,PWM[devaddr1-PWM1].PSTA,regaddr1,PWM[devaddr1-PWM1].PDUT);
            if (regaddr1==PPPER)
                PROTOCOL_recvResponse(out_str,devaddr1,PWM[devaddr1-PWM1].PSTA,regaddr1,PWM[devaddr1-PWM1].PPER);
            return NO_ERROR;
        }

        //I2Cs
        if ((devaddr1>=I2C1) && (devaddr1<=I2C7))
        {
            I2C_handler(devaddr1);
            if (regaddr1==IICTL)
                PROTOCOL_recvResponse(out_str,devaddr1,I2C[devaddr1-I2C1].ISTA,regaddr1,I2C[devaddr1-I2C1].ICTL);
            if (regaddr1==IIDEV)
                PROTOCOL_recvResponse(out_str,devaddr1,I2C[devaddr1-I2C1].ISTA,regaddr1,I2C[devaddr1-I2C1].IDEV);
            if (regaddr1==IIREG)
                PROTOCOL_recvResponse(out_str,devaddr1,I2C[devaddr1-I2C1].ISTA,regaddr1,I2C[devaddr1-I2C1].IREG);
            if (regaddr1==IIDAT)
                PROTOCOL_recvResponse(out_str,devaddr1,I2C[devaddr1-I2C1].ISTA,regaddr1,I2C[devaddr1-I2C1].IDAT);
            if (regaddr1==IIERR)
                PROTOCOL_recvResponse(out_str,devaddr1,I2C[devaddr1-I2C1].ISTA,regaddr1,I2C[devaddr1-I2C1].IERR);
            if (regaddr1==IIIDX)
                PROTOCOL_recvResponse(out_str,devaddr1,I2C[devaddr1-I2C1].ISTA,regaddr1,I2C[devaddr1-I2C1].IIDX);
            if (regaddr1==IIVAL)
                PROTOCOL_recvResponse(out_str,devaddr1,I2C[devaddr1-I2C1].ISTA,regaddr1,I2C[devaddr1-I2C1].IVAL);
            if (regaddr1==IIDEL)
                PROTOCOL_recvResponse(out_str,devaddr1,I2C[devaddr1-I2C1].ISTA,regaddr1,Idelay);
            return NO_ERROR;
        }

        //Ports
        if ((devaddr1>=PORT1) && (devaddr1<=PORTJ))
        {
            PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,
                    PORT_read(devaddr1,regaddr1));
            return NO_ERROR;
        }

        //Async timer
        if ((devaddr1==ASYNCTIMER))
        {
            if (regaddr1==AATCTL)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,ASYNCTMR.ATCTL);
            if (regaddr1==AATPER)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,ASYNCTMR.ATPER);
            if (regaddr1==AATVAL)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,ASYNCTMR.ATVAL);
            return NO_ERROR;
        }

        //Touch controller
        if ((devaddr1==TOUCHDEVICE))
        {
            if (regaddr1==TTMOD)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,TOUCH.TMOD);
            if (regaddr1==TMINX)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,TOUCH.MINX);
            if (regaddr1==TMAXX)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,TOUCH.MAXX);
            if (regaddr1==TMINY)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,TOUCH.MINY);
            if (regaddr1==TMAXY)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,TOUCH.MAXY);
            if (regaddr1==TSCRX)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,TOUCH.SCRX);
            if (regaddr1==TSCRY)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,TOUCH.SCRY);
            if (regaddr1==TCURX)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,TOUCH.CURX);
            if (regaddr1==TCURY)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,TOUCH.CURY);
            return NO_ERROR;
        }

    }

    PROTOCOL_recvResponse(out_str,devaddr1,func1+0x80,regaddr1,LENGTH_ERROR);
    return LENGTH_ERROR;
}

