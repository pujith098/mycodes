# Median of Two Sorted Arrays — C Project

This project implements a function to find the **median of two sorted arrays**.  
It handles arrays of different lengths and empty arrays safely.

---

## 📁 Project Structure

median.c           # Core logic
median.h           # Header file
test_median.c      # Test suite
Makefile           # Build/run/clean
README.md          # Documentation

---

## 🔧 Build & Run

Compile:

make

Run tests:

make run

Clean build:

make clean

---

## 📌 Function

### `double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size);`

- Returns the **median** of the merged arrays.  
- Handles **odd/even total length** correctly.  
- Uses `malloc` + `qsort` internally for simplicity.  

Example:

int nums1[] = {1, 3};
int nums2[] = {2};
double median = findMedianSortedArrays(nums1, 2, nums2, 1);
// median = 2.0

---

## 🧪 Test Cases Included

1. Odd total length: `[1,3]`, `[2]`  
2. Even total length: `[1,2]`, `[3,4]`  
3. Empty first array: `[]`, `[1]`  
4. All zeros: `[0,0]`, `[0,0]`  
5. Both arrays empty: `[]`, `[]`  
