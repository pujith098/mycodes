# Fibonacci Number Generator (C Project)

This project provides a clean and modular implementation of a Fibonacci generator in C, including a full test suite and Makefile.

---

## 📁 Project Structure

fabinoci.c          # Core Fibonacci logic (no main)
test_fabinoci.c     # Test runner + main function
Makefile            # Build, run, clean
README.md           # Documentation

---

## 🚀 Features

- Prints all Fibonacci numbers *below* a given limit  
- Handles edge cases: negative numbers, 0, 1, small values  
- Fully modular (logic separated from main)  
- Automatic test suite  
- Manual interactive mode  
- Simple Makefile for easy building  

---

## 🔧 Build

Compile everything:

make

Run automatic tests + manual input mode:

make run

Clean the build:

make clean

---

## 📌 Function Description

### `void fabinoci(int limit);`

Prints Fibonacci numbers starting at `0, 1` and continues while:

next_number < limit

Handles negative inputs gracefully.

---

## 🧪 Test Program

`test_fabinoci.c` automatically tests:

- Negative input  
- Zero  
- 1 and 2  
- Small ranges  
- Large ranges  
- Manual input  

Example output:

=== TEST (limit = 10) ===
0, 1, 1, 2, 3, 5, 8
=========================

---

## 📄 License

Free to use, modify, study, or include in personal practice projects.


