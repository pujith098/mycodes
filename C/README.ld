# C Programming Practice Repository

This repository contains multiple C programming mini-projects, interview-practice problems, data-structure challenges, and modular buildable examples.  
Each subdirectory is a self-contained module with:

- Clean, maintainable C code  
- Modular design (`.c` + `.h` split if applicable)  
- Test programs  
- Makefiles  
- Documentation (README.md / README.ld)  

This repository is structured for easy study, interview preparation, and building real-world C modular projects.

---

# 📁 Directory Structure Overview

C/
├── cproject-1
├── interview_prep
└── practiced_codes

Below is a detailed description of each top-level directory.

---

# 1️⃣ **cproject-1 — Mini Employee Database Project**

**Type:** Small real-world modular C project  
**Includes:**  
- `employee_db.c` / `.h` – employee record parsing & lookup  
- `main.c` – command-line interface  
- `employees_1.csv` – sample database  
- `Makefile` and `/build` directory  

**Features:**  
- CSV employee data parsing  
- Searching, listing, simple data operations  
- Modular folder structure: `src/`, `inc/`, `build/`  
- Demonstrates a professional C project layout  

---

# 2️⃣ **interview_prep — Organized Coding Interview Problems**

This directory contains several standalone C challenges.  
Each folder includes:

- Core logic file(s)  
- Unit test / generator  
- Makefile  
- README  

## 📦 Submodules

### 🔹 **ARRAY_REVERSE/**  
Implements array reversal with test generator.

### 🔹 **ENDIAN_NESS/**  
Detect system endianness with bit tricks.

### 🔹 **FIBINOCKI_UPTO_LIMIT/**  
Generates Fibonacci numbers below a limit.

### 🔹 **LL_PALINDROME_CHECK/**  
Linked list palindrome validator.  
Includes:
- Linked list builder  
- Loop creation  
- Stress test generator  

### 🔹 **PALINDROME_OR_NOT/**  
String palindrome checker.

### 🔹 **PRIME_NUMBER_OR_NOT/**  
Optimized primality test + randomized test cases.

### 🔹 **REVERSE_BITS_OF_32bit_UINT/**  
Optimized bit-twiddling based 32-bit bit reversal.

### 🔹 **REVERSE_SIGNED_INT_DIGITS/**  
Safe integer reverse with overflow detection (LeetCode-style).

---

# 3️⃣ **practiced_codes — Core C Concept Practice**

This folder contains simple C programs meant for learning language foundations.

## Included Programs
- Pointer basics  
- Function pointers  
- Memory alignment & padding  
- `volatile` usage  
- Custom `strcpy`, `strrev`  
- Power of 2 check  
- Swap with/without temp  
- Digit sum  
- Basic algorithms (factorial, patterns)  
- Simple embedded-style bit code  

These are intentionally kept simple and focused.

---

# 🚀 Build Instructions

Every subproject with a Makefile can be built inside its own folder:

make
make run
make clean

---
