#!/bash/bin

a=( "hi" "pujit" "kumar" )
echo "first element -${a[0]}"
echo "second element -${a[1]}"
echo "third element -${a[2]}"
echo "4th element -${a[3]}"
echo "length of array: - ${a[@]}"
a+=("cheeli")
echo "4th element -${a[3]}"

echo "length of array: - ${#a[@]}"
