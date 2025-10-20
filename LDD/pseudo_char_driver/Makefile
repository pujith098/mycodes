# -------------------------
# Kernel module build
# -------------------------
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
MODULE_NAME := simple_char_driver_templete

# -------------------------
# User-space application
# -------------------------
USER_APP := psedo_char_driver_test_appilication
CC := gcc

# -------------------------
# Targets
# -------------------------

all: module user_app

# Build kernel module
module:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

# Build user-space test application
user_app: $(USER_APP).c
	$(CC) -o $(USER_APP) $(USER_APP).c

# Remove all generated files
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	$(RM) $(USER_APP) a.out

.PHONY: all module user_app clean

