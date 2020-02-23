#!/bin/bash
# set an infinite loop
while :
do
	clear
        # display menu
        echo "Server Name - $(hostname)"
	echo "-------------------------------"
	echo "     RASPBERRY PI M A I N - M E N U"
	echo "-------------------------------"
	echo "1. Display Raspberry Pi Temperature."
	echo "2. Display Raspberry Pi CPU Usage."
  echo "3. Exit"

        # get input from the user
	read -p "Enter your choice [ 1 -2 ] " choice

	case $choice in
		1)
			echo "CPU Temperature: $(vcgencmd measure_temp | cut -f2 -d'=' | cut -f1 -)"
			read -p "Press [Enter] key to continue..." readEnterKey
			;;
		2)
      echo "Raspberry Pi CPU Usage: $(iostat -c 2 2)"
			read -p "Press [Enter] key to continue..." readEnterKey
			;;
    3)
			echo "Bye!"
			exit 0
			;;
		*)
			echo "Error: Invalid option..."
			read -p "Press [Enter] key to continue..." readEnterKey
			;;
	esac

done
