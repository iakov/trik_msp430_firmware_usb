/*
 * Trik_ProtocolHandler.c
 *
 *  Created on: October 21, 2014
 *      Author: Rostislav Varzar
 */

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "driverlib.h"
#include "Trik_Devices/trik_protocolhandler.h"
#include "Trik_Devices/trik_motor.h"
#include "Trik_Devices/trik_sensor.h"
#include "Trik_Devices/trik_encoder.h"
#include "Trik_Devices/trik_bsl.h"
#include "Trik_Devices/trik_devices.h"
#include "Trik_Devices/trik_async.h"

//Error response
void PROTOCOL_errResponse(char *r_str, uint8_t dev_addr, uint8_t func_code, uint8_t err_code)
{
	char stmp1[MAX_STRING_LENGTH]; //Temp string
	uint8_t crc;
	memset(r_str,0,MAX_STRING_LENGTH);
	if (dev_addr<16)
	    sprintf(r_str,":0%x",dev_addr);
	else
	    sprintf(r_str,":%x",dev_addr);
	if (func_code<0x80) func_code+=0x80;
	if (func_code<16)
	    sprintf(stmp1,"0%x",func_code);
	else
	    sprintf(stmp1,"%x",func_code);
	strcat(r_str,stmp1);
	if (err_code<16)
	    sprintf(stmp1,"0%x",err_code);
	else
	    sprintf(stmp1,"%x",err_code);
	strcat(r_str,stmp1);
	crc=0-(dev_addr+func_code+err_code);
	if (crc<16)
	    sprintf(stmp1,"0%x",crc);
	else
	    sprintf(stmp1,"%x",crc);
	strcat(r_str,stmp1);
	sprintf(stmp1,"\n");
	strcat(r_str,stmp1);
}

//Write register response
void PROTOCOL_transResponse(char *r_str, uint8_t dev_addr, uint8_t resp_code)
{
    char stmp1[MAX_STRING_LENGTH]; //Temp string
    uint8_t crc;
    memset(r_str,0,MAX_STRING_LENGTH);
    if (dev_addr<16)
        sprintf(r_str,":0%x",dev_addr);
    else
        sprintf(r_str,":%x",dev_addr);
    if (resp_code<16)
        sprintf(stmp1,"0%x",resp_code);
    else
        sprintf(stmp1,"%x",resp_code);
    strcat(r_str,stmp1);
    crc=0-(dev_addr+resp_code);
    if (crc<16)
        sprintf(stmp1,"0%x",crc);
    else
        sprintf(stmp1,"%x",crc);
    strcat(r_str,stmp1);
    sprintf(stmp1,"\n");
    strcat(r_str,stmp1);
}

//Read register response
void PROTOCOL_recvResponse(char *r_str, uint8_t dev_addr, uint8_t resp_code, uint8_t reg_addr, uint32_t reg_val, uint8_t reg_size)
{
    char stmp1[MAX_STRING_LENGTH]; //Temp string
    uint8_t crc,t11,t12,t13,t14;
    if (reg_size==REG_32bits)
    {
        t11=(uint8_t)((reg_val & 0xFF000000) >> 24);
        t12=(uint8_t)((reg_val & 0x00FF0000) >> 16);
    }
    t13=(uint8_t)((reg_val & 0x0000FF00) >> 8);
    t14=(uint8_t)(reg_val & 0x000000FF);
    memset(r_str,0,MAX_STRING_LENGTH);
    if (dev_addr<16)
        sprintf(r_str,":0%x",dev_addr);
    else
        sprintf(r_str,":%x",dev_addr);
    if (resp_code<16)
        sprintf(stmp1,"0%x",resp_code);
    else
        sprintf(stmp1,"%x",resp_code);
    strcat(r_str,stmp1);
    if (reg_addr<16)
        sprintf(stmp1,"0%x",reg_addr);
    else
        sprintf(stmp1,"%x",reg_addr);
    strcat(r_str,stmp1);
    if (reg_size==REG_32bits)
    {
        if (t11<16)
            sprintf(stmp1,"0%x",t11);
        else
            sprintf(stmp1,"%x",t11);
        strcat(r_str,stmp1);
        if (t12<16)
            sprintf(stmp1,"0%x",t12);
        else
            sprintf(stmp1,"%x",t12);
        strcat(r_str,stmp1);
    }
    else
    {
        t11 = t12 = 0;
    }
    if (t13<16)
        sprintf(stmp1,"0%x",t13);
    else
        sprintf(stmp1,"%x",t13);
    strcat(r_str,stmp1);
    if (t14<16)
        sprintf(stmp1,"0%x",t14);
    else
        sprintf(stmp1,"%x",t14);
    strcat(r_str,stmp1);
    crc=0-(dev_addr+resp_code+reg_addr+t11+t12+t13+t14);
    if (crc<16)
        sprintf(stmp1,"0%x",crc);
    else
        sprintf(stmp1,"%x",crc);
    strcat(r_str,stmp1);
    sprintf(stmp1,"\n");
    strcat(r_str,stmp1);
}

