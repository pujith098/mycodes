read -p "enter a value : - " a
read -p "enter b value : - " b

if [ $a -eq $b ] || [ $a -gt $b ];then
	echo "any one of the condition is true"
	
fi

if [ $a -eq $b ] && [ $a -gt $b ];then
	echo "both conditions are true"

fi
if ! [ $a -eq 0 ];then
	echo "a is not equal to zero"
fi
