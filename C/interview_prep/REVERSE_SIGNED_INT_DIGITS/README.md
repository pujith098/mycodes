# Reverse Integer (32-bit Safe)

This project implements a safe 32-bit integer reversal function in C, including overflow handling.  
If reversing the number would overflow `INT_MAX` or `INT_MIN`, the function returns `0`.

---

## 📁 Files

reverse_int.c         # Core reverse-int logic (NO main)
test_reverse_int.c    # Full test suite + user input (main)
Makefile              # Build/run/clean
README.md             # Documentation

---

## 🚀 Features

- Reverses signed 32-bit integers  
- Detects & prevents overflow  
- Returns `0` on overflow (LeetCode style behavior)  
- Clean modular design  
- Automatic test suite  
- Manual test mode  

---

## 🔧 Build & Run

Build:

make

Run tests:

make run

Clean:

make clean

---

## 📌 Function Description

### `int reverse_int(int x);`

Reverses the digits of an integer:

| Input | Output |
|-------|--------|
| 123 | 321 |
| -123 | -321 |
| 1200 | 21 |
| INT_MAX, INT_MIN | 0 (overflow) |

---

## 🧪 Test Suite

The included test file covers:

- Zero  
- Positive & negative numbers  
- Values ending with zeros  
- Large inputs  
- Overflow cases  
- Manual user input  

---