//Protocol handler
uint8_t PROTOCOL_hadler(char *in_str, char *out_str)
{
	char stmp1[MAX_STRING_LENGTH]; //Temp string
	uint8_t devaddr1 = 0; //Device address
	uint8_t func1 = 0; //Function number
	uint8_t regaddr1 = 0; //Register address
	uint32_t regval1 = 0; //Register value
	uint8_t crc1 = 0; //Cheksum
	uint8_t crc2 = 0; //Calculated checksum
	uint8_t errhandler = 0; //Result code of handlers

	//Clear output string
	memset(out_str,0,MAX_STRING_LENGTH);

	//Start condition error
	if (in_str[0]!=':')
	{
		sprintf(out_str,":000013ED\n");
		return START_ERROR;
	}

	//Incorrect packet length
	if ((strlen(in_str)!=9) && (strlen(in_str)!=13) && (strlen(in_str)!=17))
	{
		sprintf(out_str,":000014EC\n");
		return LENGTH_ERROR;
	}

	//Get device address
	sprintf(stmp1,"%c%c",in_str[1],in_str[2]);
	devaddr1=strtoul(stmp1,&stmp1[2],16);

	//Get function
	sprintf(stmp1,"%c%c",in_str[3],in_str[4]);
	func1=strtoul(stmp1,&stmp1[2],16);

	//Get register address
	sprintf(stmp1,"%c%c",in_str[5],in_str[6]);
	regaddr1=strtoul(stmp1,&stmp1[2],16);

	//Get register value
	if (func1==0x03)
	{
	    sprintf(stmp1,"%c%c%c%c",in_str[7],in_str[8],in_str[9],in_str[10]);
	    regval1=strtoul(stmp1,&stmp1[4],16);
	}
	if (func1==0x04)
	{
	    sprintf(stmp1,"%c%c%c%c%c%c%c%c",in_str[7],in_str[8],in_str[9],in_str[10],in_str[11],in_str[12],in_str[13],in_str[14]);
	    regval1=strtoul(stmp1,&stmp1[8],16);
	}

	//Device addresses range
	if ((devaddr1>MAX_DEVICES) && (devaddr1!=BSL))
	{
	    PROTOCOL_errResponse(out_str,devaddr1,func1,DEV_ADDR_ERROR);
		return DEV_ADDR_ERROR;
	}

	//Motor registers addresses range
	if (((devaddr1>=MOTOR1) && (devaddr1<=MOTOR4)) && (regaddr1>0x06))
	{
	    PROTOCOL_errResponse(out_str,devaddr1,func1,REG_ADDR_ERROR);
		return REG_ADDR_ERROR;
	}

	//Sensor registers addresses range
	if (((devaddr1>=SENSOR1) && (devaddr1<=SENSOR14)) && (regaddr1>0x04))
	{
	    PROTOCOL_errResponse(out_str,devaddr1,func1,REG_ADDR_ERROR);
		return REG_ADDR_ERROR;
	}

	//Encoder registers addresses range
	if (((devaddr1>=ENCODER1) && (devaddr1<=ENCODER4)) && (regaddr1>0x03))
	{
	    PROTOCOL_errResponse(out_str,devaddr1,func1,REG_ADDR_ERROR);
	    return REG_ADDR_ERROR;
	}

	//Actuator registers addresses range
	if (((devaddr1>=ACTUATOR1) && (devaddr1<=ACTUATOR20)) && (regaddr1>0x04))
	{
	    PROTOCOL_errResponse(out_str,devaddr1,func1,REG_ADDR_ERROR);
		return REG_ADDR_ERROR;
	}

	//Function number check
	if ((func1!=0x03) && (func1!=0x04) && (func1!=0x05) && (func1!=0x06))
	{
	    PROTOCOL_errResponse(out_str,devaddr1,func1,FUNC_CODE_ERROR);
		return FUNC_CODE_ERROR;
	}

	//CRC check
	if (func1==0x03)
	{
	    sprintf(stmp1,"%c%c",in_str[11],in_str[12]);
	    crc1=strtoul(stmp1,&stmp1[2],16);
	}
	if (func1==0x04)
	{
	    sprintf(stmp1,"%c%c",in_str[15],in_str[16]);
	    crc1=strtoul(stmp1,&stmp1[2],16);
	}
	if ((func1==0x05) || (func1==0x06))
	{
	    sprintf(stmp1,"%c%c",in_str[7],in_str[8]);
	    crc1=strtoul(stmp1,&stmp1[2],16);
	}
	if ((func1==0x03) || (func1==0x04)) crc2=0-(devaddr1+func1+regaddr1+
	        (uint8_t)(regval1 & 0x000000FF)+(uint8_t)((regval1 & 0x0000FF00) >> 8)+
	        (uint8_t)((regval1 & 0x00FF0000) >> 16)+(uint8_t)((regval1 & 0xFF000000) >> 24));
	if ((func1==0x05) || (func1==0x06)) crc2=0-(devaddr1+func1+regaddr1);
	if (crc1!=crc2)
	{
	    PROTOCOL_errResponse(out_str,devaddr1,func1,CRC_ERROR);
	    return CRC_ERROR;
	}

	//Hadle of function 0x03 - write single 16 bit register
	if (((func1==0x03) && (strlen(in_str)==13)) || ((func1==0x04) && (strlen(in_str)==17)))
	{
	    //Motors
	    if ((devaddr1>=MOTOR1) && (devaddr1<=MOTOR4))
	    {
	        if (regaddr1==MMCTL) MOT[devaddr1].MCTL=regval1;
	        if (regaddr1==MMDUT) MOT[devaddr1].MDUT=regval1;
	        if (regaddr1==MMPER) MOT[devaddr1].MPER=regval1;
	        if (regaddr1==MMANG) MOT[devaddr1].MANG=regval1;
	        if (regaddr1==MMTMR) MOT[devaddr1].MTMR=regval1;
	        if (regaddr1==MMVAL) MOT[devaddr1].MVAL=regval1;
	        //Error register values
	        if (((MOT[devaddr1].MPER==0) || (MOT[devaddr1].MDUT>MOT[devaddr1].MPER)) && (MOT[devaddr1].MCTL & 0x0004))
	        {
	            PROTOCOL_errResponse(out_str,devaddr1,func1,REG_VAL_ERROR);
	            return REG_VAL_ERROR;
	        }
	        else
	        {
	            if (regaddr1==MMCTL)
	            {
	                errhandler=MOTOR_hadler(devaddr1);
	                PROTOCOL_transResponse(out_str,devaddr1,errhandler);
	            }
	            else
	                PROTOCOL_transResponse(out_str,devaddr1,NO_ERROR);
	            return NO_ERROR;
	        }
	    }

	    //Encoders
        if ((devaddr1>=ENCODER1) && (devaddr1<=ENCODER4))
        {
            if (regaddr1==EECTL) ENC[devaddr1-ENCODER1].ECTL=regval1;
            if (regaddr1==EEVAL) ENC[devaddr1-ENCODER1].EVAL=regval1;
            if (regaddr1==EECTL)
            {
                errhandler=ENCODER_hadler(devaddr1);
                PROTOCOL_transResponse(out_str,devaddr1,errhandler);
            }
            else PROTOCOL_transResponse(out_str,devaddr1,NO_ERROR);
            return NO_ERROR;
        }

        //Async timer
        if ((devaddr1==ASYNCTIMER))
        {
            if (regaddr1==AATCTL) ASYNCTMR.ATCTL=regval1;
            if (regaddr1==AATPER) ASYNCTMR.ATPER=regval1+MAX_DEVICES;
            if (regaddr1==AATVAL) ASYNCTMR.ATVAL=regval1;
            if (regaddr1==AATCTL)
            {
                errhandler=ASYNCTIMER_hadler();
                PROTOCOL_transResponse(out_str,devaddr1,errhandler);
            }
            else PROTOCOL_transResponse(out_str,devaddr1,NO_ERROR);
            return NO_ERROR;
        }

	    //BSL
	    if ((devaddr1==BSL) && (regaddr1==0x00))
	    {
	        errhandler=BSL_enterBSL(regval1);
	        PROTOCOL_transResponse(out_str,devaddr1,errhandler);
	        //sprintf(out_str,"%x %x %x\r\n",devaddr1,regaddr1,(regval1==0xA480E917));
	        return NO_ERROR;
	    }

	    //If not found any devices
	    PROTOCOL_errResponse(out_str,devaddr1,func1,DEV_ADDR_ERROR);
	    return DEV_ADDR_ERROR;
	}

	//Functions 0x05/0x06 - read single register
    if (((func1==0x05) && (strlen(in_str)==9)) || ((func1==0x06) && (strlen(in_str)==9)))
    {

        //Motors
        if ((devaddr1>=MOTOR1) && (devaddr1<=MOTOR4))
        {
            if (regaddr1==MMCTL) PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,MOT[devaddr1].MCTL,REG_16bits);
            if (regaddr1==MMDUT) PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,MOT[devaddr1].MDUT,REG_16bits);
            if (regaddr1==MMPER) PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,MOT[devaddr1].MPER,REG_16bits);
            if (regaddr1==MMANG) PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,MOT[devaddr1].MANG,REG_32bits);
            if (regaddr1==MMTMR) PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,MOT[devaddr1].MTMR,REG_32bits);
            if (regaddr1==MMVAL) PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,MOT[devaddr1].MVAL,REG_32bits);
            if (regaddr1==MMSTA) PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,MOT[devaddr1].MSTA,REG_16bits);
            return NO_ERROR;
        }

        //Encoders
        if ((devaddr1>=ENCODER1) && (devaddr1<=ENCODER4))
        {
            if (regaddr1==EECTL) PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,ENC[devaddr1-ENCODER1].ECTL,REG_16bits);
            if (regaddr1==EEVAL) PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,ENC[devaddr1-ENCODER1].EVAL,REG_32bits);
            if (regaddr1==EESTA) PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,ENC[devaddr1-ENCODER1].ESTA,REG_16bits);
            return NO_ERROR;
        }

        //Async timer
        if ((devaddr1==ASYNCTIMER))
        {
            if (regaddr1==AATCTL) PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,ASYNCTMR.ATCTL,REG_16bits);
            if (regaddr1==AATPER) PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,ASYNCTMR.ATPER,REG_16bits);
            if (regaddr1==AATVAL) PROTOCOL_recvResponse(out_str,devaddr1,NO_ERROR,regaddr1,ASYNCTMR.ATVAL,REG_32bits);
            return NO_ERROR;
        }
    }

    PROTOCOL_errResponse(out_str,devaddr1,func1,LENGTH_ERROR);
    return LENGTH_ERROR;

    sprintf(out_str,":FFFFFF03\r\n");
	return UNDEF_ERROR;
}

