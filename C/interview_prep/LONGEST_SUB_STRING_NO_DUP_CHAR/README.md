# Longest Substring Without Repeating Characters — C Project

This project implements a function to find the **length of the longest substring without repeating characters** in a string.  
It includes:

- Modular core (`substring.c`)  
- Full test suite with edge cases and random strings (`test_substring.c`)  
- Makefile for easy build/run/clean  
- Documentation

---

## 📁 Project Structure

substring.c         # Core logic (no main)
test_substring.c    # Main + test suite
Makefile            # Build/run/clean
README.md           # This documentation

---

## 🔧 Build Instructions

Compile everything:

make

Run tests (automatic + manual input):

make run

Clean the build:

make clean

---

## 📌 Function Overview

### `int lengthOfLongestSubstring(char *s);`

Returns the length of the **longest substring without repeating characters**.

Example:

char *s = "abcabcbb";
int len = lengthOfLongestSubstring(s);
// len = 3 ("abc")

