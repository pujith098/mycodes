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

### 2️⃣ A_TO_I
- Convert string to 32-bit integer (`myAtoi`)  
- Handles spaces, `+/-` signs, overflow, invalid characters  
- Files: `atoi.c`, `atoi.h`, `test_atoi.c`, `Makefile`, `README.ld`  

### 3️⃣ ENDIAN_NESS
- Detect system endianness  
- Works on 32-bit and 64-bit systems  
- Files: `detect_endianness.c`, `detect_endianness.h`, `main.c`, `test_endianness.c`, `endian_test`, `README.md`  

### 4️⃣ FIBINOCKI_UPTO_LIMIT
- Generate Fibonacci numbers up to a limit  
- Handles edge cases and negative numbers  
- Files: `fabinoci.c`, `test_fabinoci.c`, `makefile`, `README.md`  

### 5️⃣ LL_PALINDROME_CHECK
- Check if a linked list is a palindrome  
- Handles loop detection in linked list  
- Files: `linked_list.c`, `linked_list.h`, `test_generator.c`, `test_palindrome`, `README.md`  

### 6️⃣ LOGEST_PALINDROME_IN_STRING
- Find the longest palindromic substring in a string  
- Brute-force or optimized implementations  
- Files: `palindrome.c`, `palindrome.h`, `test_palindrome.c`, `Makefile`, `README.ld`  

### 7️⃣ LONGEST_SUB_STRING_NO_DUP_CHAR
- Find length of longest substring without repeating characters  
- Sliding window algorithm (O(n) time)  
- Files: `substring.c`, `test_substring.c`, `Makefile`, `README.ld`  

### 8️⃣ MEDIAN_OF_MERGED_ARRAY
- Find median of two sorted arrays  
- Handles arrays of different lengths and empty arrays  
- Files: `median.c`, `median.h`, `test_median.c`, `Makefile`, `README.ld`  

### 9️⃣ PALINDROME_OR_NOT
- Check if a string is a palindrome  
- Automatic and manual testing  
- Files: `string_palindrome.c`, `test_string_palindrome.c`, `Makefile`, `README.ld`  

### 🔟 PRIME_NUMBER_OR_NOT
- Check if a number is prime  
- Optimized with √n complexity  
- Files: `prime.c`, `test_prime.c`, `Makefile`, `README.md`  

### 1️⃣1️⃣ REVERSE_BITS_OF_32bit_UINT
- Reverse bits in a 32-bit unsigned integer  
- Optimized branch-free implementation  
- Files: `reverse_bits.c`, `test_reverse_bits.c`, `Makefile`, `README.ld`  

### 1️⃣2️⃣ REVERSE_SIGNED_INT_DIGITS
- Reverse digits of a signed integer safely  
- Handles 32-bit overflow (returns 0 on overflow)  
- Files: `reverse_int.c`, `test_reverse_int.c`, `Makefile`, `README.ld`  

---

## 🚀 Features

- Covers arrays, strings, linked lists, integers, and bit operations  
- Edge-case and stress test coverage  
- Randomized test generators for many problems  
- Modular design (`.c` + `.h`)  
- Makefile-based build system for each project  

---




