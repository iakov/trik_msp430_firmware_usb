#!/bin/sh

# Test1 for motors

stty -F /dev/ttyACM0 -echo -onlcr

#out_device="/dev/tty"
out_device="000.txt"

printf "" | tee $out_device

period=1000
duty=800

devaddr=0

set_period_for_motor ()
{
	local crc=0
	local func=3
	local regaddr=2
	#Start condition
	printf ":"	
	#Motor number
	if [ $devaddr -lt 16 ]; then printf "0%X" $devaddr | tee -a $out_device;
		else printf "%X" $devaddr | tee -a $out_device;
	fi
	#Function number
	if [ $func -lt 16 ]; then printf "0%X" $func | tee -a $out_device;
		else printf "%X" $func | tee -a $out_device;
	fi
	#Register number
	if [ $regaddr -lt 16 ]; then printf "0%X" $regaddr | tee -a $out_device;
		else printf "%X" $regaddr | tee -a $out_device;
	fi
	#Register value
	if [ $period -lt 16 ]; then printf "000%X" $period | tee -a $out_device;
		elif [ $period -lt 256 ]; then printf "00%X" $period | tee -a $out_device;
		elif [ $period -lt 4096 ]; then printf "0%X" $period | tee -a $out_device;
		else printf "%X" $period | tee -a $out_device;
	fi
	crc=$((((0-($devaddr+$func+$regaddr+(($period>>8)&255)+($period&255)))&255)))
	if [ $crc -lt 16 ]; then printf "0%X\n" $crc | tee -a $out_device;
		else printf "%X\n" $crc | tee -a $out_device;
	fi
	return
}

set_duty_for_motor ()
{
	local crc=0
	local func=3
	local regaddr=1
	#Start condition
	printf ":"	
	#Motor number
	if [ $devaddr -lt 16 ]; then printf "0%X" $devaddr | tee -a $out_device;
		else printf "%X" $devaddr | tee -a $out_device;
	fi
	#Function number
	if [ $func -lt 16 ]; then printf "0%X" $func | tee -a $out_device;
		else printf "%X" $func | tee -a $out_device;
	fi
	#Register number
	if [ $regaddr -lt 16 ]; then printf "0%X" $regaddr | tee -a $out_device;
		else printf "%X" $regaddr | tee -a $out_device;
	fi
	#Register value
	if [ $duty -lt 16 ]; then printf "000%X" $duty | tee -a $out_device;
		elif [ $duty -lt 256 ]; then printf "00%X" $duty | tee -a $out_device;
		elif [ $duty -lt 4096 ]; then printf "0%X" $duty | tee -a $out_device;
		else printf "%X" $duty | tee -a $out_device;
	fi
	crc=$((((0-($devaddr+$func+$regaddr+(($duty>>8)&255)+($duty&255)))&255)))
	if [ $crc -lt 16 ]; then printf "0%X\n" $crc | tee -a $out_device;
		else printf "%X\n" $crc | tee -a $out_device;
	fi
	return
}

stop_motor ()
{
}



devaddr=0; set_period_for_motor
devaddr=1; set_period_for_motor
devaddr=2; set_period_for_motor
devaddr=3; set_period_for_motor

devaddr=0; duty=800; set_duty_for_motor
devaddr=1; duty=800; set_duty_for_motor
devaddr=2; duty=800; set_duty_for_motor
devaddr=3; duty=800; set_duty_for_motor

