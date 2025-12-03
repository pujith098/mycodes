# Longest Palindromic Substring — C Project

This project implements a function to find the **longest palindromic substring** in a given string.  
It includes modular code, a full test suite, and a Makefile for easy build and run.

---

## 📁 Project Structure

palindrome.c         # Core logic (no main)
test_palindrome.c    # Main + test suite
Makefile             # Build/run/clean
README.md            # Documentation

---

## 🔧 Build Instructions

Compile:

make

Run tests:

make run

Clean build:

make clean

---

## 📌 Function Overview

### `char* longestPalindrome(char* s);`

- Returns a **malloc'ed string** containing the longest palindromic substring.  
- Caller is responsible for freeing the returned string.  

Example:

char *s = "babad";
char *res = longestPalindrome(s);
// res could be "bab" or "aba"
free(res);

---

### `int isPalindrome(char *s, int left, int right);`

- Returns 1 if the substring `s[left..right]` is a palindrome, 0 otherwise.

---

## 🧪 Test Cases Included

- Empty string  
- Single character  
- Two identical / different characters  
- Odd and even length palindromes  
- Strings with multiple palindrome possibilities  
- Manual input for user testing  

