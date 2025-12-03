# Reverse Bits (32-bit) — C Implementation

This project provides an optimized implementation of reversing bits in a 32-bit unsigned integer using efficient bit-twiddling techniques.

---

## 📁 Files

reverse_bits.c       # Core logic (no main)
test_reverse_bits.c  # Main + full test suite
Makefile             # Build, run, clean
README.md            # Documentation

---

## 🚀 Features

- Fully optimized 32-bit bit-reversal  
- Branch-free, fast operations  
- Clean modular design  
- Automatic test suite  
- Optional manual testing mode  
- Works on all standard C compilers  

---

## 🔧 Build & Run

Compile:

make

Run tests:

make run

Clean output:

make clean

---

## 📌 Function

### `uint32_t reverse_bits(uint32_t x);`

Reverses all 32 bits:

Input:  00000010 00000000 00000000 00000000
Output: 00000000 00000000 00000000 01000000


## 🧪 Test Program

The test suite checks:

- All zeros  
- All ones  
- Highest / lowest bit  
- Alternating patterns  
- Random patterns  
- Manual hex input  

Example:

Input:  0xF0F0A5A5
Output: 0xA5A50F0F




