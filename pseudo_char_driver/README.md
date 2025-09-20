
# Pseudo Character Device Driver


## Overview

This project demonstrates a **Linux kernel pseudo character device driver** with multiple device instances, along with a **user-space test application**. It is intended for educational purposes to learn Linux device driver development and interaction with user-space applications.

The driver features:

- Multiple character devices (default: 4)
- Read and write operations
- `ioctl` support to clear device buffer
- Dynamic creation of device nodes in `/dev/`
- Memory management using `kmalloc` and `kfree`

---

## Directory Structure


pseudo\_char\_driver/
├── Makefile
├── README.md
├── simple\_char\_driver\_templete.c
├── simple\_char\_driver\_templete.ko
├── psedo\_char\_driver\_test\_appilication.c
└── Module.symvers

````

---

## Requirements

- Linux system with kernel headers installed for the running kernel
- GCC compiler
- `sudo` privileges for module insertion/removal

---

## Build Instructions

1. **Build the kernel module and user-space application**


   make


2. **Insert the kernel module**

 
   sudo insmod simple_char_driver_templete.ko


3. **Check kernel messages**


   sudo dmesg | tail -n 20

   Expected output:
   ===============

   [PseudoChar] Loaded 4 devices (major XXX)

4. **Compile and Run the user-space test application**

   cc psedo_char_driver_test_appilication.c -o psedo_char_driver_test_appilication

   ./psedo_char_driver_test_appilication

5.3. **Check kernel messages**

   sudo dmesg | tail -n 20

---

## User-Space Test Application Features

The test application performs the following:

1. Lists available pseudo devices:

   ls /dev/pseudo_char_dev*

   /dev/pseudo_char_dev0
   /dev/pseudo_char_dev1
   /dev/pseudo_char_dev2
   /dev/pseudo_char_dev3
   ```

2. Writes data to any device and reads back:


   Enter device number: 0
   Enter text to write: Hello Kernel
   Read from device: Hello Kernel


3. Clears device buffer using `ioctl`:


   ioctl command executed: buffer cleared


4. Demonstrates kernel-user space interaction for character devices

---

## Module Removal

1. **Remove the kernel module**

   sudo rmmod simple_char_driver_templete

2. **Check kernel messages for unload confirmation**

   sudo dmesg | tail -n 20

   Expected output:
   ===============

   [PseudoChar] Unloaded 4 devices

---

## Clean Build Artifacts

To remove compiled files and clean the directory:

```bash
make clean
```

---

## Module Information

* **License:** GPL
* **Author:** CHEELI Pujitkumar
* **Description:** Modern Multi-Device Pseudo Char Driver
* **Version:** 3.0

---

## Notes

* Tested on Ubuntu 24.04 with kernel `6.14.0-28-generic`.
* Kernel module interacts with `/dev` devices using standard file operations.
* The test application demonstrates read/write/ioctl usage.

---

## References

* [Linux Device Drivers, 3rd Edition](https://lwn.net/Kernel/LDD3/)
* [Linux Kernel Documentation](https://www.kernel.org/doc/html/latest/)



 


