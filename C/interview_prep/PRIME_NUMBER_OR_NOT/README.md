Prime Number Checker – Modular C Project with Full Edge-Case Testing

This project demonstrates a clean, modular, optimized implementation of a prime-checking function in C, along with a comprehensive automated test suite and a Makefile for easy build/run.

It is ideal for:

Coding interview preparation

Practicing modular C programming

Learning algorithm optimization

Demonstrating clean project structure

📂 Project Structure
.
├── prime.c          # Optimized is_prime() implementation
├── test_prime.c     # Automatic edge-case and random test generator
├── Makefile         # Build, run, clean targets
└── README.md         # Documentation

🔍 1. prime.c — Optimized Prime Checking

The file prime.c contains an efficient implementation of:

int is_prime(int n)

🚀 Optimization Features

Rejects negative numbers and zero

Handles small numbers (1, 2, 3) correctly

Eliminates all even numbers early

Checks divisors only up to sqrt(n)

Iterates only odd numbers after 3

Very fast for large values

Return Values
Value	Meaning
1	Number is prime
0	Number is not prime
🔍 2. test_prime.c — Complete Test Suite

This file includes:

✔ Deterministic Edge-Case Tests

Covers:

Negative numbers

Zero

1, special-cased

2 (first prime)

Small primes & composites

Random small values

Random medium values

Very large integers (INT_MAX)

✔ Randomized Stress Tests

Every run generates:

Small numbers

Mid-range values

Extremely large values

All printed in structured test format

📝 Sample Test Output
=============================
TEST 4
Input number: 97
Result: PRIME ✔
=============================

=============================
TEST 8
Input number: 0
Result: NOT PRIME ✘
=============================

🔧 Build Instructions
Compile:
make

Run:
make run

Clean:
make clean
