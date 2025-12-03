# C Interview Preparation Repository

This folder contains a collection of C programming exercises and interview practice problems.  
Each subfolder is a self-contained project with:

- Core logic (`.c` / `.h`)  
- Test programs  
- Makefiles  
- Documentation  

The exercises cover algorithms, data structures, bit manipulation, and common interview problems.

---

## 📁 Subfolder Overview

### 1️⃣ ARRAY_REVERSE
- Reverse arrays in C  
- Includes automated test generator  
- Files: `array_reverse.c`, `array_reverse.h`, `test_generator.c`, `test_reverse`, `README.ld`  

### 2️⃣ ENDIAN_NESS
- Detect system endianness  
- Works on 32-bit and 64-bit systems  
- Files: `detect_endianness.c`, `detect_endianness.h`, `main.c`, `test_endianness.c`, `endian_test`, `README.md`  

### 3️⃣ FIBINOCKI_UPTO_LIMIT
- Generate Fibonacci numbers up to a limit  
- Handles edge cases and negative numbers  
- Files: `fabinoci.c`, `test_fabinoci.c`, `makefile`, `README.md`  

### 4️⃣ LL_PALINDROME_CHECK
- Check if a linked list is a palindrome  
- Handles loops detection in linked list  
- Files: `linked_list.c`, `linked_list.h`, `test_generator.c`, `test_palindrome`, `README.md`  

### 5️⃣ PALINDROME_OR_NOT
- Check if a string is a palindrome  
- Automatic and manual testing  
- Files: `string_palindrome.c`, `test_string_palindrome.c`, `Makefile`, `README.ld`  

### 6️⃣ PRIME_NUMBER_OR_NOT
- Check if a number is prime  
- Optimized with √n complexity  
- Files: `prime.c`, `test_prime.c`, `Makefile`, `README.md`  

### 7️⃣ REVERSE_BITS_OF_32bit_UINT
- Reverse bits in a 32-bit unsigned integer  
- Optimized branch-free implementation  
- Files: `reverse_bits.c`, `test_reverse_bits.c`, `Makefile`, `README.ld`  

### 8️⃣ REVERSE_SIGNED_INT_DIGITS
- Reverse digits of a signed integer safely  
- Handles 32-bit overflow (returns 0 on overflow)  
- Files: `reverse_int.c`, `test_reverse_int.c`, `Makefile`, `README.ld`  

---

## 🚀 Features

- Covers arrays, strings, linked lists, and integers  
- Edge-case and stress test coverage  
- Randomized test generators for many problems  
- Modular design (`.c` + `.h`)  
- Makefile-based build system for each project  

---

## 🔧 Build & Run Instructions

1. Navigate to a subfolder:

cd interview_prep/FIBINOCKI_UPTO_LIMIT

2. Build the project:

make

3. Run the test program:

make run

4. Clean build artifacts:

make clean

> Each subfolder follows a similar structure and Makefile commands.

---

## 🧪 Test Coverage

- Deterministic edge cases: negative numbers, 0, 1, small/large numbers  
- Randomized tests for stress testing  
- Manual input mode for interactive testing  

---
