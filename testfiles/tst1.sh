#!/bin/sh

# Test1 for motors

stty -F /dev/ttyACM0 -echo -onlcr

cat /dev/ttyACM0 &

#out_device="/dev/tty"
out_device="/dev/ttyACM0"
#out_device="000.txt"

printf "Privet!\n" > $out_device; printf "Privet!\n";

period=1000
duty=800

set_period_for_motor ()
{
	local crc
	local func=3
	local regaddr=2
	#Start condition
	printf ":" >> $out_device; printf ":";
	#Motor number
	if [ $devaddr -lt 16 ]; then printf "0%X" $devaddr >> $out_device; printf "0%X" $devaddr;
		else printf "%X" $devaddr >> $out_device; printf "%X" $devaddr;
	fi
	#Function number
	if [ $func -lt 16 ]; then printf "0%X" $func >> $out_device; printf "0%X" $func;
		else printf "%X" $func >> $out_device; printf "%X" $func;
	fi
	#Register number
	if [ $regaddr -lt 16 ]; then printf "0%X" $regaddr >> $out_device; printf "0%X" $regaddr;
		else printf "%X" $regaddr >> $out_device; printf "%X" $regaddr;
	fi
	#Register value
	if [ $period -lt 16 ]; then printf "000%X" $period >> $out_device; printf "000%X" $period;
		elif [ $period -lt 256 ]; then printf "00%X" $period >> $out_device; printf "00%X" $period;
		elif [ $period -lt 4096 ]; then printf "0%X" $period >> $out_device; printf "0%X" $period;
		else printf "%X" $period >> $out_device; printf "%X" $period;
	fi
	crc=$((((0-($devaddr+$func+$regaddr+(($period>>8)&255)+($period&255)))&255)))
	if [ $crc -lt 16 ]; then printf "0%X\n" $crc >> $out_device; printf "0%X\n" $crc;
		else printf "%X\n" $crc >> $out_device; printf "%X\n" $crc;
	fi
	return
}

set_duty_for_motor ()
{
	local crc
	local func=3
	local regaddr=1
	#Start condition
	printf ":" >> $out_device; printf ":";
	#Motor number
	if [ $devaddr -lt 16 ]; then printf "0%X" $devaddr >> $out_device; printf "0%X" $devaddr;
		else printf "%X" $devaddr >> $out_device; printf "%X" $devaddr;
	fi
	#Function number
	if [ $func -lt 16 ]; then printf "0%X" $func >> $out_device; printf "0%X" $func;
		else printf "%X" $func >> $out_device; printf "%X" $func;
	fi
	#Register number
	if [ $regaddr -lt 16 ]; then printf "0%X" $regaddr >> $out_device; printf "0%X" $regaddr;
		else printf "%X" $regaddr >> $out_device; printf "%X" $regaddr;
	fi
	#Register value
	if [ $duty -lt 16 ]; then printf "000%X" $duty >> $out_device; printf "000%X" $duty;
		elif [ $duty -lt 256 ]; then printf "00%X" $duty >> $out_device; printf "00%X" $duty;
		elif [ $duty -lt 4096 ]; then printf "0%X" $duty >> $out_device; printf "0%X" $duty;
		else printf "%X" $duty >> $out_device; printf "%X" $duty;
	fi
	crc=$((((0-($devaddr+$func+$regaddr+(($duty>>8)&255)+($duty&255)))&255)))
	if [ $crc -lt 16 ]; then printf "0%X\n" $crc >> $out_device; printf "0%X\n" $crc;
		else printf "%X\n" $crc >> $out_device; printf "%X\n" $crc;
	fi
	return
}

stop_motor ()
{
	local crc
	local func=3
	local regaddr=0
	local ctrl_reg=32768
	#Start condition
	printf ":" >> $out_device; printf ":";
	#Motor number
	if [ $devaddr -lt 16 ]; then printf "0%X" $devaddr >> $out_device; printf "0%X" $devaddr;
		else printf "%X" $devaddr >> $out_device; printf "%X" $devaddr;
	fi
	#Function number
	if [ $func -lt 16 ]; then printf "0%X" $func >> $out_device; printf "0%X" $func;
		else printf "%X" $func >> $out_device; printf "%X" $func;
	fi
	#Register number
	if [ $regaddr -lt 16 ]; then printf "0%X" $regaddr >> $out_device; printf "0%X" $regaddr;
		else printf "%X" $regaddr >> $out_device; printf "%X" $regaddr;
	fi
	#Register value
	if [ $ctrl_reg -lt 16 ]; then printf "000%X" $ctrl_reg >> $out_device; printf "000%X" $ctrl_reg;
		elif [ $ctrl_reg -lt 256 ]; then printf "00%X" $ctrl_reg >> $out_device; printf "00%X" $ctrl_reg;
		elif [ $ctrl_reg -lt 4096 ]; then printf "0%X" $ctrl_reg >> $out_device; printf "0%X" $ctrl_reg;
		else printf "%X" $ctrl_reg >> $out_device; printf "%X" $ctrl_reg;
	fi
	crc=$((((0-($devaddr+$func+$regaddr+(($ctrl_reg>>8)&255)+($ctrl_reg&255)))&255)))
	if [ $crc -lt 16 ]; then printf "0%X\n" $crc >> $out_device; printf "0%X\n" $crc;
		else printf "%X\n" $crc >> $out_device; printf "%X\n" $crc;
	fi
	return
}

