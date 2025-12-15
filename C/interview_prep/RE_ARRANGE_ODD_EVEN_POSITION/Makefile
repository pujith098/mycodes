CC = gcc
CFLAGS = -Wall -Wextra -I./common

TARGET = test_rearrange_ll
SRC = rearrange_ll.c test_rearrange_ll.c \
      ../common/logger.c ../common/test_common.c ../common/test_linked_list_helper.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

