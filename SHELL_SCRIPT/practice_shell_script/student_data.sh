
while :
do
	read -s -p "enter the name:- " name
	if [ "$name" = "exit" ]; then
		break
	else
	echo "entered name- $name"
	fi
done
