# 🔌 Custom USB Mass Storage Driver — Raspberry Pi

This directory contains a **custom Linux USB driver** implemented and tested on a **Raspberry Pi** running a recent Linux kernel (e.g., 6.x series).  
The driver demonstrates how to register a USB driver, parse USB endpoints, handle probe/disconnect events, and perform control and bulk transfers — similar to a simplified version of the Linux **usb-storage** driver.

---

## 📁 Directory Structure

| File | Description |
|------|-------------|
| `custom_usb_mass.c` | Main source code implementing the custom USB mass storage–like driver. |
| `Makefile` | Kernel module Makefile for building the driver. |
| `README.md` | This file — explains purpose, build steps, and debugging notes. |

---

## ⚙️ Environment Setup

Make sure your Raspberry Pi has the required development tools and headers:

```bash
sudo apt update
sudo apt install raspberrypi-kernel-headers build-essential git

