/*
 * Trik_ProtocolHandler.c
 *
 *  Created on: 21 окт. 2014 г.
 *      Author: Rostislav Varzar
 */

#include "Trik_Devices/Trik_ProtocolHandler.h"
#include "Trik_Devices/Trik_Devices.h"

//Protocol handler
uint8_t PROTOCOL_hadler(char *in_str, char *out_str)
{
	char stmp1[MAX_STRING_LENGTH]; //Temp string
	uint16_t devaddr1; //Device address
	uint16_t func1; //Function number
	uint16_t regaddr1; //Register address
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




	return 0;
}

