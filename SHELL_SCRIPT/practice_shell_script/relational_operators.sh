#!/bin/bash

read -p "enter a value : - " a
read -p "enter b value : - " b

if [ $a -eq $b ];then	#equal 
	echo "a is qual to b"
fi
if [ $a -ne $b ];then	#not equal
       echo "a is not equal to  b"
fi
if [ $a -gt $b ];then	#greater than
	echo "a is greater than b"
fi
if [ $a -lt $b ];then	#less than
	echo "a is less than b"
fi
