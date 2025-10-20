arr=("one" "two" "three")
count=0
for item in ${arr[@]}
do
	echo "item -$item, arr - ${arr[$count]}"
	((count+=1))
done
