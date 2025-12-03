CC = gcc
CFLAGS = -Wall -Wextra -O2

TARGET = reverse
SRC = reverse_bits.c test_reverse_bits.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

