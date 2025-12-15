# COMMON MODULE

This directory contains all reusable components for C interview problems.

## Logger
- `logger_init()` to configure LOG_LEVEL from environment
- Macros: `LOG_ERROR()`, `LOG_WARN()`, `LOG_INFO()`, `LOG_DEBUG()`
- Used for debug and reporting across all problems

## Test Framework
- `run_test_generic()` to run a single test
- `print_test_summary()` to display pass/fail counters
- Tracks TOTAL_TESTS, PASSED_TESTS, FAILED_TESTS

## Array Helpers
- Random arrays, single-element, empty, all same
- Memory-safe allocation and freeing

## String Helpers
- Random strings, empty strings, single character strings

## Linked List Helpers
- Generate linked list from array
- Free linked list memory

## Usage
Include headers in problem-specific tests and implementations to reuse logging, testing, and helper utilities.
