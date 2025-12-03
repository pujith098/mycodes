## **VL805 MMIO Reader/Writer – Raspberry Pi 4 USB 3.0 Controller (PCIe)**

### **Overview**

This kernel module provides **direct MMIO (memory-mapped I/O) access** to the VIA Labs **VL805 USB 3.0 controller** on the Raspberry Pi 4.
The VL805 is a **PCIe xHCI USB 3.0 host controller**, and this module enables:

* Reading raw PCIe **BAR0 registers**
* Writing to BAR0 registers (**dangerous**)
* Inspecting important xHCI registers (CAPLENGTH, USBCMD, USBSTS, etc.)
* Sending read/write commands through a **debugfs interface**

This is intended for **educational, research, and hardware exploration purposes only**.

> ⚠️ **DANGER:** Writing incorrect values to VL805 registers can freeze USB, disconnect devices, or crash the system.
> Use at your own risk!

---

## **Features**

* Automatically detects the VL805 PCI device (Vendor ID: `0x1b73`)
* Maps PCIe BAR0 into kernel space via `pci_iomap()`
* Logs critical controller registers to `dmesg`
* Exposes debugfs interface:

  * `R <offset>` → read 32-bit from offset
  * `W <offset> <value>` → write 32-bit value to offset

Example:

echo "R 0x100" | sudo tee /sys/kernel/vl805_regs/cmd

---

## **Files**

vl805_mmio_rw_via_pcie_bar.c		# Kernel module source code
Makefile            		 	# Build rules
README.md            			# Documentation

---

## **Prerequisites**

Install dependencies:

sudo apt update
sudo apt install raspberrypi-kernel-headers build-essential pciutils

---

## **Build**

Run:

make

This generates:

vl805_mmio_rw.ko

---

## **Load the Module**

sudo insmod vl805_mmio_rw.ko

or (recommended):

sudo modprobe vl805_mmio_rw

---

## **Verify It Loaded**

dmesg | grep vl805

You should see lines like:

vl805_mmio_rw: CAPLENGTH=0x40
vl805_mmio_rw: USBCMD = 0x00000000
vl805_mmio_rw: USBSTS = 0x00000001

---

## **DebugFS Interface**

When loaded, the module creates:

/sys/kernel/vl805_regs/cmd

### **Read 32-bit Register**

echo "R 0x100" | sudo tee /sys/kernel/vl805_regs/cmd

Check output:

dmesg | tail

### **Write 32-bit Register (dangerous)**

echo "W 0x100 0x1" | sudo tee /sys/kernel/vl805_regs/cmd

---

## **Unload the Module**

sudo rmmod vl805_mmio_rw

---

## **Unbinding xHCI (Optional, Advanced)**

If you want to safely modify sensitive registers, unbind the xHCI driver:

echo -n "0000:01:00.0" | sudo tee /sys/bus/pci/drivers/xhci_hcd/unbind

Rebind:

echo -n "0000:01:00.0" | sudo tee /sys/bus/pci/drivers/xhci_hcd/bind

---

## **Troubleshooting**

### **VL805 not visible in `lspci`**

Make sure:

* Raspberry Pi 4 has latest EEPROM firmware
* VL805 firmware is loaded correctly

Update:

sudo rpi-eeprom-update

Check PCI devices:

lspci -nn

---

## **License**

GPL v2

---

## **Author**
PUJIT

