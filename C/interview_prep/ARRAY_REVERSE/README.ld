# 📘 Array In-place Reversal — Automated Test Suite

This project implements a **modular in-place array reversal** program with a **comprehensive automated test suite**, inspired by the linked list palindrome checker project.  

The test suite generates multiple types of arrays, logs all steps, and verifies the reversal logic automatically.



- **Reverse array in-place**: `reverse_array_inplace(int *a, int size)`  
- **Automated test generator**:
  - Random arrays
  - Palindrome-like arrays
  - Patterned arrays (repeated sequences)
  - Single-value arrays
- **Edge case coverage**:
  - Empty array, single element
  - Even and odd length arrays
  - Arrays with repeated values
  - Large arrays (up to `MAX_SIZE = 50`, configurable)
- **Detailed logs**:
  - Generated array contents
  - Input type for each test
  - Swap operations during reversal
  - Final reversed array
- **Modular code structure**: Separate header and source files for reusability

---

## Build & Run

#Compile

gcc array_reverse.c test_generator.c -o test_reverse

#Run

./test_reverse

