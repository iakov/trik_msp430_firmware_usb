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
#include "driverlib.h"
#include "Trik_Devices/trik_protocolhandler.h"
#include "Trik_Devices/trik_motor.h"
#include "Trik_Devices/trik_sensor.h"
#include "Trik_Devices/trik_encoder.h"
#include "Trik_Devices/trik_bsl.h"
#include "Trik_Devices/trik_devices.h"
#include "Trik_Devices/trik_async.h"
#include "Trik_Devices/trik_touch.h"
//#include "Trik_Devices/trik_port.h"

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

/*
uint8_t hex2char(char *string, uint8_t pos)
{
    uint8_t an = string[pos] > '9' ? string[pos] - 'A' + 10 : string[pos] - '0';
    uint8_t bn = string[pos+1] > '9' ? string[pos+1] - 'A' + 10 : string[pos+1] - '0';
    return (an << 4 ) | bn;
}

uint16_t hex2int(char *string, uint8_t pos)
{
    uint8_t an = string[pos] > '9' ? string[pos] - 'A' + 10 : string[pos] - '0';
    uint8_t bn = string[pos+1] > '9' ? string[pos+1] - 'A' + 10 : string[pos+1] - '0';
    uint8_t cn = string[pos+2] > '9' ? string[pos+2] - 'A' + 10 : string[pos+2] - '0';
    uint8_t dn = string[pos+3] > '9' ? string[pos+3] - 'A' + 10 : string[pos+3] - '0';
    return (an << 12) | (bn << 8) | (cn << 4) | dn;
}
*/

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

//Error response
void PROTOCOL_errResponse(char *r_str, uint8_t dev_addr, uint8_t func_code, uint8_t err_code)
{
	char stmp1[MAX_STRING_LENGTH]; //Temp string
	uint8_t crc; //Checksum

	r_str[0] = ':';
	r_str[1] = '\0';

	char2hex(stmp1,dev_addr);
	strcat(r_str,stmp1);

	if (func_code<0x80) func_code += 0x80;
	char2hex(stmp1,func_code);
	strcat(r_str,stmp1);

    char2hex(stmp1,err_code);
    strcat(r_str,stmp1);

	crc = 0 - (dev_addr + func_code + err_code);
    char2hex(stmp1,crc);
    strcat(r_str,stmp1);

	strcat(r_str,"\n\0");
}

//Write register response
void PROTOCOL_transResponse(char *r_str, uint8_t dev_addr, uint8_t resp_code)
{
    char stmp1[MAX_STRING_LENGTH]; //Temp string
    uint8_t crc; //Checksum

    r_str[0] = ':';
    r_str[1] = '\0';

    char2hex(stmp1,dev_addr);
    strcat(r_str,stmp1);

    char2hex(stmp1,resp_code);
    strcat(r_str,stmp1);

    crc = 0 - (dev_addr + resp_code);
    char2hex(stmp1,crc);
    strcat(r_str,stmp1);

    strcat(r_str,"\n\0");
}

