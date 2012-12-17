#!/bin/bash

system=$(uname -s)
errors=0

echo -e "\n====== Configuring dependences ======"
echo -e "System identified as $system"
case $system in
    Linux) dependences="opencv_core
                        opencv_highgui
						opencv_imgproc
						asound
						qmake";;

    *) echo -e "This script hasn't been designed to work with your system, please refer to the README" && exit;;

esac


echo -e "\n====== Checking dependences ======"
for i in $dependences
do
	if [ $(locate $i | wc -l) == "0" ]
	then
		echo -e "[ERROR] Missing librairie : $i"
		errors=$(($errors+1))
	else
		echo -e "$i : ok"
	fi
done


if [ $errors != 0 ]
then
	echo -e "\n====== Dependences error, installation aborted ======" && exit
fi


echo -e "\n====== All dependences are ok, starting installation ======"
qmake
make
cp MDMA /usr/bin/MDMA


