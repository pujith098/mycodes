savedcmd_/home/dell/pujith/ldd/sysfs/driver.mod := printf '%s\n'   driver.o | awk '!x[$$0]++ { print("/home/dell/pujith/ldd/sysfs/"$$0) }' > /home/dell/pujith/ldd/sysfs/driver.mod
