#/bin/bash


file="arth_operator.sh"
while IFS= read -r line
do
	echo "$line"
done < $"$file"