//Read register response
void PROTOCOL_recvResponse(char *r_str, uint8_t dev_addr, uint8_t resp_code, uint8_t reg_addr, uint32_t reg_val, uint8_t reg_size)
{
    char stmp1[MAX_STRING_LENGTH]; //Temp string
    uint8_t t11,t12,t13,t14; //Temp vars
    uint8_t crc; //Checksum

    if (reg_size==REG_32bits)
    {
        t11 = (uint8_t)((reg_val & 0xFF000000) >> 24);
        t12 = (uint8_t)((reg_val & 0x00FF0000) >> 16);
    }
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

    if (reg_size==REG_32bits)
    {
        char2hex(stmp1,t11);
        strcat(r_str,stmp1);
        char2hex(stmp1,t12);
        strcat(r_str,stmp1);
    } else
    {
        t11 = t12 = 0;
    }
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
		strcpy(out_str,":000013ED\n\0");
		return START_ERROR;
	}

	//Incorrect packet length
	if ((strlen(in_str)!=9) && (strlen(in_str)!=13) && (strlen(in_str)!=17))
	{
		strcpy(out_str,":000014EC\n\0");
		return LENGTH_ERROR;
	}

	//Get device address
	devaddr1 = hex2num(in_str, 1, NUM_BYTE);

	//Get function
	func1 = hex2num(in_str, 3, NUM_BYTE);

	//Get register address
	regaddr1 = hex2num(in_str, 5, NUM_BYTE);

	//Get register value
	if (func1==FUNCx03)
	    regval1 = hex2num(in_str, 7, NUM_WORD);

	if (func1==FUNCx04)
	    regval1 = hex2num(in_str, 7, NUM_DWORD);

	//Device addresses range
	if ((devaddr1>MAX_DEVICES) && (devaddr1!=BSL))
	{
	    PROTOCOL_errResponse(out_str,devaddr1,func1,DEV_ADDR_ERROR);
		return DEV_ADDR_ERROR;
	}

	//Motor registers addresses range
	//if (((devaddr1>=MOTOR1) && (devaddr1<=MOTOR4)) && (regaddr1>0x06))
	if (((devaddr1<=MOTOR4)) && (regaddr1>0x06))
	{
	    PROTOCOL_errResponse(out_str,devaddr1,func1,REG_ADDR_ERROR);
		return REG_ADDR_ERROR;
	}

	//Sensor registers addresses range
	if (((devaddr1>=SENSOR1) && (devaddr1<=SENSOR18)) && (regaddr1>0x02))
	{
	    PROTOCOL_errResponse(out_str,devaddr1,func1,REG_ADDR_ERROR);
		return REG_ADDR_ERROR;
	}

	//Encoder registers addresses range
	if (((devaddr1>=ENCODER1) && (devaddr1<=ENCODER4)) && (regaddr1>0x01))
	{
	    PROTOCOL_errResponse(out_str,devaddr1,func1,REG_ADDR_ERROR);
	    return REG_ADDR_ERROR;
	}

    //Port registers addresses range
    if (((devaddr1>=PORT1) && (devaddr1<=PORTJ)) && (regaddr1>0x08))
    {
        PROTOCOL_errResponse(out_str,devaddr1,func1,REG_ADDR_ERROR);
        return REG_ADDR_ERROR;
    }

	//Function number check
	if ((func1!=FUNCx03) && (func1!=FUNCx04) && (func1!=FUNCx05) && (func1!=FUNCx06))
	{
	    PROTOCOL_errResponse(out_str,devaddr1,func1,FUNC_CODE_ERROR);
		return FUNC_CODE_ERROR;
	}

	//CRC check
	switch (func1)
	{
	    case FUNCx03:
	        crc1 = hex2num(in_str, 11, NUM_BYTE);
	        break;
        case FUNCx04:
            crc1 = hex2num(in_str, 15, NUM_BYTE);
            break;
        case FUNCx05:
            crc1 = hex2num(in_str, 7, NUM_BYTE);
            break;
        case FUNCx06:
            crc1 = hex2num(in_str, 7, NUM_BYTE);
            break;
        default:
            break;
	}
	if ((func1==FUNCx03) || (func1==FUNCx04))
	    crc2=0-(devaddr1+func1+regaddr1+
	            (uint8_t)(regval1 & 0x000000FF)+(uint8_t)((regval1 & 0x0000FF00) >> 8)+
	            (uint8_t)((regval1 & 0x00FF0000) >> 16)+(uint8_t)((regval1 & 0xFF000000) >> 24));
	if ((func1==FUNCx05) || (func1==FUNCx06))
	    crc2=0-(devaddr1+func1+regaddr1);
	if (crc1!=crc2)
	{
	    PROTOCOL_errResponse(out_str,devaddr1,func1,CRC_ERROR);
	    return CRC_ERROR;
	}

	//Hadle of function 0x03 - write single 16 bit register
	if (((func1==FUNCx03) && (strlen(in_str)==13)) || ((func1==FUNCx04) && (strlen(in_str)==17)))
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
                PROTOCOL_errResponse(out_str,devaddr1,func1,REG_VAL_ERROR);
                return REG_VAL_ERROR;
            }
            MOTOR_handler(devaddr1);
            PROTOCOL_transResponse(out_str,devaddr1,MOT[devaddr1].MSTA);
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
            PROTOCOL_transResponse(out_str,devaddr1,ENC[devaddr1-ENCODER1].ESTA);
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
            PROTOCOL_transResponse(out_str,devaddr1,SENS[devaddr1-SENSOR1].SSTA);
            return NO_ERROR;
        }

        /*
        //Ports
        if ((devaddr1>=PORT1) && (devaddr1<=PORTJ))
        {
            PORT_write(devaddr1, regaddr1, regval1);
            PROTOCOL_transResponse(out_str,devaddr1,NO_ERROR);
            return NO_ERROR;
        }
        */

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
            PROTOCOL_transResponse(out_str,devaddr1,NO_ERROR);
            return NO_ERROR;
        }

	    //BSL
	    if ((devaddr1==BSL) && (regaddr1==0x00))
	    {
	        PROTOCOL_transResponse(out_str,devaddr1,
	                BSL_enterBSL(regval1));
	        return NO_ERROR;
	    }

	    //If not found any devices
	    PROTOCOL_errResponse(out_str,devaddr1,func1,DEV_ADDR_ERROR);
	    return DEV_ADDR_ERROR;
	}

	//Functions 0x05/0x06 - read single register
    if (((func1==FUNCx05) && (strlen(in_str)==9)) || ((func1==FUNCx06) && (strlen(in_str)==9)))
    {

        //Motors
        //if ((devaddr1>=MOTOR1) && (devaddr1<=MOTOR4))
        if ((devaddr1<=MOTOR4))
        {
            if (regaddr1==MMCTL)
                PROTOCOL_recvResponse(out_str,devaddr1,MOT[devaddr1].MSTA,regaddr1,MOT[devaddr1].MCTL,REG_16bits);
            if (regaddr1==MMDUT)
                PROTOCOL_recvResponse(out_str,devaddr1,MOT[devaddr1].MSTA,regaddr1,MOT[devaddr1].MDUT,REG_16bits);
            if (regaddr1==MMPER)
                PROTOCOL_recvResponse(out_str,devaddr1,MOT[devaddr1].MSTA,regaddr1,MOT[devaddr1].MPER,REG_16bits);
            if (regaddr1==MMANG)
                PROTOCOL_recvResponse(out_str,devaddr1,MOT[devaddr1].MSTA,regaddr1,MOT[devaddr1].MANG,REG_32bits);
            if (regaddr1==MMTMR)
                PROTOCOL_recvResponse(out_str,devaddr1,MOT[devaddr1].MSTA,regaddr1,MOT[devaddr1].MTMR,REG_32bits);
            if (regaddr1==MMVAL)
                PROTOCOL_recvResponse(out_str,devaddr1,MOT[devaddr1].MSTA,regaddr1,MOT[devaddr1].MVAL,REG_32bits);
            if (regaddr1==MMERR)
                PROTOCOL_recvResponse(out_str,devaddr1,MOT[devaddr1].MSTA,regaddr1,MOT[devaddr1].MERR,REG_32bits);
            return NO_ERROR;
        }

        //Encoders
        if ((devaddr1>=ENCODER1) && (devaddr1<=ENCODER4))
        {
            if (regaddr1==EECTL)
                PROTOCOL_recvResponse(out_str,devaddr1,ENC[devaddr1-ENCODER1].ESTA,regaddr1,ENC[devaddr1-ENCODER1].ECTL,REG_16bits);
            if (regaddr1==EEVAL)
                PROTOCOL_recvResponse(out_str,devaddr1,ENC[devaddr1-ENCODER1].ESTA,regaddr1,ENC[devaddr1-ENCODER1].EVAL,REG_32bits);
            return NO_ERROR;
        }

        //Sensors
        if ((devaddr1>=SENSOR1) && (devaddr1<=SENSOR18))
        {
            SENSOR_handler(devaddr1);
            if (regaddr1==SSCTL)
                PROTOCOL_recvResponse(out_str,devaddr1,SENS[devaddr1-SENSOR1].SSTA,regaddr1,SENS[devaddr1-SENSOR1].SCTL,REG_16bits);
            if (regaddr1==SSIDX)
                PROTOCOL_recvResponse(out_str,devaddr1,SENS[devaddr1-SENSOR1].SSTA,regaddr1,SENS[devaddr1-SENSOR1].SIDX,REG_16bits);
            if (regaddr1==SSVAL)
                PROTOCOL_recvResponse(out_str,devaddr1,SENS[devaddr1-SENSOR1].SSTA,regaddr1,SENS[devaddr1-SENSOR1].SVAL,REG_32bits);
            return NO_ERROR;
        }

        /*
        //Ports
        if ((devaddr1>=PORT1) && (devaddr1<=PORTJ))
        {
            PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,
                    PORT_read(devaddr1,regaddr1),REG_16bits);
            return NO_ERROR;
        }
        */

        //Async timer
        if ((devaddr1==ASYNCTIMER))
        {
            if (regaddr1==AATCTL)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,ASYNCTMR.ATCTL,REG_16bits);
            if (regaddr1==AATPER)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,ASYNCTMR.ATPER,REG_16bits);
            if (regaddr1==AATVAL)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,ASYNCTMR.ATVAL,REG_32bits);
            return NO_ERROR;
        }

        //Touch controller
        if ((devaddr1==TOUCHDEVICE))
        {
            if (regaddr1==TTMOD)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,TOUCH.TMOD,REG_16bits);
            if (regaddr1==TMINX)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,TOUCH.MINX,REG_16bits);
            if (regaddr1==TMAXX)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,TOUCH.MAXX,REG_16bits);
            if (regaddr1==TMINY)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,TOUCH.MINY,REG_16bits);
            if (regaddr1==TMAXY)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,TOUCH.MAXY,REG_16bits);
            if (regaddr1==TSCRX)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,TOUCH.SCRX,REG_16bits);
            if (regaddr1==TSCRY)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,TOUCH.SCRY,REG_16bits);
            if (regaddr1==TCURX)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,TOUCH.CURX,REG_16bits);
            if (regaddr1==TCURY)
                PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,TOUCH.CURY,REG_16bits);
            return NO_ERROR;
        }

    }

    PROTOCOL_errResponse(out_str,devaddr1,func1,LENGTH_ERROR);
    return LENGTH_ERROR;
}