break_motor ()
{
	local crc
	local func=3
	local regaddr=0
	local ctrl_reg=32776
	#Start condition
	printf ":" >> $out_device; printf ":";
	#Motor number
	if [ $devaddr -lt 16 ]; then printf "0%X" $devaddr >> $out_device; printf "0%X" $devaddr;
		else printf "%X" $devaddr >> $out_device; printf "%X" $devaddr;
	fi
	#Function number
	if [ $func -lt 16 ]; then printf "0%X" $func >> $out_device; printf "0%X" $func;
		else printf "%X" $func >> $out_device; printf "%X" $func;
	fi
	#Register number
	if [ $regaddr -lt 16 ]; then printf "0%X" $regaddr >> $out_device; printf "0%X" $regaddr;
		else printf "%X" $regaddr >> $out_device; printf "%X" $regaddr;
	fi
	#Register value
	if [ $ctrl_reg -lt 16 ]; then printf "000%X" $ctrl_reg >> $out_device; printf "000%X" $ctrl_reg;
		elif [ $ctrl_reg -lt 256 ]; then printf "00%X" $ctrl_reg >> $out_device; printf "00%X" $ctrl_reg;
		elif [ $ctrl_reg -lt 4096 ]; then printf "0%X" $ctrl_reg >> $out_device; printf "0%X" $ctrl_reg;
		else printf "%X" $ctrl_reg >> $out_device; printf "%X" $ctrl_reg;
	fi
	crc=$((((0-($devaddr+$func+$regaddr+(($ctrl_reg>>8)&255)+($ctrl_reg&255)))&255)))
	if [ $crc -lt 16 ]; then printf "0%X\n" $crc >> $out_device; printf "0%X\n" $crc;
		else printf "%X\n" $crc >> $out_device; printf "%X\n" $crc;
	fi
	return
}

start_motor ()
{
	local crc
	local func=3
	local regaddr=0
	local ctrl_reg=32775
	#Start condition
	printf ":" >> $out_device; printf ":";
	#Motor number
	if [ $devaddr -lt 16 ]; then printf "0%X" $devaddr >> $out_device; printf "0%X" $devaddr;
		else printf "%X" $devaddr >> $out_device; printf "%X" $devaddr;
	fi
	#Function number
	if [ $func -lt 16 ]; then printf "0%X" $func >> $out_device; printf "0%X" $func;
		else printf "%X" $func >> $out_device; printf "%X" $func;
	fi
	#Register number
	if [ $regaddr -lt 16 ]; then printf "0%X" $regaddr >> $out_device; printf "0%X" $regaddr;
		else printf "%X" $regaddr >> $out_device; printf "%X" $regaddr;
	fi
	#Register value
	if [ $ctrl_reg -lt 16 ]; then printf "000%X" $ctrl_reg >> $out_device; printf "000%X" $ctrl_reg;
		elif [ $ctrl_reg -lt 256 ]; then printf "00%X" $ctrl_reg >> $out_device; printf "00%X" $ctrl_reg;
		elif [ $ctrl_reg -lt 4096 ]; then printf "0%X" $ctrl_reg >> $out_device; printf "0%X" $ctrl_reg;
		else printf "%X" $ctrl_reg >> $out_device; printf "%X" $ctrl_reg;
	fi
	crc=$((((0-($devaddr+$func+$regaddr+(($ctrl_reg>>8)&255)+($ctrl_reg&255)))&255)))
	if [ $crc -lt 16 ]; then printf "0%X\n" $crc >> $out_device; printf "0%X\n" $crc;
		else printf "%X\n" $crc >> $out_device; printf "%X\n" $crc;
	fi
	return
}

reverse_motor ()
{
	local crc
	local func=3
	local regaddr=0
	local ctrl_reg=32791
	#Start condition
	printf ":" >> $out_device; printf ":";
	#Motor number
	if [ $devaddr -lt 16 ]; then printf "0%X" $devaddr >> $out_device; printf "0%X" $devaddr;
		else printf "%X" $devaddr >> $out_device; printf "0%X" $devaddr;
	fi
	#Function number
	if [ $func -lt 16 ]; then printf "0%X" $func >> $out_device; printf "0%X" $devaddr;
		else printf "%X" $func >> $out_device; printf "0%X" $devaddr;
	fi
	#Register number
	if [ $regaddr -lt 16 ]; then printf "0%X" $regaddr >> $out_device; printf "0%X" $devaddr;
		else printf "%X" $regaddr >> $out_device; printf "0%X" $devaddr;
	fi
	#Register value
	if [ $ctrl_reg -lt 16 ]; then printf "000%X" $ctrl_reg >> $out_device; printf "0%X" $devaddr;
		elif [ $ctrl_reg -lt 256 ]; then printf "00%X" $ctrl_reg >> $out_device; printf "0%X" $devaddr;
		elif [ $ctrl_reg -lt 4096 ]; then printf "0%X" $ctrl_reg >> $out_device; printf "0%X" $devaddr;
		else printf "%X" $ctrl_reg >> $out_device; printf "0%X" $devaddr;
	fi
	crc=$((((0-($devaddr+$func+$regaddr+(($ctrl_reg>>8)&255)+($ctrl_reg&255)))&255)))
	if [ $crc -lt 16 ]; then printf "0%X\n" $crc >> $out_device; printf "0%X" $devaddr;
		else printf "%X\n" $crc >> $out_device; printf "0%X" $devaddr;
	fi
	return
}


#Init PWM period
devaddr=0; set_period_for_motor
devaddr=1; set_period_for_motor
devaddr=2; set_period_for_motor
devaddr=3; set_period_for_motor

#devaddr=0; duty=800; set_duty_for_motor
#devaddr=1; duty=800; set_duty_for_motor
#devaddr=2; duty=800; set_duty_for_motor
#devaddr=3; duty=800; set_duty_for_motor

#duty=999
#while [ $duty -gt 0 ]; do
	#devaddr=0; set_duty_for_motor
	#duty=$((duty-10))
#done

