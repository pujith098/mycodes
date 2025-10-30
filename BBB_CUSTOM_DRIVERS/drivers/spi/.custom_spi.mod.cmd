savedcmd_/home/debian/drivers/spi/custom_spi.mod := printf '%s\n'   custom_spi.o | awk '!x[$$0]++ { print("/home/debian/drivers/spi/"$$0) }' > /home/debian/drivers/spi/custom_spi.mod
