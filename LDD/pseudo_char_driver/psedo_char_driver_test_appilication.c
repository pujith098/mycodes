#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>

#define DEVICE "/dev/pseudo_char_dev0"

// Define same ioctl macro as in your driver
#define MAGIC_NUM 0xF0
#define CLEAR_BUFFER _IO(MAGIC_NUM, 0)

int main() {
    int fd;
    char write_buf[] = "Hello from user space!";
    char read_buf[100];

    printf("Opening device: %s\n", DEVICE);
    fd = open(DEVICE, O_RDWR);
    if (fd < 0) {
        perror("open");
        return EXIT_FAILURE;
    }

    // Step 1: Write
    printf("Writing to device: %s\n", write_buf);
    ssize_t written = write(fd, write_buf, strlen(write_buf));
    if (written < 0) {
        perror("write");
        close(fd);
        return EXIT_FAILURE;
    }
    printf("Wrote %zd bytes\n", written);

    // Step 2: Read back
    lseek(fd, 0, SEEK_SET); // reset file offset to beginning
    ssize_t read_bytes = read(fd, read_buf, sizeof(read_buf) - 1);
    if (read_bytes < 0) {
        perror("read");
        close(fd);
        return EXIT_FAILURE;
    }
    read_buf[read_bytes] = '\0';
    printf("Read from device: %s\n", read_buf);

    // Step 3: IOCTL - clear buffer
    printf("Calling ioctl to clear buffer...\n");
    if (ioctl(fd, CLEAR_BUFFER) == -1) {
        perror("ioctl");
    } else {
        printf("Buffer cleared successfully!\n");
    }

    // Step 4: Read again (should be empty)
    lseek(fd, 0, SEEK_SET);
    read_bytes = read(fd, read_buf, sizeof(read_buf) - 1);
    if (read_bytes < 0) {
        perror("read after ioctl");
    } else {
        read_buf[read_bytes] = '\0';
        printf("After ioctl, read returned: \"%s\"\n", read_buf);
    }

    // Step 5: Close
    close(fd);
    printf("Device closed.\n");

    return EXIT_SUCCESS;
}

