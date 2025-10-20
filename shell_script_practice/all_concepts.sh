#!/bin/bash
# Practice script demonstrating multiple shell scripting concepts

# ===== Variables and Command Substitution =====
name="Pujit"
date_today=$(date +%F)
echo "Hello, $name! Today is $date_today."

# ===== Arithmetic =====
a=10
b=3
echo "Sum: $((a + b)), Product: $((a * b)), Division: $((a / b))"

# ===== Arrays =====
fruits=("apple" "banana" "cherry")
echo "First fruit: ${fruits[0]}"
echo "All fruits: ${fruits[@]}"

# ===== If/Else =====
if [[ $a -gt $b ]]; then
    echo "$a is greater than $b"
else
    echo "$b is greater or equal to $a"
fi

# ===== Case Statement =====
read -p "Enter a letter (a/b/c): " letter
case $letter in
    a) echo "You chose A";;
    b) echo "You chose B";;
    c) echo "You chose C";;
    *) echo "Invalid choice";;
esac

# ===== For Loop =====
echo "Numbers from 1 to 5:"
for i in {1..5}; do
    echo " - $i"
done

# ===== While Loop =====
count=1
while [[ $count -le 3 ]]; do
    echo "While loop iteration $count"
    ((count++))
done

# ===== Until Loop =====
n=5
until [[ $n -le 0 ]]; do
    echo "Countdown: $n"
    ((n--))
done

# ===== Functions =====
greet_user() {
    echo "Welcome, $1! This is a function demo."
}
greet_user "$name"

# ===== String Operations =====
str="HelloShellScripting"
echo "Length of string: ${#str}"
echo "Substring (5 chars from index 5): ${str:5:5}"
echo "Replace 'Shell' with 'Bash': ${str/Shell/Bash}"

# ===== File Handling =====
echo "Creating a file 'demo.txt'..."
echo "This is a test file created on $date_today" > demo.txt
echo "File contents:"
cat demo.txt

# ===== Reading from File =====
echo "Reading back line by line:"
while read -r line; do
    echo "-> $line"
done < demo.txt

# ===== Trap (Signal Handling) =====
trap "echo 'Script interrupted! Cleaning up...'; rm -f demo.txt; exit" SIGINT

echo "Press Ctrl+C to test trap (wait 5s)..."
sleep 5

echo "Script finished successfully!"

