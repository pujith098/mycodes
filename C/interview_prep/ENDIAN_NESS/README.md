# Endianness Detection (with Tests)

This project provides portable C code to detect the system's endianness
(little-endian or big-endian) and includes a built-in test suite — all using a
single `main()` function.

The project is separated into:
- **Core endianness detection code**
- **Test functions (no main)**
- **A single main driver that runs both detection and tests**

---

Then checks the first byte in memory:

If first byte is 0x02 → little-endian

If first byte is 0x01 → big-endian

This method works on all platforms, including:

x86 / x86_64

ARM (AArch32/AArch64)

RISC-V

MIPS

PowerP## 🔍 How Endianness Detection Works

The program stores a 16-bit number:

uint16_t v = 0x0102;

🔧 Build Instructions

Compile all files together (one final executable):

gcc -o endian_test main.c detect_endianness.c test_endianness.c

▶ Run the Program
./endian_test


Expected output
--------------

=== Platform Endianness Check ===
Detected system is little-endian

Running endian tests...
[TEST] Expected: little-endian
[TEST] Detected: little-endian
[PASS] Endianness detection is correct.

