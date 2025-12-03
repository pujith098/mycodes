CC = gcc
CFLAGS = -Wall -Wextra -O2

TARGET = reverse_int
SRC = reverse_int.c test_reverse_int.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

