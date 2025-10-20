#!/bin/bash

for file in *temp*;do
	if [ -f "$file" ];then
		echo "deleteing - $file"
		rm -r $file
	fi
done
