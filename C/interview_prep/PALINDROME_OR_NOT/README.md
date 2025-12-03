# String Palindrome Checker (C Project)

This project provides a modular C implementation of a string palindrome checker, including a full test suite and Makefile.

---

## 📁 Project Structure

string_palindrome.c        # Core logic (no main)
test_string_palindrome.c   # Test suite + manual tests (has main)
Makefile                   # Build/run/clean
README.md                  # Documentation

---

## 🚀 Features

- Checks if a string is a palindrome  
- Handles edge cases: empty string, single char, symbols  
- Clean modular design  
- Full automatic test suite  
- Manual testing mode  
- Ready for interviews or practice  

---

## 🔧 Build & Run

Compile:

make

Run test suite:

make run

Clean:

make clean

---

## 📌 Function

### `int is_palindrome(const char *s);`

Returns:

- `1` → palindrome  
- `0` → not palindrome  

Examples:

| Input | Output |
|-------|--------|
| "madam" | Palindrome |
| "abba" | Palindrome |
| "charan" | Not Palindrome |
| "" | Palindrome |
| "a" | Palindrome |

---

## 🧪 Test Coverage

Includes tests for:

- Normal strings  
- Empty string  
- Single-character string  
- Numeric strings  
- Mixed characters (!@# etc.)  
- Symmetric/asymmetric strings  
- Manual user input  

---



