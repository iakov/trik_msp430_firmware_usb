/*
 * Trik_ProtocolHandler.c
 *
 *  Created on: 21 окт. 2014 г.
 *      Author: Rostislav Varzar
 */

#include "Trik_Devices/Trik_ProtocolHandler.h"
#include "Trik_Devices/Trik_Devices.h"

//Error response
void PROTOCOL_errResponse(char *r_str, uint8_t dev_addr, uint8_t func_code, uint8_t err_code)
{
	char stmp1[MAX_STRING_LENGTH]; //Temp string
	memset(r_str,0,MAX_STRING_LENGTH);
	if (dev_addr<16) sprintf(r_str,"0%x",dev_addr);
	if (dev_addr>=16) sprintf(r_str,"%x",dev_addr);
	if (func_code<0x80) func_code+=0x80;
	if (func_code<16) sprintf(stmp1,"0%x",func_code);
	if (func_code>=16) sprintf(stmp1,"%x",func_code);
	strcat(r_str,stmp1);
	if (err_code<16) sprintf(stmp1,"0%x",err_code);
	if (err_code>=16) sprintf(stmp1,"%x",err_code);
}

//Protocol handler
uint8_t PROTOCOL_hadler(char *in_str, char *out_str)
{
	char stmp1[MAX_STRING_LENGTH]; //Temp string
	uint8_t devaddr1; //Device address
	uint8_t func1; //Function number
	uint8_t regaddr1; //Register address
	uint32_t regval1; //Register value
	uint8_t crc1; //Cheksum
	uint8_t crc2; //Calculated checksum

	//Clear output string
	memset(out_str,0,MAX_STRING_LENGTH);

	//Start condition error
	if (in_str[0]!=':')
	{
		sprintf(out_str,":00000013ED\r\n");
		return 0x13;
	}

	//Incorrect packet length
	if ((strlen(in_str)!=15) && (strlen(in_str)!=19) && (strlen(in_str)!=23))
	{
		sprintf(out_str,":00000014EC\r\n");
		return 0x14;
	}

	//Get device address
	sprintf(stmp1,"%c%c%c%c",in_str[1],in_str[2],in_str[3],in_str[4]);
	devaddr1=strtoul(stmp1,&stmp1[4],16);
	//Get function
	sprintf(stmp1,"%c%c",in_str[5],in_str[6]);
	func1=strtoul(stmp1,&stmp1[2],16);
	//Get register address
	sprintf(stmp1,"%c%c%c%c",in_str[7],in_str[8],in_str[9],in_str[10]);
	regaddr1=strtoul(stmp1,&stmp1[4],16);

	//Device addresses range
	if ((devaddr1<0x0000) || (devaddr1>MAX_PORTS))
	{

		return 0x11;
	}

	//Motor registers addresses range
	if (((devaddr1>=MOTOR1) && (devaddr1<=MOTOR4)) && ((regaddr1<0x0000) || ((regaddr1>0x0006))))
	{

		return 0x02;
	}

	//Sensor registers addresses range
	if (((devaddr1>=SENSOR1) && (devaddr1<=SENSOR14)) && ((regaddr1<0x0000) || ((regaddr1>0x0004))))
	{

		return 0x02;
	}

	//Actuator registers addresses range
	if (((devaddr1>=ACTUATOR1) && (devaddr1<=ACTUATOR20)) && ((regaddr1<0x0000) || ((regaddr1>0x0004))))
	{

		return 0x02;
	}

	//Function number check
	if ((func1!=0x03) && (func1!=0x04) && (func1!=0x05) && (func1!=0x06))
	{

		return 0x01;
	}

	//Packet size check according to function number
	if ((func1==0x03) && (strlen(in_str)!=19))
	{

		return 0x14;
	}




	return 0x00;
}

