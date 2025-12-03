# myAtoi — String to 32-bit Signed Integer in C

This project implements a function similar to **C’s atoi** but handles:

- Leading/trailing spaces  
- Optional `+`/`-` signs  
- Leading zeros  
- Overflow detection (returns `INT_MAX` / `INT_MIN`)  
- Non-digit characters  

---

## 📁 Project Structure

atoi.c           # Core function
atoi.h           # Header file
test_atoi.c      # Test suite + manual input
Makefile         # Build/run/clean
README.md        # Documentation

---

## 🔧 Build & Run

Compile:

make

Run tests:

make run

Clean build:

make clean

---

## 📌 Function

### `int myAtoi(char* s);`

Converts string `s` to 32-bit signed integer.  
Handles spaces, signs, overflow, and invalid characters.

Example:

char *s = "   -42";
int n = myAtoi(s);  // n == -42

---

## 🧪 Test Cases Included

- Simple numbers: `"42"`  
- Leading spaces: `"   -42"`  
- Strings with words: `"4193 with words"`  
- Words first: `"words and 987"`  
- Overflow: `"-91283472332"`, `"91283472332"`  
- Leading zeros: `"0000123"`  
- Signs: `"+1"`, `"-0"`  
- Empty string / spaces only

---
