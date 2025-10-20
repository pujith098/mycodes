#!/bin/bash

read -t 5 -p "give input with in 5 seconds" var

if [ -z "$var" ];then
       echo "No value enterned within 5 sec"
else 
 	echo "value entered : -$var"
fi
